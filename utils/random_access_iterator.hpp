
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

                ~random_access_iterator() { return ; }

                bool    operator==( random_access_iterator const & src ) const
                {
                    return (this->_ptr == src._ptr);
                }

                bool    operator!=( random_access_iterator const & src ) const
                {
                    return (this->_ptr != src._ptr);
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

                difference_type   operator-(random_access_iterator const & src)
                {
                    random_access_iterator   ret;

                    // ret._ptr = this->_ptr - src._ptr;
                    // return (ret);
                    return (this->_ptr - src._ptr);
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

                bool    operator<( random_access_iterator const & src ) const
                {
                    return (this->_ptr < src._ptr);
                }

                bool    operator<=( random_access_iterator const & src ) const
                {
                    return (this->_ptr <= src._ptr);
                }

                bool    operator>( random_access_iterator const & src ) const
                {
                    return (this->_ptr > src._ptr);
                }

                bool    operator>=( random_access_iterator const & src ) const
                {
                    return (this->_ptr >= src._ptr);
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
                // operator    value_type() { return _ptr; }
                operator random_access_iterator<const Type>()
                {
                    return (random_access_iterator< const Type>(*_ptr));
                }

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
}

#endif