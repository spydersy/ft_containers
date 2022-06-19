
#ifndef __RANDOM_ACCESS_ITERATOR_HPP__
# define __RANDOM_ACCESS_ITERATOR_HPP__

# include <iostream>
# include <iterator>

# include "iterators_traits.hpp"
# include "iterator.hpp"

namespace ft
{
    template <typename Type>
    class   random_access_iterator  : public ft::iterator_traits<ft::iterator<ft::random_access_iterator_tag, Type> >
    {
        public:

            /*
            ** Member Types:
            */
            typedef typename ft::iterator_traits<ft::iterator<ft::random_access_iterator_tag, Type> >::value_type        value_type;
            typedef typename ft::iterator_traits<ft::iterator<ft::random_access_iterator_tag, Type> >::difference_type   difference_type;
            typedef typename ft::iterator_traits<ft::iterator<ft::random_access_iterator_tag, Type> >::pointer           pointer;
            typedef typename ft::iterator_traits<ft::iterator<ft::random_access_iterator_tag, Type> >::reference         reference;
            typedef typename ft::iterator_traits<ft::iterator<ft::random_access_iterator_tag, Type> >::iterator_category iterator_category;
            typedef          size_t                                                                                      size_type;


                random_access_iterator( void )
                {
                    this->_ptr = NULL;
                }

                random_access_iterator( random_access_iterator const & src )
                {
                    this->_ptr = src._ptr;
                }

                random_access_iterator ( pointer x ) : _ptr(x) {}

                random_access_iterator( value_type &src )
                {
                    this->_ptr = &src;
                }

                random_access_iterator    &operator=( random_access_iterator const & src)
                {
                    this->_ptr = src._ptr;
                    return ( *this );
                }

                value_type *base() const
                {
                    return this->_ptr;
                }

                ~random_access_iterator() { return ; }

                template <typename U>
                bool    operator==( random_access_iterator<U> const & src ) const
                {
                    return (this->base() == src.base());
                }

                template <typename U>
                bool    operator!=( random_access_iterator<U> const & src )
                {
                    return (this->base() != src.base());
                }

            /*
            ** Incrementation / Decrementaion Operators:
            */
                /*
                ** Pre-increment opearator:
                */
                random_access_iterator    &operator++()
                {
                    this->_ptr++;
                    return (*this);
                }

                /*
                ** Post-increment opearator:
                */
                random_access_iterator    operator++( int )
                {
                        random_access_iterator   prev = *this;

                        this->_ptr++;
                        return (prev);
                }

                /*
                ** Pre-decrement opearator:
                */
                random_access_iterator    &operator--()
                {
                    this->_ptr--;
                    return (*this);
                }

                /*
                ** Post-decrement opearator:
                */
                random_access_iterator    operator--( int )
                {
                        random_access_iterator   prev = *this;

                        this->_ptr--;
                        return (prev);
                }

            /*
            ** Dereference Operators:
            */
                reference   operator*( void )
                {
                    return (*(this->_ptr));
                }

                pointer   operator->( void )
                {
                    return (this->_ptr);
                }

                // difference_type   operator-(random_access_iterator const & src)
                // {
                    // return (this->_ptr - src._ptr);
                // }

                template <typename U>
                difference_type    operator-( random_access_iterator<U> const & src ) const
                {
                    return this->base() - src.base();
                }

                random_access_iterator   operator-(size_type value)
                {
                    random_access_iterator   ret;

                    ret._ptr = this->_ptr - value;
                    return (ret);
                }

                random_access_iterator   operator+(size_type value)
                {
                    random_access_iterator   ret;

                    ret._ptr = this->_ptr + value;
                    return (ret);
                }

                template <typename U>
                bool    operator<( random_access_iterator<U> const & src ) const
                {
                    return (this->base() < src.base());
                }

                template <typename U>
                bool    operator<=( random_access_iterator<U> const & src ) const
                {
                    return this->base() <= src.base();
                }

                template <typename U>
                bool    operator>( random_access_iterator<U> const & src ) const
                {
                    return this->base() > src.base();
                }

                template <typename U>
                bool    operator>=( random_access_iterator<U> const & src ) const
                {
                    return this->base() >= src.base();
                }

                random_access_iterator operator+=( size_type const value)
                {
                    this->_ptr += value;
                    return (*this);
                }

                random_access_iterator   operator-=( size_type value)
                {
                    this->_ptr -= value;
                    return (*this);
                }

                reference   operator[]( size_type index ) const
                {
                    return (this->_ptr[index]);
                }

                // // User Defined Conversion Function
                // operator random_access_iterator<const Type>()
                // {
                //     return (random_access_iterator< const Type>(*_ptr));
                // }
        private:
            value_type    *_ptr;
    };

    template< typename Type>
    random_access_iterator<Type>   operator+(size_t value, const random_access_iterator<Type> & src)
    {
        random_access_iterator<Type>   ret(src);

        ret += value;
        return (ret);
    }

    template< typename Iterator1, typename Iterator2 >
    typename random_access_iterator<Iterator1>::difference_type
        operator-( const random_access_iterator<Iterator1>& lhs,
                    const random_access_iterator<Iterator2>& rhs )
    {
        return rhs.base() - lhs.base();
    }
}

#endif