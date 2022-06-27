
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
        typedef ft::pair<const Key, T>           value_type;
        typedef TreeNode<Key, T, Compare, Alloc> node;
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
        node*   get_root( void ) const { return this->__root; }

    /*
    ** Methods :
    */
        // node*   get_previous_node( node* current )  // For iterator operator--() && operator--(int)
        // {
        // }

        // node*   get_next_node( node* current ) // For iterator operator++() && operator++(int)
        // {
        // }

        node* get_symmetrical_sutree( node* sutree )
        {
            if (sutree->__position == LEFT_NODE)
                return sutree->__parent->__right;
            else if (sutree->__position == RIGHT_NODE)
                return sutree->__parent->__left;
            else
                return sutree;
        }

        node*    append_node(node** node_it, node** parent_it, int node_position, value_type pair)
        {
            *node_it = new node(pair, node_position);
            (*node_it)->__parent = *parent_it;

            if (node_position == LEFT_NODE)
                return (*parent_it)->__left = *node_it;
            else
                return (*parent_it)->__right = *node_it;
        }

        bool    balance_factor(node* node1)
        {
            int     diff = node1->__index;
            node*   node2 = nullptr;

            if (node1->__index == LEFT_NODE)
                node2 = node1->__parent->get_right();
            else if (node1->__index == RIGHT_NODE)
                node2 = node1->__parent->get_left();

            if (node2 != nullptr)
                diff = node1->__index - node2->__index;
            return (-1 <= diff && diff <= 1);
        }

        // node*   left_right_rotation( node* child_node )
        // {
        //     left_rotation(child_node);
        //     //right_rotation(child_node);
        // }

        // node*   right_left_rotation( node* child_node )
        // {
        //     right_rotation(child_node);
        //     // left_rotation(child_node);
        // }

        // node*   left_rotation( node* parent_node )
        // {
        // }

        // node*   right_rotation( node* parent_node )
        // {
        // }

        void    do_some_magic( node* child_node )
        {
            int childe_position = child_node->__position;
            int parent_position = child_node->__parent->__position;

            std::cerr << "__DO_SOME_MAGIC__CHECK__ : " << childe_position << " | " << parent_position << std::endl;

            if (childe_position == LEFT_NODE && childe_position == parent_position)
            {
                std::cerr << "__DO_SOME_MAGIC__ : " << "__LEFT_ROTATION__" << std::endl;
            }
            else if (childe_position == RIGHT_NODE && childe_position == parent_position)
            {
                std::cerr << "__DO_SOME_MAGIC__ : " << "__RIGHT_ROTATION__" << std::endl;
            }
        }

        void    balance_tree( node* inserted_node )
        {
            node*   node_it = inserted_node;
            while (node_it != node_it->__parent)
            {
                if (node_it != inserted_node)
                {
                    node_it->__index++;
                    if (get_symmetrical_sutree(node_it)
                        && get_symmetrical_sutree(node_it)->__index
                            == node_it->__index - 1)
                    {
                        node_it->__index--;
                    }
                }
                // std::cerr << KMAG << "__TREE__IS__BALANCED__ : " << (balance_factor(node_it) == true ? "__TRUE__" : "__FALSE__") << KNRM << std::endl;
                if (balance_factor(node_it) == false)
                {
                    do_some_magic(node_it);
                }
                std::cout << "NODE_INDEX ************************************ : " << node_it->__index << std::endl;;
                node_it = node_it->__parent;
            }
            std::cerr << KRED << "BALANCE_TREE_INPUT : **********************************" << KNRM << std::endl;
            std::cerr << "PARENT   : [" << inserted_node->__parent << "]" << std::endl;
            std::cerr << "LEFT     : [" << inserted_node->__left << "]" << std::endl;
            std::cerr << "RIGHTT   : [" << inserted_node->__right << "]" << std::endl;
            std::cerr << "PAIR     : [" << inserted_node->__pair.first << " | " << inserted_node->__pair.second << "]" << std::endl;
            std::cerr << "POSITION : [" << inserted_node->__position << "]" << std::endl;
            std::cerr << "INDEX    : [" << inserted_node->__index << "]" << std::endl;
            std::cerr << "THIS     : [" << inserted_node << "]" << std::endl;
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
                balance_tree(__root);
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