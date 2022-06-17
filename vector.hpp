
#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

# include <iostream>

# include "utils/reverse_iterator.hpp"
# include "utils/random_access_iterator.hpp"
# include "utils/enable_if.hpp"
# include "utils/is_integral.hpp"
# include "utils/lexicographical_compare.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            /*
            ** Member types:
            */
			typedef	T										                value_type;
			typedef	Alloc									                allocator_type;
            typedef	value_type&    							                reference;
            typedef	const value_type&						                const_reference;
			typedef value_type*								                pointer;
			typedef const value_type*						                const_pointer;
			typedef	ft::random_access_iterator<value_type>                  iterator;
			typedef	ft::random_access_iterator<const value_type>            const_iterator;
			typedef ft::reverse_iterator<iterator>				            reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		            const_reverse_iterator;
			typedef	typename ft::iterator_traits<iterator>::difference_type difference_type;
			typedef size_t													size_type;

        private:
            pointer                     __array;
            allocator_type              __allocator;
            size_type                   __size;
            size_type                   __capacity;

		public:
/* Constructors: *****************************************************************************************************/
            /*
            ** Constructors:
            */
                /*
                ** Default Constructor:
                */
                explicit vector (const allocator_type& alloc = allocator_type()) : __allocator(alloc)
                {
                    this->__capacity = 0;
                    this->__size = 0;
                    this->__array = nullptr;
                }
                /*
                ** Fill Constructor:
                */
                explicit vector (size_type n, const_reference val = value_type(), const allocator_type& alloc = allocator_type()) : __allocator(alloc)
                {
                    this->__size = 0;
                    this->__capacity = 0;
                    this->__array = nullptr;
                    this->assign(n, val);
                }
                /*
                ** Range Constructor:
                */
                template<typename InputIterator>
                vector(InputIterator first,
                        InputIterator last,
                        const allocator_type& alloc = allocator_type(),
                        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
                : __allocator(alloc)
                {
                    this->__size = 0;
                    this->__capacity = std::distance(first, last);
                    this->__array = __allocator.allocate(this->__capacity);
                    while (first != last)
                    {
                        this->__allocator.construct(this->__array + __size, *first);
                        __size++;
                        first++;
                    }
                }
                /*
                ** Copy Constructor:
                */
                vector (const vector& x)
                {
                    if (this != &x)
                    {
                        this->__size = x.__size;
                        this->__capacity = x.__capacity;
                        this->__allocator = x.__allocator;
                        if (this->__capacity)
                            this->__array = this->__allocator.allocate(this->__capacity);
                        else
                            this->__array = nullptr;
                        for (size_type i = 0; i != this->__size; i++)
                        {
                            this->__allocator.construct(this->__array + i, x[i]);
                        }
                    }
                }
/* Destructor: *****************************************************************************************************/
            /*
            ** Destructor:
            */
            ~vector()
            {
                for (size_type i = 0; i != this->size(); i++)
                    this->__allocator.destroy(this->__array + i);
                this->__size = 0;
                if (this->__capacity)
                {
                    __allocator.deallocate(this->__array, this->__capacity);
                    this->__array = nullptr;
                    this->__capacity = 0;
                }
                return ;
            }
/* Operator=: ****************************************************************************************************/
            /*
            ** Operator=:
            */
            vector& operator=(const vector& src)
            {
                if (this != &src)
                {
                    size_type   index = 0;

                    for (size_type i = 0; i != this->__size; i++)
                        this->__allocator.destroy(this->__array + i);
                    if (this->__capacity)
                        this->__allocator.deallocate(this->__array, this->__capacity);
                    this->__size = src.__size;
                    this->__capacity = src.__capacity;
                    if (this->__capacity)
                    {
                        this->__array = this->__allocator.allocate(src.__capacity);
                    }
                    else
                    {
                        this->__array = nullptr;
                    }
                    while (index < src.size())
                    {
                        this->__allocator.construct(__array + index, src[index]);
                        index++;
                    }
                }
                return (*this);
            }
/* Iterators: ****************************************************************************************************/
            /*
            ** Iterators:
            */
                iterator begin( void ) { return iterator(this->__array[0]); }

                const_iterator begin() const {  return const_iterator(this->__array[0]); }

                iterator end() { return iterator(this->__array[this->__size]); }

                const_iterator end() const { return const_iterator(this->__array[this->__size]); }

                reverse_iterator rbegin() { return reverse_iterator(this->end()); }

                const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }

                reverse_iterator rend() { return reverse_iterator(this->begin()); }

                const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }
