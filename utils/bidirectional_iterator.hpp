
#ifndef __BIDIRECTIONAL_ITERATOR_HPP
# define __BIDIRECTIONAL_ITERATOR_HPP

# include "iterators_traits.hpp"
# include "iterator.hpp"
# include "avl_self_balancing_binary_search_tree.hpp"

namespace ft
{
    template <typename Type>
    class   bidirectional_iterator  : public ft::iterator_traits<ft::iterator<ft::bidirectional_iterator_tag, Type> >
    {
        private:
            typedef typename Type::first_type                         Key;
            typedef typename Type::second_type                        Value;
            typedef avl_sbbst::TreeNode<Key, Value, std::less<Key> >  node;

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


            // template< class InputIterator>
            // bidirectional_iterator( InputIterator const & src ) : __node(src.node),
            //                                                       __ptr(src.__ptr)
            // { return; }

            template< class AnotherType>
            bidirectional_iterator( const bidirectional_iterator<AnotherType, Value, avl_sbbst::TreeNode<AnotherType, Value, std::less<AnotherType> > >& src) : __node(src.node),
                                                                                      __ptr(src.ptr)
            { return; }

            // bidirectional_iterator( pointer x ) : __ptr(x) { return; }
            // bidirectional_iterator( value_type &src ) : __ptr(&src) { return; }

            bidirectional_iterator( node* n )
            {
                this->__node = n;
                this->__ptr = n->get_pair();
            }

            bidirectional_iterator( void ) : __ptr(nullptr),
                                             __node(nullptr)
            { return; }

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
                    return *this;
                }

                /*
                ** Post-decrement opearator:
                */
                bidirectional_iterator    operator--( int )
                {
                        bidirectional_iterator   prev = *this;

                        this->__ptr--;
                        return prev;
                }

            /*
            ** Dereference Operators:
            */
                reference   operator*( void ) { return *(this->__ptr); }
                Type*       operator->( void ) { return this->__node->__pair; }

        private:
            pointer     __ptr;
            node*  __node;
    };
}

#endif
