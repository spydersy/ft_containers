
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
        node*    append_node(node** node_it, node** parent_it, int node_position, value_type pair)
        {
            *node_it = new node(pair, node_position);
            (*node_it)->__parent = *parent_it;

            if (node_position == LEFT_NODE)
                return (*parent_it)->__left = *node_it;
            else
                return (*parent_it)->__right = *node_it;
        }

        void    balance_tree( node* inserted_node )
        {
            std::cerr << KRED << "BALANCE_TREE_INPUT : **********************************" << KNRM << std::endl;
            std::cerr << "PARENT   : [" << inserted_node->__parent << "]" << std::endl;
            std::cerr << "LEFT     : [" << inserted_node->__left << "]" << std::endl;
            std::cerr << "RIGHTT   : [" << inserted_node->__right << "]" << std::endl;
            std::cerr << "PAIR     : [" << inserted_node->__pair.first << " | " << inserted_node->__pair.second << "]" << std::endl;
            std::cerr << "POSITION : [" << inserted_node->__position << "]" << std::endl;
            std::cerr << KRED << "*******************************************************" << KNRM << std::endl;
        }

        void insert( value_type pair )
        {
            node*   node_it = __root;
            node*   parent_it = __root;
            int     node_position = 0;

            if (__root == NULL)
            {
                __root = new node(pair, ROOT_NODE);
                __root->__parent = __root;
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
                this->balance_tree(append_node(&node_it, &parent_it, node_position, pair));
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