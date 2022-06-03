
#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__ 

# include <iostream>
# include "utils/iterators_traits.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
        // Member Types :
        typedef T                               value_type;
        typedef std::allocator<value_type>      allocator_type;
        typedef value_type&                     reference;
        typedef const value_type&               const_reference;
        typedef value_type*                     pointer;
        typedef const value_type*               const_pointer;

        // typedef iterator	a random access iterator to value_type	convertible to const_iterator
        // typedef const_iterator	a random access iterator to const value_type	
        // typedef reverse_iterator	reverse_iterator<iterator>	
        // typedef const_reverse_iterator	reverse_iterator<const_iterator>	
        // typedef difference_type iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
        // typedef size_type	an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t

        private:
            T*              __array;
            size_t          __size;
            size_t          __capacity;
            allocator_type  __allocator;

        public:
            // Default Constructor :
            explicit vector (const allocator_type& alloc = allocator_type())
            {
                this->__array = nullptr;
                this->__size = 0;
                this->__capacity = 0;
                this->__allocator = alloc;
            }
            // Fill Constructor :
            explicit vector (size_t n, const value_type& val = value_type(),
                            const allocator_type& alloc = allocator_type())
            {
                this->__size = 0;
                this->__allocator = alloc;                
                this->__array = this->__allocator.allocate(n);
                this->__capacity = n;

                for (size_t i = 0; i != n; i++)
                    this->__allocator.construct(this->__array + i, val);
            }

            // Range Constructor : 
            template <class InputIterator>
                    vector (InputIterator first, InputIterator last,
                            const allocator_type& alloc = allocator_type())
            {
                this->__size = 0;
                this->__capacity = last - first;
                this->__allocator = alloc;
                this->__array = nullptr;
                if (this->__capacity)
                    this->__array = this->__allocator.allocate(this->__capacity);
                while (first != last)
                {
                    this->__allocator.construct(this->__array + __size, first);
                    first++;
                }
                this->__size = this->__capacity;
            }

            // Copy Constructor :
            vector (const vector& x)
            {
                if (this != &x)
                {
                    this->__array = nullptr;
                    this->__size = x.__size;
                    this->__capacity = x.__capacity;
                    this->__allocator = x.__allocator;

                    if (this->__capacity)
                        this->__array = this->__allocator.allocate(this->__capacity);
                    for (size_t i = 0; i != x.__size; i++)
                        this->__allocator.construct(this->__array + i, x[i]);
                }
            }

            // Destructor : 
            ~vector()
            {
                for (size_t i = 0; i != this->__size; i++)
                    this->__allocator.destroy(this->__array + i);
                this->__size = 0;
                if (this->__capacity)
                    this->__allocator.deallocate(this->__array, this->__capacity);
                this->__capacity = 0;
                this->__array = nullptr;
            }

            // Operator= :
            // vector& operator= (const vector& x)
            // {
            //     if (this != &x)
            //     {
            //         if (this->__capacity)
            //     }
            // }

            // // Begin :
            // iterator begin()
            // {

            // }

            // // Const Begin :
            // const_iterator begin() const
            // {

            // }

    };
};

#endif
