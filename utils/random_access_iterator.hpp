
#ifndef __RANDOM_ACCESS_ITERATOR_HPP__
# define __RANDOM_ACCESS_ITERATOR_HPP__

# include "iterators_traits.hpp"
# include "iterator.hpp"

namespace ft
{
    template <class T>
    class random_access_iterator : public ft::iterator_traits<ft::iterator<ft::random_access_iterator_tag, T> >
    {
        public:
        /*
         * Member Types ===========================================================================
        */        
            typedef typename ft::iterator_traits<ft::iterator<ft::random_access_iterator_tag, T> >::value_type        value_type;
            typedef typename ft::iterator_traits<ft::iterator<ft::random_access_iterator_tag, T> >::difference_type   difference_type;
            typedef typename ft::iterator_traits<ft::iterator<ft::random_access_iterator_tag, T> >::pointer           pointer;
            typedef typename ft::iterator_traits<ft::iterator<ft::random_access_iterator_tag, T> >::reference         reference;
            typedef typename ft::iterator_traits<ft::iterator<ft::random_access_iterator_tag, T> >::iterator_category iterator_category;
        
        private:
            pointer     _pointer;
        
        public:
        /*
         * Constructors & Destructor ==============================================================
        */
            // Default Constructor :
            random_access_iterator( void ) : _pointer(nullptr) {}
            // Copy Constructror :
            random_access_iterator (const random_access_iterator& x)
            {
                if (this != &x)
                    *this = x;
            }
            // Copy Assignment :
            random_access_iterator &operator=(const random_access_iterator& x)
            {
                if (this != &x)
                    this->_pointer = x._pointer;
                return *this;
            }
            // Destructor :
            ~random_access_iterator( void )
            {
                this->_pointer = nullptr;
                return ;
            }
        
        /*
         * Comparison Operators ===================================================================
        */
            // Equality Operator :
            bool    operator==(const random_access_iterator& x) const
            {
                return this->_pointer == x._pointer;
            }
            // Inequality Operator :
            bool    operator!=(const random_access_iterator& x) const
            {
                return this->_pointer != x._pointer;
            }
        
        /*
         * Dereferencing Operators ================================================================
        */
            // *it Operator :
            // it->m Operator :

        /*
         * Incrementation Operators ===============================================================
        */
            // Pre-increment Operator ++it : 
            random_access_iterator& operator++( void )
            {
                this->_pointer++;
                return *this;
            }
            // Post-increment Operator it++ :
            random_access_iterator& operator++( int )
            {
                random_access_iterator current(*this);
                //this++;
                return current;
            }
        /*
         * Decrementation Operators ===============================================================
        */
            // Pre-decrement Operator --it : 
            random_access_iterator& operator--( void )
            {
                this->_pointer--;
                return *this;
            }
            // Post-decrement Operator it-- :
            random_access_iterator& operator--( int )
            {
                random_access_iterator current(this);
                this--;
                return *current;
            }
        /*
         * Arithmetics Operations =================================================================
        */

        /*
         * Inequality Operations Operators ========================================================
        */
            // Operator < :
            bool    operator<(const random_access_iterator& x) const
            {
                return this->_pointer < x._pointer;
            }
            // Operator <= :
            bool    operator<=(const random_access_iterator& x) const
            {
                return this->_pointer <= x._pointer;
            }
            // Operator > :
            bool    operator>(const random_access_iterator& x) const
            {
                return this->_pointer > x._pointer;
            }
            // Operator >= :
            bool    operator>=(const random_access_iterator& x) const
            {
                return this->_pointer >= x._pointer;
            }
        /*
         * Compound Assignment Operators ==========================================================
        */

        };
}

#endif
