
#ifndef __SELF_BALANCED_BINARY_SEARCH_TREE__
# define __SELF_BALANCED_BINARY_SEARCH_TREE__

# include "self_balanced_binary_search_tree_utils.hpp"

namespace sbbst
{
    // class TreeNode;

    template < class Key,                                              // ft::map::key_type
               class T,                                                // ft::map::mapped_type
               class Compare = std::less<Key>,                         // ft::map::key_compare
               class Alloc = std::allocator<ft::pair<const Key,T> > >  // ft::map::allocator_type
    class sbbst
    {
    /*
    ** Member Types :
    */
    public:
        typedef ft::pair<const Key, T>                     value_type;
        typedef TreeNode<Key, T, Compare, Alloc>    node;
    private:
        size_t  __size;
        node*   __root;
    public:
    /*
    ** Canonical Form :
    */
        sbbst( void ) : __size(0),
                        __root(nullptr)
        { std::cout << KBLU << "__SBBST__DEFAULT__CONSTRUCTOR__CALLED__" << KNRM << std::endl; }

        sbbst( const sbbst & src );
        sbbst&  operator=( const sbbst & src );

        ~sbbst( void )
        { std::cout << KBLU << "__SBBST__DESTRUCTOR__CALLED__" << KNRM << std::endl; }

    /*
    ** Getters :
    */
        node*   get_root() const { return this->__root; }

    /*
    ** Methods :
    */
        void insert(value_type pair)
        {
            node*   node_it = __root;
            node*   parent_it = __root;
            int     node_position = 0;

            if (__root == NULL)
            {
                __root = new node(pair);
                return ;
            }
            else
            {
                while (node_it != NULL)
                {
                    if (pair.first == node_it->get_pair().first)
                    {
                        std::cout << "Duplicated Element" << std::endl;
                        return ;
                    }
                    else if (pair.first < node_it->get_pair().first)
                    {
                        std::cout << KYEL << "<< TO_LEFT" << KNRM << std::endl;
                        parent_it = node_it;
                        node_it = node_it->get_left();
                        node_position = LEFT_NODE;
                    }
                    else if (pair.first > node_it->get_pair().first)
                    {
                        std::cout << KYEL << ">> TO_RIGHT" << KNRM << std::endl;
                        parent_it = node_it;
                        node_it = node_it->get_right();
                        node_position = RIGHT_NODE;
                    }
                }
                node_it = new node(pair);
                if (node_position == LEFT_NODE)
                    parent_it->__left = node_it;
                else if (node_position == RIGHT_NODE)
                    parent_it->__right = node_it;
            }
        }
    }; // class sbbst
} // namespace sbbst


// //single element (1)
// pair<iterator,bool> insert (const value_type& val);

// //with hint (2)
// iterator insert (iterator position, const value_type& val);

// //range (3)
// template <class InputIterator>
//   void insert (InputIterator first, InputIterator last);

#endif