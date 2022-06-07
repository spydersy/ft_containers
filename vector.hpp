
#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

# include <iostream>

# include "utils/iterators_traits.hpp"
# include "utils/random_access_iterator.hpp"
# include "utils/reverse_iterator.hpp"
# include "utils/enable_if.hpp"
# include "utils/is_integral.hpp"
# include "utils/distance.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
        // Member Types :
        typedef T                                                       value_type;             // The first template parameter (T)
        typedef std::allocator<value_type>                              allocator_type;         // The second template parameter (Alloc)
        typedef value_type&                                             reference;              // Reference to value_type
        typedef const value_type&                                       const_reference;        // Const reference to value_type
        typedef value_type*                                             pointer;                // Pointer to value_type
        typedef const value_type*                                       const_pointer;          // Const pointer to value_type
        typedef typename ft::random_access_iterator<value_type>         iterator;               // A random access iterator to value_type
        typedef typename ft::random_access_iterator<const value_type>   const_iterator;         // A random access iterator to const value_type
        typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;	    //
        typedef typename ft::reverse_iterator<const_iterator>           const_reverse_iterator;	//
        typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;        // Usually the same as ptrdiff_t
        typedef std::size_t                                             size_type;              // An unsigned integral type that can represent any non-negative value of difference_type

        private:
            pointer         __array;
            size_type       __size;
            size_type       __capacity;
            allocator_type  __allocator;

        public:
        /*
         * Constructors & Destructor ==============================================================
        */
            // Default Constructor :
            explicit vector (const allocator_type& alloc = allocator_type())
            {
                this->__array = nullptr;
                this->__size = 0;
                this->__capacity = 0;
                this->__allocator = alloc;
            }
            // Fill Constructor :
            explicit vector (size_type n, const value_type& val = value_type(),
                            const allocator_type& alloc = allocator_type())
            {
                this->__size = 0;
                this->__allocator = alloc;
                this->__array = this->__allocator.allocate(n);
                this->__capacity = n;

                for (size_type i = 0; i != n; i++)
                    this->__allocator.construct(this->__array + i, val);
            }
            // Range Constructor :
            template <class InputIterator>
            vector (InputIterator first, InputIterator last,
                    const allocator_type& alloc = allocator_type(),
                    typename ft::enable_if< !ft::is_integral<InputIterator>::value,
                    InputIterator>::type = InputIterator())
            {
                this->__size = 0;
                this->__capacity = ft::distance(first , last);
                this->__allocator = alloc;
                this->__array = nullptr;
                if (this->__capacity)
                    this->__array = this->__allocator.allocate(this->__capacity);
                while (first != last)
                {
                    this->__allocator.construct(this->__array + this->__size, first);
                    first++;
                    this->__size++;
                }
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
                    for (size_type i = 0; i != x.__size; i++)
                        this->__allocator.construct(this->__array + i, x[i]);
                }
            }
            // Destructor :
            ~vector()
            {
                for (size_type i = 0; i != this->__size; i++)
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

        /*
         * Iterators ==============================================================================
        */
            // Begin :
            iterator begin()
            {
                return iterator(&this->__array[0]);
            }
            // Const Begin :
            const_iterator begin() const
            {
                return const_iterator(&this->__array[0]);
            }
            // End :
            iterator end()
            {
                return iterator(&this->__array[this->__size]);
            }
            // Const End :
            const_iterator end() const
            {
                return const_iterator(&this->__array[this->__size]);
            }
            // Rbegin :
            reverse_iterator rbegin()
            {
                return reverse_iterator(this->end());
            }
            // Const Rbegin :
            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(this->end());
            }
            // Rend :
            reverse_iterator rend()
            {
                return reverse_iterator(this->begin());
            }
            // Const Rend :
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(this->begin());
            }
    };      // Class vector
};  // Namespace ft

#endif
