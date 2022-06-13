
#ifndef __REVERSE_ITERATOR_HPP__
# define __REVERSE_ITERATOR_HPP__

# include "random_access_iterator.hpp"

namespace ft
{
    template <class Iterator>
    class reverse_iterator
    {
        public:
        /*
         * Member Types ===========================================================================
        */
            typedef Iterator                                  iterator_type;
            typedef typename iterator_type::iterator_category iterator_category;
            typedef typename iterator_type::value_type        value_type;
            typedef typename iterator_type::difference_type   difference_type;
            typedef typename iterator_type::pointer           pointer;
            typedef typename iterator_type::reference         reference;
        private:
            iterator_type   __it;
        public:
        /*
         * Member Functions =======================================================================
        */
            // Default Constructor :
            reverse_iterator( void )
            {
                return ;
            }
            // Initialization Constructor :
            explicit reverse_iterator ( iterator_type it ) : __it(it)
            {
                return ;
            }
            // Copy / Type-Cast Constructor :
            template <class Iter>
            reverse_iterator (const reverse_iterator<Iter>& rev_it) : __it(rev_it.base())
            {
                return ;
            }
        /*
         * Assignment Operator ====================================================================
        */
            // Operator = :
            template< class U >
            reverse_iterator& operator=( const reverse_iterator<U>& other )
            {
                this->__it = other.base();
                return *this;
            }
        /*
         * Underlying Iterator Accessor ===========================================================
        */
            // Base :
            iterator_type base( void ) const
            {
                return this->__it;
            }
        /*
         * Pointed-to Element Accessor ============================================================
        */
            // Operator * :
            reference operator*() const
            {
                iterator_type ret(__it);
                return *--ret;
            }
            // Operator -> :
            pointer operator->() const
            {
                return (this->base() - 1).operator->();
            }
        /*
         * Element by Index Accessor ==============================================================
        */
            // Operator [] :
            reference operator[]( difference_type n ) const
            {
                return this->base()[-n - 1];
            }
        /*
         * Advances & Decrements the iterator =====================================================
        */
            // Pre-increment Operator ++rit :
            reverse_iterator& operator++()
            {
                this->__it--;
                return *this;
            }
            // Pre-increment Operator --rit :
            reverse_iterator& operator--()
            {
                this->__it++;
                return *this;
            }
            // Post-increment Operator rit++ :
            reverse_iterator operator++( int )
            {
                reverse_iterator    prev = *this;

                this->__it--;
                return (prev);

            }
            // Post-increment Operator rit-- :
            reverse_iterator operator--( int )
            {
                reverse_iterator    prev = *this;

                this->__it++;
                return (prev);
            }
            // Operator + :
            reverse_iterator operator+( difference_type n ) const
            {
                reverse_iterator    ret;

                ret.__it = (this->base() - n);
                return (ret);
            }
            // Operator - :
            reverse_iterator operator-( difference_type n ) const
            {
                reverse_iterator    ret;

                ret.__it = (this->base() + n);
                return (ret);
            }
            // Operator += :
            reverse_iterator& operator+=( difference_type n )
            {
                this->__it -= n;
                return *this;
            }
            // Operator -= :
            reverse_iterator& operator-=( difference_type n )
            {
                this->__it += n;
                return *this;
            }
    };      // Class reverse_iterator

    /*
     * Non-Member Functions =======================================================================
    */

    template< class Iterator1, class Iterator2 >
    bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs )
    {
        return (lhs.base() == rhs.base());
    }

    template< class Iter >
    reverse_iterator<Iter>
        operator+( typename reverse_iterator<Iter>::difference_type n,
                    const reverse_iterator<Iter>& it )
    {
        reverse_iterator<Iter>  ret(it);

        ret += n;
        return (ret);
    }

    template< class Iterator >
    typename reverse_iterator<Iterator>::difference_type
        operator-( const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs )
    {
        return (rhs.base() - lhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs )
    {
        return (lhs.base() != rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs )
    {
        return (!(lhs.base() < rhs.base()));
    }

    template< class Iterator1, class Iterator2 >
    bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs )
    {
        return (!(lhs.base() <= rhs.base()));
    }

    template< class Iterator1, class Iterator2 >
    bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs )
    {
        return (!(lhs.base() > rhs.base()));
    }

    template< class Iterator1, class Iterator2 >
    bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
                    const ft::reverse_iterator<Iterator2>& rhs )
    {
        return (!(lhs.base() >= rhs.base()));
    }
};  // Namespace ft

#endif