/* Capacity: ****************************************************************************************************/
            /*
            ** Capacity:
            */
                /*
                ** Size:
                */
                size_type size() const { return this->__size; }

                /*
                ** Max Size:
                */
                size_type max_size() const { return this->__allocator.max_size(); }

                /*
                ** Resize:
                */
                void resize (size_type n, value_type val = value_type())
                {
                    if (n == this->__size)
                        return ;
                    else if (n < this->__size)
                    {
                        for (size_type i = n; i < n; i++)
                        {
                            this->__allocator.destroy(this->__array + i);
                        }
                        this->__size = n;
                    }
                    else
                    {
                        if (this->__capacity * 2 >= n && n > this->__capacity)
                            this->reserve(this->__capacity * 2);
                        this->insert(this->end(), n - this->__size, val);
                        this->__size = n;
                    }
                }

                /*
                ** Capacity:
                */
                size_type capacity() const { return this->__capacity; }

                /*
                ** Empty:
                */
                bool empty() const { return (this->__size == 0); }

                /*
                ** Reserve:
                */
                void reserve (size_type n)
                {
                    if (n > 0 && this->__capacity < n)
                    {
                        size_type   index = 0;
                        pointer     new_arr = this->__allocator.allocate(n);

                        for (iterator it = this->begin(); it < this->end(); it++)
                        {
                            this->__allocator.construct(new_arr + index, *it);
                            index++;
                        }
                        for (size_type i = 0; i < this->__size; i++)
                            __allocator.destroy(this->__array + i);
                        if (this->__capacity)
                            __allocator.deallocate(this->__array, this->__capacity);
                        this->__array = new_arr;
                        this->__capacity = n;
                    }
                }

            /*
            ** Element Access: ********************************************************************
            */
                /*
                **  Operator[]:
                */
                reference operator[] (size_type n) { return this->__array[n]; }

                /*
                **  Const Operator[]:
                */
                const_reference operator[] (size_type n) const { return this->__array[n]; }

                /*
                **  At:
                */
                reference at (size_type n)
                {
                    if (n >= this->__size)
                        throw std::out_of_range("Out Of Range.");
                    return this->__array[n];
                }

                /*
                **  Const At:
                */
                const_reference at (size_type n) const
                {
                    if (n >= this->__size)
                        throw std::out_of_range("Out Of Range.");
                    return this->__array[n];
                }

                /*
                **  Front:
                */
                reference front() { return this->__array[0]; }

                /*
                **  Const Front:
                */
                const_reference front() const { return this->__array[0]; }

                /*
                **  Back:
                */
                reference back() { return this->__array[this->__size - 1]; }

                /*
                **  Const Back:
                */
                const_reference back() const { return this->__array[this->__size - 1]; }

            /*
            ** Modifiers: *************************************************************************
            */
                /*
                **  Range Assignment:
                */
                template <class InputIterator>
                void assign (InputIterator first, InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
                {
                    size_type       old_size = this->size();

                    this->__size = std::distance(first, last);
                    if (this->__capacity < this->__size)
                    {
                        for (size_type i = 0; i < old_size; i++)
                            this->__allocator.destroy(this->__array + i);
                        if (this->__capacity)
                        {
                            this->__allocator.deallocate(this->__array, this->__capacity);
                            this->__array = NULL;
                        }
                        this->__capacity = this->__size;
                        this->__array = this->__allocator.allocate(this->__capacity);
                    }
                    size_type   c = 0;
                    while (first != last)
                    {
                        this->__allocator.construct(&(this->__array[c]), *first);
                        c++;
                        first++;
                    }
                }

                /*
                **  Fill Assignment:
                */
                void assign (size_type n, const value_type& val)
                {
                    if (this->__capacity < n)
                    {
                        for (size_type i = 0; i != this->__size; i++)
                            this->__allocator.destroy(this->__array + i);
                        if (this->__capacity)
                        {
                            this->__allocator.deallocate(this->__array, this->__capacity);
                            this->__array = nullptr;
                            this->__capacity = 0;
                        }
                        if (n)
                        {
                            this->__array = this->__allocator.allocate(n);
                            this->__capacity = n;
                        }
                        else
                        {
                            this->__array = nullptr;
                            this->__capacity = 0;
                        }
                        for (size_type i = 0; i < n; i++)
                            this->__allocator.construct(this->__array + i, val);
                        this->__size = n;
                        return ;
                    }
                    for (size_type i = 0; i != this->__size; i++)
                        this->__allocator.destroy(this->__array + i);
                    for (size_type i = 0; i < n; i++)
                    {
                        this->__allocator.construct(this->__array + i, val);
                    }
                    this->__size = n;
                    return ;
                }

                /*
                **  Push Back:
                */
                void push_back (const value_type& val)
                {
                    size_type   old_size = this->__size;
                    size_type   old_capacity = this->__capacity;

                    if (this->__size + 1 <= this->__capacity)
                        this->__allocator.construct(this->__array + this->__size, val);
                    else
                    {
                        pointer     new_array;
                        size_type   index = 0;
                        if (this->__capacity == 0)
                        {
                            this->__capacity++;
                            new_array = this->__allocator.allocate(this->__capacity);
                        }
                        else
                        {
                            new_array = this->__allocator.allocate(this->__capacity * 2);
                            this->__capacity *= 2;
                        }
                        while (index < this->__size)
                        {
                            this->__allocator.construct(new_array + index, this->__array[index]);
                            index++;
                        }
                        this->__allocator.construct(new_array + index, val);
                        for (size_type i = 0; i != old_size; i++)
                            this->__allocator.destroy(this->__array + i);
                        if (old_capacity)
                            this->__allocator.deallocate(this->__array, old_capacity);
                        this->__array = new_array;
                    }
                    this->__size++;
                }
                /*
                **  Pop Back:
                */
                void pop_back()
                {
                    this->__allocator.destroy(&this->back());
                    this->__size--;
                }
                /*
                **  Single Elament - Insert:
                */
                iterator insert (iterator position, const value_type& val)
                {
                    if (this->__size == 0)
                    {
                        iterator    ret;
                        if (this->begin() == position)
                        {
                            this->__array = this->__allocator.allocate(1);
                            this->__allocator.construct(this->__array , val);
                            this->__size++;
                            this->__capacity = this->__size;
                            ret = this->begin();
                        }
                        return (ret);
                    }
                    else if (this->__size + 1 <= this->__capacity)
                    {
                        iterator    it = this->end();
                        for (; it >= position + 1; it--)
                        {
                            if (it != this->end())
                                this->__allocator.construct(this->__array + (it - this->begin() + 1), *it);
                            if ((size_type)(it - this->begin()) < this->__size)
                                this->__allocator.destroy(this->__array + (it - this->begin()));
                        }
                        this->__allocator.construct(this->__array + (it - this->begin() + 1), *it);
                        if ((size_type)(it - this->begin()) < this->__size)
                            this->__allocator.destroy(this->__array + (it - this->begin()));
                        this->__allocator.construct(this->__array + (it - this->begin()), val);
                        this->__size++;
                        return (it);
                    }
                    else
                    {
                        iterator    ret;
                        int         ret_index = 0;
                        pointer     new_array = this->__allocator.allocate(this->__size * 2);
                        size_type   index = 0;

                        for (iterator it = this->begin(); it <= this->end() ; it++)
                        {
                            if (it == position)
                            {
                                this->__allocator.construct(new_array + index, val);
                                this->__allocator.construct(new_array + index + 1, *it);
                                ret_index = index;
                                index++;
                            }
                            else
                                this->__allocator.construct(new_array + index, *it);
                            index++;
                        }
                        for (size_type i = 0; i != this->__size; i++)
                            this->__allocator.destroy(this->__array + i);
                        if (this->__capacity)
                            this->__allocator.deallocate(this->__array, this->__capacity);
                        this->__array = new_array;
                        this->__capacity = this->__size * 2;
                        this->__size++;
                        ret = this->begin() + ret_index;
                        return (ret);
                    }
                }
                /*
                **  Fill - Insert:
                */
                void insert (iterator position, size_type n, const value_type& val)
                {
                    if (n == 0)
                        return ;
                    if (this->__size + n <= this->__capacity)
                    {
                        iterator    it = this->end();
                        size_type   tmp = n;

                        for (; it > position; it--)
                        {
                            this->__allocator.construct(this->__array + (it - this->begin() + n), *it);
                            this->__allocator.destroy(this->__array + (it - this->begin()));
                        }
                        this->__allocator.construct(this->__array + (it - this->begin() + n), *it);
                        while (n)
                        {
                            this->__allocator.construct(this->__array + (it - this->begin()), val);
                            it++;
                            n--;
                        }
                        this->__size += tmp;
                    }
                    else
                    {
                        size_t      new_capacity = 0;
                        pointer     new_array = NULL;
                        if (this->__size + n <= this->__size * 2)
                        {
                            new_array = this->__allocator.allocate(this->__size * 2);
                            new_capacity = this->__size * 2;
                        }
                        else
                        {
                            new_array = this->__allocator.allocate(this->__size + n);
                            new_capacity = this->__size + n;
                        }
                        iterator    it = this->begin();
                        size_type   tmp = n;
                        for (size_type index = 0; index < this->__size + n; index++)
                        {
                            if (it == position && tmp)
                            {
                                while (tmp)
                                {
                                    this->__allocator.construct(new_array + index, val);
                                    tmp--;
                                    index++;
                                }
                                if (index < new_capacity)
                                    this->__allocator.construct(new_array + index, *it);
                                it++;
                            }
                            else
                            {
                                this->__allocator.construct(new_array + index, *it);
                                it++;
                            }
                        }
                        this->__size += n;
                        this->__allocator.deallocate(this->__array, this->__capacity);
                        this->__capacity = new_capacity;
                        this->__array = new_array;
                    }
                }

                /*
                **  Range - Insert:
                */
                template <class InputIterator>
                void insert (iterator position, InputIterator first, InputIterator last,
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator())
                {
                    const size_type   n = std::distance(first, last);
                    if (n == 0)
                        return ;
                    if (this->__size + n <= this->__capacity)
                    {
                        iterator    it = this->end() - 1;

                        for (; it > position; it--)
                            this->__allocator.construct(this->__array + (it - this->begin() + n), *it);
                        this->__allocator.construct(this->__array + (it - this->begin() + n), *it);
                        while (first != last)
                        {
                            this->__allocator.construct(this->__array + (it - this->begin()), *first);
                            it++;
                            first++;
                        }
                        this->__size += n;
                    }
                    else
                    {
                        iterator    it = this->begin();
                        iterator    end = this->end();
                        pointer     new_array;
                        if (this->__size + n <= this->__size * 2)
                        {
                            new_array = this->__allocator.allocate(this->__size * 2);
                            this->__capacity = this->__size * 2;
                        }
                        else
                        {
                            new_array = this->__allocator.allocate(this->__size + n);
                            this->__capacity = this->__size + n;
                        }
                        size_type   index = 0;
                        for (; it != end; it++)
                        {
                            if (it == position)
                                break;
                            else
                            {
                                this->__allocator.construct(new_array + index, *it);
                                index++;
                            }
                        }
                        size_type insert_index = index;
                        while (first != last)
                        {
                            this->__allocator.construct(new_array + insert_index, *first);
                            first++;
                            insert_index++;
                        }
                        for (; it != end; it++)
                        {
                            this->__allocator.construct(new_array + insert_index, *it);
                            insert_index++;
                        }
                        this->__allocator.deallocate(this->__array, this->__capacity);
                        this->__array = new_array;
                        this->__size += n;
                    }
                }
            /*
            ** Erase: *************************************************************************
            */
                /*
                **  Position-Erase:
                */
                iterator erase (iterator position)
                {
					size_type	index = position - this->begin();
					iterator	ret = position;

					this->__allocator.destroy(this->__array + index);
					for (; index < this->__size - 1; index++)
					{
						this->__allocator.destroy(this->__array + index);
						this->__allocator.construct(this->__array + index, this->__array[index + 1]);
					}
					this->__size--;
					return ret;
                }
                /*
                **  Range-Erase:
                */
                iterator erase (iterator first, iterator last)
                {
                    size_type   n = last - first;
                    iterator    ret;
                    if (n)
                    {
                        iterator    begin = this->begin();
                        iterator    end = this->end();
                        while (begin != end)
                        {
                            if (begin == first)
                                break;
                            begin++;
                        }
                        ret = begin;
                        size_type index = 0;
                        while (begin != end && (last + index) != end)
                        {
                            *begin = *(last + index);
                            index++;
                            begin++;
                        }
                        this->__size -= n;
                    }
                    else
                        return this->erase(first);
                    return ret;
                }
            /*
            ** Swap: *************************************************************************
            */
            void swap (vector& x)
            {
				// (void)x;
                pointer         tmp_pointer = this->__array;
                size_type       tmp_size = this->__size;
                size_type       tmp_capacity = this->__capacity;
                allocator_type  tmp_allocator = this->__allocator;

                this->__array = x.__array;
                this->__size = x.__size;
                this->__capacity = x.__capacity;
                this->__allocator = x.__allocator;

                x.__array = tmp_pointer;
                x.__size = tmp_size;
                x.__capacity = tmp_capacity;
                x.__allocator = tmp_allocator;
            }
            /*
            ** Clear: *************************************************************************
            */
            void clear()
            {
                this->__size = 0;
            }

            /*
            ** Allocator: *************************************************************************
            */
                /*
                **  Get_allocator:
                */
                allocator_type get_allocator() const
                {
                    return (this->__allocator);
                }
    };  // CLASS VECTOR

    template <class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        typedef typename ft::vector<T>::const_iterator   const_iterator;

        if (lhs.size() != rhs.size())
            return (false);
        const_iterator     lit = lhs.begin();
        const_iterator     rit = rhs.begin();

        for (; lit < lhs.end(); lit++, rit++)
            if (*lit != *rit)
                return (false);
        return (true);
    }

    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(operator==(lhs, rhs)));
    }

    template <class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare< ft::vector<T>::const_iterator, ft::vector<T>::const_iterator > compare(lhs.begin(), lhs.end(), rhs.begin(). rhs.end());
        // size_t  minSize = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
        // size_t  i = 0;

        // for (; i < minSize; i++)
        //     if (lhs[i] < rhs[i])
        //         return (true);
        // if (lhs.end() == lhs.begin() + i && rhs.begin() + i != rhs.end())
        //     return (true);
        // return (false);
    }

    template <class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        size_t  minSize = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
        size_t  i = 0;

        for (; i < minSize; i++)
            if (lhs[i] > rhs[i])
                return (true);
        if (rhs.end() == rhs.begin() + i && lhs.begin() + i != lhs.end())
            return (true);
        return (false);
    }

    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(operator>(lhs, rhs)));
    }

    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (!(operator<(lhs, rhs)));
    }

    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
    {
        x.swap(y);
    }
};  // NAMEDPACE FT;

#endif
