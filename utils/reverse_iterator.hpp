
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
            typedef Iterator                                                     iterator_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category    iterator_category;
            typedef typename ft::iterator_traits<Iterator>::value_type           value_type;
            typedef typename ft::iterator_traits<Iterator>::difference_type      difference_type;
            typedef typename ft::iterator_traits<Iterator>::pointer              pointer;
            typedef typename ft::iterator_traits<Iterator>::reference            reference;
        private:
            iterator_type   __it;
        public:
        /*
         * Member Functions =======================================================================
        */
            // Default Constructor :
            reverse_iterator( void ) : __it(nullptr)
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
                if (this != &other)
                {
                    this->__it = other.base();
                }
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
                return *this->__it;
            }
            // Operator -> :
            pointer operator->() const
            {
                return this->__it.operator->();
            }
        /*
         * Element by Index Accessor ==============================================================
        */
            // Operator [] :
            reference operator[]( difference_type n ) const
            {
                return this->__it.base[-n-1];
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
                this->__it--;
                return *this;
            }
            // Post-increment Operator rit++ :
            reverse_iterator operator++( int )
            {
                // reverse_iterator    prev(this);
                // this->__it--;
                // return prev;
                return reverse_iterator(this->_it--);
            }
            // Post-increment Operator rit-- :
            reverse_iterator operator--( int )
            {
                return reverse_iterator(this->_it++);
            }
            // Operator + :
            reverse_iterator operator+( difference_type n ) const
            {
                return reverse_iterator(this->__it - n);
            }
            // Operator - :
            reverse_iterator operator-( difference_type n ) const
            {
                return reverse_iterator(this->__it + n);
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
    bool operator==( const std::reverse_iterator<Iterator1>& lhs,
                    const std::reverse_iterator<Iterator2>& rhs )
    {
        return  lhs.base() == rhs.base();
    }

    template< class Iterator1, class Iterator2 >
    bool operator!=( const std::reverse_iterator<Iterator1>& lhs,
                    const std::reverse_iterator<Iterator2>& rhs )
    {
        return  lhs.base() != rhs.base();
    }

    template< class Iterator1, class Iterator2 >
    bool operator<( const std::reverse_iterator<Iterator1>& lhs,
                    const std::reverse_iterator<Iterator2>& rhs )
    {
        return lhs.base() > rhs.base();
    }

    template< class Iterator1, class Iterator2 >
    bool operator<=( const std::reverse_iterator<Iterator1>& lhs,
                    const std::reverse_iterator<Iterator2>& rhs )
    {
        return lhs.base() >= rhs.base();
    }


    template< class Iterator1, class Iterator2 >
    bool operator>( const std::reverse_iterator<Iterator1>& lhs,
                    const std::reverse_iterator<Iterator2>& rhs )
    {
        return lhs.base() < rhs.base();
    }

    template< class Iterator1, class Iterator2 >
    bool operator>=( const std::reverse_iterator<Iterator1>& lhs,
                    const std::reverse_iterator<Iterator2>& rhs )
    {
        return lhs.base() <= rhs.base();
    }
    // Operator + :
    template< class Iter >
    reverse_iterator<Iter>  operator+( typename ft::reverse_iterator<Iter>::difference_type n,
                            const ft::reverse_iterator<Iter>& it )
    {
        return reverse_iterator<Iter>(it - n);
    }

    template< class Iterator >
    typename reverse_iterator<Iterator>::difference_type
        operator-( const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs )
    {
        return reverse_iterator<Iterator>(lhs.base() - rhs.base());
    }
};  // Namespace ft

#endif
