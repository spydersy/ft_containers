
#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

# include <iostream>

# include "utils/reverse_iterator.hpp"
# include "utils/random_access_iterator.hpp"
# include "utils/enable_if.hpp"
# include "utils/is_integral.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            /*
            ** Member types:
            */
                // typedef     T                                           value_type;
                // typedef     Alloc                                       allocator_type;
                // typedef     typename allocator_type::reference	        reference;
                // typedef     typename allocator_type::const_reference    const_reference;
                // typedef     typename allocator_type::pointer            pointer;
                // typedef     typename allocator_type::const_pointer	    const_pointer;
                // typedef     size_t                                      size_type;
                // typedef     ft::Iterator<value_type>                    iterator;
                // typedef     ft::Iterator<value_type const>              const_iterator;
                // typedef     ft::reverse_iterator<iterator>              reverse_iterator;
                // typedef     ft::reverse_iterator< const_iterator>       const_reverse_iterator;


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


		public:
/* Constructors: *****************************************************************************************************/
            /*
            ** Constructors:
            */
                /*
                ** Default Constructor:
                */
                explicit vector (const allocator_type& alloc = allocator_type()) : _vector_allocator(alloc)
                {
                    std::cout << "WEWE" << std::endl;
                    this->_capacity = 0;
                    this->_size = 0;
                    this->_array = nullptr;
                }
                /*
                ** Fill Constructor:
                */
                explicit vector (size_type n, const_reference val = value_type(), const allocator_type& alloc = allocator_type()) : _vector_allocator(alloc)
                {
                    this->_size = 0;
                    this->_capacity = 0;
                    this->_array = nullptr;
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
                : _vector_allocator(alloc)
                {
                    this->_size = 0;
                    this->_capacity = std::distance(first, last);
                    this->_array = _vector_allocator.allocate(this->_capacity);
                    while (first != last)
                    {
                        this->_vector_allocator.construct(this->_array + _size, *first);
                        _size++;
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
                        this->_size = x._size;
                        this->_capacity = x._capacity;
                        this->_vector_allocator = x._vector_allocator;
                        if (this->_capacity)
                            this->_array = this->_vector_allocator.allocate(this->_capacity);
                        else
                            this->_array = nullptr;
                        for (size_type i = 0; i != this->_size; i++)
                        {
                            this->_vector_allocator.construct(this->_array + i, x[i]);
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
                    this->_vector_allocator.destroy(this->_array + i);
                this->_size = 0;
                if (this->_capacity)
                {
                    _vector_allocator.deallocate(this->_array, this->_capacity);
                    this->_array = nullptr;
                    this->_capacity = 0;
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

                    for (size_type i = 0; i != this->_size; i++)
                        this->_vector_allocator.destroy(this->_array + i);
                    if (this->_capacity)
                        this->_vector_allocator.deallocate(this->_array, this->_capacity);
                    this->_size = src._size;
                    this->_capacity = src._capacity;
                    if (this->_capacity)
                    {
                        this->_array = this->_vector_allocator.allocate(src._capacity);
                    }
                    else
                    {
                        this->_array = nullptr;
                    }
                    while (index < src.size())
                    {
                        this->_vector_allocator.construct(_array + index, src[index]);
                        index++;
                    }
                }
                return (*this);
            }
/* Iterators: ****************************************************************************************************/
            /*
            ** Iterators:
            */
                iterator begin( void ) { return iterator(this->_array[0]); }

                const_iterator begin() const {  return const_iterator(this->_array[0]); }

                iterator end() { return iterator(this->_array[this->_size]); }

                const_iterator end() const { return const_iterator(this->_array[this->_size]); }

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
                size_type size() const { return this->_size; }

                /*
                ** Max Size:
                */
                size_type max_size() const { return this->_vector_allocator.max_size(); }

                /*
                ** Resize:
                */
                void resize (size_type n, value_type val = value_type())
                {
                    if (n == this->_size)
                        return ;
                    else if (n < this->_size)
                    {
                        for (size_type i = n; i < n; i++)
                        {
                            this->_vector_allocator.destroy(this->_array + i);
                        }
                        this->_size = n;
                    }
                    else
                    {
                        if (this->_capacity * 2 >= n && n > this->_capacity)
                            this->reserve(this->_capacity * 2);
                        this->insert(this->end(), n - this->_size, val);
                        this->_size = n;
                    }
                }

                /*
                ** Capacity:
                */
                size_type capacity() const { return this->_capacity; }

                /*
                ** Empty:
                */
                bool empty() const { return (this->_size == 0); }

                /*
                ** Reserve:
                */
                void reserve (size_type n)
                {
                    if (n > 0 && this->_capacity < n)
                    {
                        size_type   index = 0;
                        pointer     new_arr = this->_vector_allocator.allocate(n);

                        for (iterator it = this->begin(); it < this->end(); it++)
                        {
                            this->_vector_allocator.construct(new_arr + index, *it);
                            index++;
                        }
                        for (size_type i = 0; i < this->_size; i++)
                            _vector_allocator.destroy(this->_array + i);
                        if (this->_capacity)
                            _vector_allocator.deallocate(this->_array, this->_capacity);
                        this->_array = new_arr;
                        this->_capacity = n;
                    }
                }

            /*
            ** Element Access: ********************************************************************
            */
                /*
                **  Operator[]:
                */
                reference operator[] (size_type n) { return this->_array[n]; }

                /*
                **  Const Operator[]:
                */
                const_reference operator[] (size_type n) const { return this->_array[n]; }

                /*
                **  At:
                */
                reference at (size_type n)
                {
                    if (n >= this->_size)
                        throw std::out_of_range("Out Of Range.");
                    return this->_array[n];
                }

                /*
                **  Const At:
                */
                const_reference at (size_type n) const
                {
                    if (n >= this->_size)
                        throw std::out_of_range("Out Of Range.");
                    return this->_array[n];
                }

                /*
                **  Front:
                */
                reference front() { return this->_array[0]; }

                /*
                **  Const Front:
                */
                const_reference front() const { return this->_array[0]; }

                /*
                **  Back:
                */
                reference back() { return this->_array[this->_size - 1]; }

                /*
                **  Const Back:
                */
                const_reference back() const { return this->_array[this->_size - 1]; }

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

                    this->_size = std::distance(first, last);
                    if (this->_capacity < this->_size)
                    {
                        for (size_type i = 0; i < old_size; i++)
                            this->_vector_allocator.destroy(this->_array + i);
                        if (this->_capacity)
                        {
                            this->_vector_allocator.deallocate(this->_array, this->_capacity);
                            this->_array = NULL;
                        }
                        this->_capacity = this->_size;
                        this->_array = this->_vector_allocator.allocate(this->_capacity);
                    }
                    size_type   c = 0;
                    while (first < last)
                    {
                        this->_vector_allocator.construct(&(this->_array[c]), *first);
                        c++;
                        first++;
                    }
                }

                /*
                **  Fill Assignment:
                */
                void assign (size_type n, const value_type& val)
                {
                    if (this->_capacity < n)
                    {
                        for (size_type i = 0; i != this->_size; i++)
                            this->_vector_allocator.destroy(this->_array + i);
                        if (this->_capacity)
                        {
                            this->_vector_allocator.deallocate(this->_array, this->_capacity);
                            this->_array = nullptr;
                            this->_capacity = 0;
                        }
                        if (n)
                        {
                            this->_array = this->_vector_allocator.allocate(n);
                            this->_capacity = n;
                        }
                        else
                        {
                            this->_array = nullptr;
                            this->_capacity = 0;
                        }
                        for (size_type i = 0; i < n; i++)
                            this->_vector_allocator.construct(this->_array + i, val);
                        this->_size = n;
                        return ;
                    }
                    for (size_type i = 0; i != this->_size; i++)
                        this->_vector_allocator.destroy(this->_array + i);
                    for (size_type i = 0; i < n; i++)
                    {
                        this->_vector_allocator.construct(this->_array + i, val);
                    }
                    this->_size = n;
                    return ;
                }

                /*
                **  Push Back:
                */
                void push_back (const value_type& val)
                {
                    size_type   old_size = this->_size;
                    size_type   old_capacity = this->_capacity;

                    if (this->_size + 1 <= this->_capacity)
                        this->_vector_allocator.construct(this->_array + this->_size, val);
                    else
                    {
                        pointer     new_array;
                        size_type   index = 0;
                        if (this->_capacity == 0)
                        {
                            this->_capacity++;
                            new_array = this->_vector_allocator.allocate(this->_capacity);
                        }
                        else
                        {
                            new_array = this->_vector_allocator.allocate(this->_capacity * 2);
                            this->_capacity *= 2;
                        }
                        while (index < this->_size)
                        {
                            this->_vector_allocator.construct(new_array + index, this->_array[index]);
                            index++;
                        }
                        this->_vector_allocator.construct(new_array + index, val);
                        for (size_type i = 0; i != old_size; i++)
                            this->_vector_allocator.destroy(this->_array + i);
                        if (old_capacity)
                            this->_vector_allocator.deallocate(this->_array, old_capacity);
                        this->_array = new_array;
                    }
                    this->_size++;
                }
                /*
                **  Pop Back:
                */
                void pop_back()
                {
                    this->_vector_allocator.destroy(&this->back());
                    this->_size--;
                }
                /*
                **  Single Elament - Insert:
                */
                iterator insert (iterator position, const value_type& val)
                {
                    if (this->_size == 0)
                    {
                        iterator    ret;
                        if (this->begin() == position)
                        {
                            this->_array = this->_vector_allocator.allocate(1);
                            this->_vector_allocator.construct(this->_array , val);
                            this->_size++;
                            this->_capacity = this->_size;
                            ret = this->begin();
                        }
                        return (ret);
                    }
                    else if (this->_size + 1 <= this->_capacity)
                    {
                        iterator    it = this->end() - 1;
                        for (; it >= position + 1; it--)
                        {
                            this->_vector_allocator.construct(this->_array + (it - this->begin() + 1), *it);
                            if ((size_type)(it - this->begin()) < this->_size)
                                this->_vector_allocator.destroy(this->_array + (it - this->begin()));
                        }
                        this->_vector_allocator.construct(this->_array + (it - this->begin() + 1), *it);
                        if ((size_type)(it - this->begin()) < this->_size)
                            this->_vector_allocator.destroy(this->_array + (it - this->begin()));
                        this->_vector_allocator.construct(this->_array + (it - this->begin()), val);
                        this->_size++;
                        return (it);
                    }
                    else
                    {
                        iterator    ret;
                        int         ret_index = 0;
                        pointer     new_array = this->_vector_allocator.allocate(this->_size * 2);
                        size_type   index = 0;

                        for (iterator it = this->begin(); it <= this->end() ; it++)
                        {
                            if (it == position)
                            {
                                this->_vector_allocator.construct(new_array + index, val);
                                this->_vector_allocator.construct(new_array + index + 1, *it);
                                ret_index = index;
                                index++;
                            }
                            else
                                this->_vector_allocator.construct(new_array + index, *it);
                            index++;
                        }
                        for (size_type i = 0; i != this->_size; i++)
                            this->_vector_allocator.destroy(this->_array + i);
                        if (this->_capacity)
                            this->_vector_allocator.deallocate(this->_array, this->_capacity);
                        this->_array = new_array;
                        this->_capacity = this->_size * 2;
                        this->_size++;
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
                    if (this->_size + n <= this->_capacity)
                    {
                        iterator    it = this->end();
                        size_type   tmp = n;

                        for (; it > position; it--)
                        {
                            this->_vector_allocator.construct(this->_array + (it - this->begin() + n), *it);
                            this->_vector_allocator.destroy(this->_array + (it - this->begin()));
                        }
                        this->_vector_allocator.construct(this->_array + (it - this->begin() + n), *it);
                        while (n)
                        {
                            this->_vector_allocator.construct(this->_array + (it - this->begin()), val);
                            it++;
                            n--;
                        }
                        this->_size += tmp;
                    }
                    else
                    {
                        size_t      new_capacity = 0;
                        pointer     new_array = NULL;
                        if (this->_size + n <= this->_size * 2)
                        {
                            new_array = this->_vector_allocator.allocate(this->_size * 2);
                            new_capacity = this->_size * 2;
                        }
                        else
                        {
                            new_array = this->_vector_allocator.allocate(this->_size + n);
                            new_capacity = this->_size + n;
                        }
                        iterator    it = this->begin();
                        size_type   tmp = n;
                        for (size_type index = 0; index < this->_size + n; index++)
                        {
                            if (it == position && tmp)
                            {
                                while (tmp)
                                {
                                    this->_vector_allocator.construct(new_array + index, val);
                                    tmp--;
                                    index++;
                                }
                                if (index < new_capacity)
                                    this->_vector_allocator.construct(new_array + index, *it);
                                it++;
                            }
                            else
                            {
                                this->_vector_allocator.construct(new_array + index, *it);
                                it++;
                            }
                        }
                        this->_size += n;
                        this->_vector_allocator.deallocate(this->_array, this->_capacity);
                        this->_capacity = new_capacity;
                        this->_array = new_array;
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
                    if (this->_size + n <= this->_capacity)
                    {
                        iterator    it = this->end() - 1;

                        for (; it > position; it--)
                            this->_vector_allocator.construct(this->_array + (it - this->begin() + n), *it);
                        this->_vector_allocator.construct(this->_array + (it - this->begin() + n), *it);
                        while (first < last)
                        {
                            this->_vector_allocator.construct(this->_array + (it - this->begin()), *first);
                            it++;
                            first++;
                        }
                        this->_size += n;
                    }
                    else
                    {
                        iterator    it = this->begin();
                        iterator    end = this->end();
                        pointer     new_array;
                        if (this->_size + n <= this->_size * 2)
                        {
                            new_array = this->_vector_allocator.allocate(this->_size * 2);
                            this->_capacity = this->_size * 2;
                        }
                        else
                        {
                            new_array = this->_vector_allocator.allocate(this->_size + n);
                            this->_capacity = this->_size + n;
                        }
                        size_type   index = 0;
                        for (; it != end; it++)
                        {
                            if (it == position)
                                break;
                            else
                            {
                                this->_vector_allocator.construct(new_array + index, *it);
                                index++;
                            }
                        }
                        size_type insert_index = index;
                        while (first < last)
                        {
                            this->_vector_allocator.construct(new_array + insert_index, *first);
                            first++;
                            insert_index++;
                        }
                        for (; it != end; it++)
                        {
                            this->_vector_allocator.construct(new_array + insert_index, *it);
                            insert_index++;
                        }
                        this->_vector_allocator.deallocate(this->_array, this->_capacity);
                        this->_array = new_array;
                        this->_size += n;
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

					this->_vector_allocator.destroy(this->_array + index);
					for (; index < this->_size - 1; index++)
					{
						this->_vector_allocator.destroy(this->_array + index);
						this->_vector_allocator.construct(this->_array + index, this->_array[index + 1]);
					}
					this->_size--;
					return ret;
					// iterator    ret;
                    // iterator    end = this->end();
                    // iterator it = this->begin();

                    // for (; it < end ; it++)
                    // {
                    //     if (it == position)
                    //     {
                    //         ret = it;
                    //         this->_size--;
                    //         break ;
                    //     }
                    // }
                    // it--;
                    // while (++it != end)
                    //     *(it - 1) = *it;
                    // return (ret);
                }
                /*
                **  Range-Erase:
                */
                iterator erase (iterator first, iterator last)
                {
                    size_type   n = last - first;
                    iterator    ret;
                    this->_size -= n;
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
                    }
                    else
                        return (this->erase(first));
                    return ret;
                }
            /*
            ** Swap: *************************************************************************
            */
            void swap (vector& x)
            {
				// (void)x;
                pointer         tmp_pointer = this->_array;
                size_type       tmp_size = this->_size;
                size_type       tmp_capacity = this->_capacity;
                allocator_type  tmp_allocator = this->_vector_allocator;

                this->_array = x._array;
                this->_size = x._size;
                this->_capacity = x._capacity;
                this->_vector_allocator = x._vector_allocator;

                x._array = tmp_pointer;
                x._size = tmp_size;
                x._capacity = tmp_capacity;
                x._vector_allocator = tmp_allocator;
            }
            /*
            ** Clear: *************************************************************************
            */
            void clear()
            {
                this->_size = 0;
            }

            /*
            ** Allocator: *************************************************************************
            */
                /*
                **  Get_allocator:
                */
                allocator_type get_allocator() const
                {
                    return (this->_vector_allocator);
                }

/*****************************************************************************************************/
        private:
            pointer                     _array;
            allocator_type              _vector_allocator;
            size_type                   _size;
            size_type                   _capacity;

            size_type        capacity_calculator(size_type const current_size)
            {
                if (current_size == 0)
                    return (0);
                for (size_type capacity = 1;; capacity *= 2)
                    if (capacity >= current_size)
                        return (capacity);
            }
    };

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
        size_t  minSize = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
        size_t  i = 0;

        for (; i < minSize; i++)
            if (lhs[i] < rhs[i])
                return (true);
        if (lhs.end() == lhs.begin() + i && rhs.begin() + i != rhs.end())
            return (true);
        return (false);
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
};

#endif
