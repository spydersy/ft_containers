
#ifndef __BIDIRECTIONAL_ITERATOR_HPP
# define __BIDIRECTIONAL_ITERATOR_HPP

# include "iterators_traits.hpp"
# include "iterator.hpp"
# include <iostream>
# include "../containers/map.hpp"
# include "avl_self_balancing_binary_search_tree_utils.hpp"



namespace ft
{
    template < typename TreeNode, class Type>
    class   bidirectional_iterator  : public ft::iterator_traits<ft::iterator<ft::bidirectional_iterator_tag, Type> >
    {
        private:
            typedef typename Type::first_type                            Key;
            typedef typename Type::second_type                           Value;
            // typedef typename TreeNode::key_type                       key_type;
            // typedef typename TreeNode::mapped_type                    mapped_type;
            // typedef typename ft::map<Key, value>::key_compare            key_compare;

            // typedef typename TreeNode::key_comapre                       key_comapre;
            // typedef TreeNode<Key, Value, key_compare>                    node;


            // node*   get_node() { return this->__ptr; }
        //  class bidirectional_iterator;

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

            // template < class AnotherNodeType, class AnotherType>
            bidirectional_iterator( const bidirectional_iterator& src)
            { this->__ptr = src.__ptr; }

            // bidirectional_iterator( const bidirectional_iterator& x )
            // {
            //     this->operator=(x);
            // }

            bidirectional_iterator( TreeNode* x )
            {
                this->__ptr = x;
            }

            // bidirectional_iterator( value_type &src ) : __ptr(&src) { return; }

            // bidirectional_iterator( const TreeNode n )
            // { this->__ptr = n; }

            bidirectional_iterator( void ) : __ptr(nullptr)
            { return; }

            ~bidirectional_iterator( void ) { return; }

            bidirectional_iterator    &operator=( bidirectional_iterator const & src)
            {
                if (this != &src)
                {
                // std::cout << "__DBG00__" << std::endl;
                    this->__ptr = src.__ptr;
                // std::cout << "__DBG01__" << std::endl;
                }
                return ( *this );
            }

            value_type *base() const { return this->__ptr; }


                template< class AnotherNodeType, class AnotherType>
                bool    operator==( bidirectional_iterator<AnotherNodeType, AnotherType> const & src ) const { return this->__ptr->__pair == src.__ptr->__pair; }

                template< class AnotherNodeType, class AnotherType>
                bool    operator!=( bidirectional_iterator<AnotherNodeType, AnotherType> const & src )
                {
                    return (this->__ptr != src.__ptr);
                }

            /*
            ** Incrementation / Decrementaion Operators:
            */
                /*
                ** Pre-increment opearator:
                */
                bidirectional_iterator    &operator++()
                {
                    // std::cout << "00 : ---------------------" << std::endl;
                    this->__ptr = this->__ptr->__next;
                    return (*this);
                }

                /*
                ** Post-increment opearator:
                */
                bidirectional_iterator    operator++( int )
                {
                    // std::cout << "01 : ---------------------" << std::endl;
                        bidirectional_iterator   prev = *this;

                        this->__ptr = this->__ptr->__next;
                        return (prev);
                }

                /*
                ** Pre-decrement opearator:
                */
                bidirectional_iterator    &operator--()
                {
                    this->__ptr = this->__ptr->get_prev_node();
                    return *this;
                }

                /*
                ** Post-decrement opearator:
                */
                bidirectional_iterator    operator--( int )
                {
                        bidirectional_iterator   prev = *this;

                        this->__ptr = this->__ptr->get_prev_node();
                        return prev;
                }

            /*
            ** Dereference Operators:
            */
                reference     operator*( void ) { return *this->__ptr->__pair; }
                pointer       operator->( void ) { return this->__ptr->__pair; }
                const pointer       operator->( void ) const { return this->__ptr->__pair; }

                // User Defined Conversion Function
                operator bidirectional_iterator<TreeNode,const Type>()
                {
                    return (bidirectional_iterator< TreeNode, const Type>(__ptr));
                }
        // private:
        public:
            TreeNode*     __ptr;
    };
}

#endif
