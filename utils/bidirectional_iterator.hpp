
#ifndef __BIDIRECTIONAL_ITERATOR_HPP
# define __BIDIRECTIONAL_ITERATOR_HPP

# include "iterators_traits.hpp"
# include "iterator.hpp"


namespace ft
{
    template <typename Type>
    class   bidirectional_iterator  : public ft::iterator_traits<ft::iterator<ft::bidirectional_iterator_tag, Type> >
    {
        public:

            /*
            ** Member Types:
            */
            typedef typename ft::iterator_traits<ft::iterator<ft::bidirectional_iterator_tag, Type> >::value_type        value_type;
            typedef typename ft::iterator_traits<ft::iterator<ft::bidirectional_iterator_tag, Type> >::difference_type   difference_type;
            typedef typename ft::iterator_traits<ft::iterator<ft::bidirectional_iterator_tag, Type> >::pointer           pointer;
            typedef typename ft::iterator_traits<ft::iterator<ft::bidirectional_iterator_tag, Type> >::reference         reference;
            typedef typename ft::iterator_traits<ft::iterator<ft::bidirectional_iterator_tag, Type> >::iterator_category iterator_category;
            typedef          size_t                                                                                      size_type;


            bidirectional_iterator( void ) : __ptr(NULL) { return; }
            bidirectional_iterator( bidirectional_iterator const & src ) : __ptr(src.__ptr) {return; }
            bidirectional_iterator( pointer x ) : __ptr(x) { return; }
            bidirectional_iterator( value_type &src ) : __ptr(&src) { return; }
            ~bidirectional_iterator( void ) { return; }

            bidirectional_iterator    &operator=( bidirectional_iterator const & src)
            {
                this->__ptr = src.__ptr;
                return ( *this );
            }

                value_type *base() const { return this->__ptr; }


                template <typename U>
                bool    operator==( bidirectional_iterator<U> const & src ) const { return this->base() == src.base();}

                template <typename U>
                bool    operator!=( bidirectional_iterator<U> const & src )
                {
                    return (this->base() != src.base());
                }

            /*
            ** Incrementation / Decrementaion Operators:
            */
                /*
                ** Pre-increment opearator:
                */
                bidirectional_iterator    &operator++()
                {
                    this->__ptr++;
                    return (*this);
                }

                /*
                ** Post-increment opearator:
                */
                bidirectional_iterator    operator++( int )
                {
                        bidirectional_iterator   prev = *this;

                        this->__ptr++;
                        return (prev);
                }

                /*
                ** Pre-decrement opearator:
                */
                bidirectional_iterator    &operator--()
                {
                    this->__ptr--;
                    return (*this);
                }

                /*
                ** Post-decrement opearator:
                */
                bidirectional_iterator    operator--( int )
                {
                        bidirectional_iterator   prev = *this;

                        this->__ptr--;
                        return (prev);
                }

            /*
            ** Dereference Operators:
            */
                reference   operator*( void )
                {
                    return (*(this->__ptr));
                }

                pointer   operator->( void )
                {
                    return (this->__ptr);
                }

                // // User Defined Conversion Function
                // operator bidirectional_iterator<const Type>()
                // {
                //     return (bidirectional_iterator< const Type>(*__ptr));
                // }
        private:
            value_type    *__ptr;
    };
}

#endif
