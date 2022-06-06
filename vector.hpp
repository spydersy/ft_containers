
#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__ 

# include <iostream>
# include "utils/iterators_traits.hpp"
# include "utils/random_access_iterator.hpp"

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
        // Member Types :
        typedef T                                                       value_type;         // The first template parameter (T)	
        typedef std::allocator<value_type>                              allocator_type;     // The second template parameter (Alloc)	
        typedef value_type&                                             reference;          // Reference to value_type
        typedef const value_type&                                       const_reference;    // Const reference to value_type
        typedef value_type*                                             pointer;            // Pointer to value_type
        typedef const value_type*                                       const_pointer;      // Const pointer to value_type
        typedef typename ft::random_access_iterator<value_type>         iterator;           // A random access iterator to value_type
        typedef typename ft::random_access_iterator<const value_type>   const_iterator;     // A random access iterator to const value_type	
        // typedef const_reverse_iterator	reverse_iterator<const_iterator>	
        // typedef difference_type iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
        typedef std::size_t                                             size_type;          // An unsigned integral type that can represent any non-negative value of difference_type

        private:
            pointer         __array;
            size_type       __size;
            size_type       __capacity;
            allocator_type  __allocator;

        public:
        /*
         * Member Types =======================================================================
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
            // template <class InputIterator>
            //         vector (InputIterator first, InputIterator last,
            //                 const allocator_type& alloc = allocator_type())
            // {
            //     this->__size = 0;
            //     this->__capacity = last - first;
            //     this->__allocator = alloc;
            //     this->__array = nullptr;
            //     if (this->__capacity)
            //         this->__array = this->__allocator.allocate(this->__capacity);
            //     while (first != last)
            //     {
            //         this->__allocator.construct(this->__array + __size, first);
            //         first++;
            //     }
            //     this->__size = this->__capacity;
            // }
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

        /*
         * Iterators ==============================================================================
        */
            // Begin :
            iterator begin()
            {
                iterator it;
                return it;
            }
            // Const Begin :
            const_iterator begin() const
            {
                const_iterator cit;
                return cit;
            }

    };
};

#endif
