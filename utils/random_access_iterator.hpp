
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
            pointer     __pointer;

        public:
        /*
         * Constructors & Destructor ==============================================================
        */
            // Default Constructor :
            random_access_iterator( void ) : __pointer(nullptr) { return ; }
            // Address Constructor :
            random_access_iterator( pointer ptr ) : __pointer(ptr) { return ; }
            // Copy Constructror :
            random_access_iterator ( const random_access_iterator& x )
            {
                if (this != &x)
                    *this = x;
            }
            // Copy Assignment :
            random_access_iterator &operator=( const random_access_iterator& x )
            {
                if (this != &x)
                    this->__pointer = x.__pointer;
                return *this;
            }
            // Destructor :
            ~random_access_iterator( void )
            {
                this->__pointer = nullptr;
                return ;
            }

        /*
         * Comparison Operators ===================================================================
        */
            // Equality Operator :
            bool    operator==( const random_access_iterator& x ) const
            {
                return this->__pointer == x.__pointer;
            }
            // Inequality Operator :
            bool    operator!=( const random_access_iterator& x ) const
            {
                return this->__pointer != x.__pointer;
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
            random_access_iterator& operator++( void ) const
            {
                this->__pointer++;
                return *this;
            }
            // Post-increment Operator it++ :
            random_access_iterator& operator++( int ) const
            {
                random_access_iterator current(this);
                this->__pointer++;
                return current;
            }
        /*
         * Decrementation Operators ===============================================================
        */
            // Pre-decrement Operator --it :
            random_access_iterator& operator--( void ) const
            {
                this->__pointer--;
                return *this;
            }
            // Post-decrement Operator it-- :
            random_access_iterator& operator--( int ) const
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
            bool    operator<( const random_access_iterator& x ) const
            {
                return this->__pointer < x.__pointer;
            }
            // Operator <= :
            bool    operator<=( const random_access_iterator& x ) const
            {
                return this->__pointer <= x.__pointer;
            }
            // Operator > :
            bool    operator>( const random_access_iterator& x ) const
            {
                return this->__pointer > x.__pointer;
            }
            // Operator >= :
            bool    operator>=( const random_access_iterator& x ) const
            {
                return this->__pointer >= x.__pointer;
            }
        /*
         * Compound Assignment Operators ==========================================================
        */
            // Operator += :
            random_access_iterator& operator+=( int n ) const
            {
                this->__pointer += n;
                return *this;
            }
            // Operator -= :
            random_access_iterator& operator-=( int n ) const
            {
                this->__pointer -= n;
                return *this;
            }
        /*
         * Offset Dereference Operator ============================================================
        */
            // Operator [] :
            pointer operator[]( int n ) const
            {
                return this->__pointer + n;
            }
        };
}

#endif
