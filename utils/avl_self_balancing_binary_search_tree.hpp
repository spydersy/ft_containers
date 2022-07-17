
#ifndef __AVL_SELF_BALANCING_BINARY_SEARCH_TREE__
# define __AVL_SELF_BALANCING_BINARY_SEARCH_TREE__

# include "avl_self_balancing_binary_search_tree_utils.hpp"

namespace avl_sbbst
{
    // class TreeNode;

    template < class Key,                                              // ft::map::key_type
               class T,                                                // ft::map::mapped_type
               class Compare = std::less<Key>,                         // ft::map::key_compare
               class Alloc = std::allocator<ft::pair<const Key,T> > >  // ft::map::allocator_type
    class avl_sbbst
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
        avl_sbbst( void ) : __size(0),
                        __root(nullptr)
        { /*std::cout << KBLU << "__avl_SBBST__DEFAULT__CONSTRUCTOR__CALLED__" << KNRM << std::endl;*/ }

        avl_sbbst( const avl_sbbst & src );
        avl_sbbst&  operator=( const avl_sbbst & src );

        ~avl_sbbst( void )
        { /*std::cout << KBLU << "__avl_SBBST__DESTRUCTOR__CALLED__" << KNRM << std::endl; */}

    /*
    ** Getters :
    */
        node*   get_root( void ) const { return this->__root; }

        node*   get_left_most_node() const
        {
            node*   it = this->__root;

           if (it == nullptr)
                return it;
            while (it->__left != nullptr)
                it = it->__left;
            return it;
        }

        node*   get_right_most_node() const
        {
            node*   it = this->__root;
            if (it == nullptr)
                return it;
            while (it != nullptr)
                it = it->__right;
            return it->__parent;
        }

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
            if (sutree == nullptr)
                return nullptr;
            if (sutree->__position == LEFT_NODE)
            {
                return sutree->__parent->__right;
            }
            else if (sutree->__position == RIGHT_NODE)
            {
                return sutree->__parent->__left;
            }
            else
            {
                return sutree;
            }
        }

        node*    append_node(node** node_it, node** parent_it, int node_position, value_type pair)
        {
            *node_it = new node(pair, node_position);
            (*node_it)->__parent = *parent_it;

            this->__size++;
            if (node_position == LEFT_NODE)
                return (*parent_it)->__left = *node_it;
            else
                return (*parent_it)->__right = *node_it;
        }

        node*   get_non_null_child(node* parent)
        {
            if (parent->__left != nullptr)
                return parent->__left;
            if (parent->__right != nullptr)
                return parent->__right;
            return nullptr;
        }

        int balance_factor_value(node* node1)
        {
            node*   node2 = get_symmetrical_sutree(node1);

            if (node1 != nullptr && node2 == nullptr)
                return node1->__index;
            if (node1 == nullptr && node2 != nullptr)
                return node2->__index;
            if (node1 == nullptr && node2 == nullptr)
                return 0;
            return node1->__index - node2->__index;
        }

        bool    balance_factor_bool(node* node1)
        {
            int     diff = node1->__index;
            node*   node2 = get_symmetrical_sutree(node1);

            if (node2 != nullptr)
                diff = node1->__index - node2->__index;
            return (-1 <= diff && diff <= 1);
        }

        /* ************************************************************************************ *
         *                                                                                      *
         *  T1, T2, T3 and T4 are subtrees.                                                     *
         *                                                                                      *
         *             Z                                                      Y                 *
         *           /  \                                                   /  \                *
         *          /    \                                                 /    \               *
         *         /      \                                               /      \              *
         *        T1      Y                Left Rotate (z)               Z       X              *
         *               / \               =============>               / \     / \             *
         *              /   \                                          /   \   /   \            *
         *            T2    X                                         T1   T2 T3   T4           *
         *                 / \                                                                  *
         *                /   \                                                                 *
         *               T3   T4                                                                *
         *                                                                                      *
         * ************************************************************************************ */
        node*   left_rotation( node* z, bool CHANGE_INDEX )
        {
            node* y = z->__right;
            node* t2 = y->__left;

            if (t2)
            {
                t2->__parent = z;
                t2->__position = RIGHT_NODE;
            }
            if (z->__position == ROOT_NODE)
            {
                this->__root = y;
                y->__parent = y;
                y->__position = ROOT_NODE;
            }
            else
            {
                y->__parent = z->__parent;
                y->__position = z->__position;
                if (y->__position == LEFT_NODE)
                    z->__parent->__left = y;
                else
                    z->__parent->__right = y;
            }
            y->__left = z;
            z->__right = t2;
            std::cerr << "Z->PARENT : [" << z->__parent->__pair.first << "] | Y : [" << y->__pair.first << "]" << std::endl;
            z->__parent = y;
            z->__position = LEFT_NODE;
            if (CHANGE_INDEX)
                z->__index = y->__index - 1;
            return y;
        }

        /* ************************************************************************************ *
         *                                                                                      *
         *  T1, T2, T3 and T4 are subtrees.                                                     *
         *                                                                                      *
         *                   Z                                       Y                          *
         *                 /  \                                    /  \                         *
         *                /    \                                  /    \                        *
         *               /      \                                /      \                       *
         *              Y      T4       Right Rotate (z)        X       Z                       *
         *            /  \              =============>         / \     / \                      *
         *           /    \                                   /   \   /   \                     *
         *          X     T3                                 T1   T2 T3   T4                    *
         *         / \                                                                          *
         *        /   \                                                                         *
         *       T1   T2                                                                        *
         *                                                                                      *
         * ************************************************************************************ */
        node*   right_rotation( node* z, bool CHANGE_INDEX )
        {
            node* y = z->__left;
            node* t3 = y->__right;

            if (t3)
            {
                t3->__parent = z;
                t3->__position = LEFT_NODE;
            }
            if (z->__position == ROOT_NODE)
            {
                this->__root = y;
                y->__parent = y;
                y->__position = ROOT_NODE;
            }
            else
            {
                y->__parent = z->__parent;
                y->__position = z->__position;
                if (y->__position == LEFT_NODE)
                    z->__parent->__left = y;
                else
                    z->__parent->__right = y;
            }
            y->__right = z;
            z->__left = t3;
            z->__parent = y;
            z->__position = RIGHT_NODE;
            if (CHANGE_INDEX)
                z->__index = y->__index - 1;
            return y;
        }

        /* ************************************************************************************ *
         *                                                                                      *
         *  T1, T2, T3 and T4 are subtrees.                                                     *
         *                                                                                      *
         *           Z                             Z                               X            *
         *          / \                           / \                            /   \          *
         *         /   \                         /   \                          /     \         *
         *        Y    T4                       X    T4                        /       \        *
         *      /  \        Left Rotate (y)    / \       Right Rotate(z)      Y         Z       *
         *     /   \       =============>     /   \      =============>      / \       / \      *
         *    T1   X                         Y    T3                        /   \     /   \     *
         *        / \                       / \                            /     \   /     \    *
         *       /   \                     /   \                          T1    T2  T3     T4   *
         *      T2   T3                   T1   T2                                               *
         *                                                                                      *
         * ************************************************************************************ */
        void    left_right_rotation(node* y)
        {
            node* x = left_rotation(y, false);
            node* ret = right_rotation(x->__parent, false);

            int old_index = ret->__index;
            ret->__index = get_max_index_of_child(ret)->__index;

            if (ret->__left)
                ret->__left->__index = old_index;
            if (ret->__right)
                ret->__right->__index = old_index;
        }

        /* ************************************************************************************ *
         *                                                                                      *
         *  T1, T2, T3 and T4 are subtrees.                                                     *
         *                                                                                      *
         *       Z                              Z                                    X          *
         *     /  \                            / \                                 /   \        *
         *    /    \                          /   \                               /     \       *
         *   T1     Y                       T1     X                             /       \      *
         *         / \     Right Rotate(y)        / \      Left Rotate(z)       Z         Y     *
         *        /  \     =============>        /   \     =============>      / \       / \    *
         *       X   T4                         T2   Y                        /   \     /   \   *
         *      / \                                 / \                      /     \   /     \  *
         *     /   \                               /   \                    T1    T2  T3     T4 *
         *    T2   T3                             T3   T4                                       *
         *                                                                                      *
         * ************************************************************************************ */
        void    right_left_rotation(node* y)
        {
            int old_index;
            node* x = right_rotation(y, false);
            node* ret = left_rotation(x->__parent, false);

            old_index = ret->__index;
            ret->__index = get_max_index_of_child(ret)->__index;
            if (ret->__left)
                ret->__left->__index = old_index;
            if (ret->__right)
                ret->__right->__index = old_index;
        }

        void    do_some_magic( node* child_node, node* inserted_node )
        {
            int inserted_position = inserted_node->__position;
            int childe_position = child_node->__position;

            // Right rotation
            if ((childe_position == LEFT_NODE || childe_position == ROOT_NODE) && childe_position == inserted_position)
            {
                std::cerr << KGRN << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_RIGHT_-_ROTATION_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << KNRM << std::endl;
                right_rotation(child_node->__parent, true);
            }
            // Left rotation
            else if ((childe_position == RIGHT_NODE || childe_position == ROOT_NODE) && childe_position == inserted_position)
            {
                std::cerr << KGRN << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_LEFT_-_ROTATION_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << KNRM << std::endl;
                left_rotation(child_node->__parent, true);
            }
            // Right Left Rotation
            else if (inserted_position == LEFT_NODE && childe_position == RIGHT_NODE)
            {
                std::cerr << KGRN << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_RIGHT_-_LEFT_-_ROTATION_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << KNRM << std::endl;
                right_left_rotation(child_node);
            }
            // Left Right Rotation
            else if (inserted_position == RIGHT_NODE && childe_position == LEFT_NODE)
            {
                std::cerr << KGRN << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_LEFT_-_RIGHT_-_ROTATION_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << KNRM << std::endl;
                left_right_rotation(child_node);
            }
        }

        node*   get_max_index_of_child(node* n)
        {
            if (n->__left == nullptr && n->__right == nullptr)
                return nullptr;
            if (n->__left != nullptr && n->__right == nullptr)
                return n->__left;
            if (n->__left == nullptr && n->__right != nullptr)
                return n->__right;
            return n->__left->__index <= n->__right->__index ? n->__right : n->__left;
        }

        void    balance_tree( node** inserted_node )
        {
            node*   node_it = *inserted_node;

            while (*inserted_node != (*inserted_node)->__parent) // Only root_tree verify this condition aka [inserted_node = inserted_node->__parent]
            {
                if (*inserted_node != node_it)
                {
                    std::cerr << KRED << "___WAAAARNING___EXCEPTION___00 :: " << (*inserted_node)->__pair.first << KNRM << std::endl;
                    (*inserted_node)->__index++;
                    if (get_max_index_of_child(*inserted_node)
                    && (*inserted_node)->__index - get_max_index_of_child(*inserted_node)->__index > 1)
                    {
                        (*inserted_node)->__index--;
                        std::cerr << KCYN << "___WAAAARNING___EXCEPTION___00__________________ :: " << KNRM << std::endl;
                    }
                }
                if (this->balance_factor_bool(*inserted_node) == false)
                {
                    this->do_some_magic(*inserted_node, node_it);
                }
                // std::cout << "NODE_INDEX ************************************ : " << (*inserted_node)->__index << std::endl;;
                *inserted_node = (*inserted_node)->__parent;
                if (*inserted_node == (*inserted_node)->__parent && balance_factor_value(get_non_null_child(*inserted_node)) != 0)
                {
                    std::cerr << KRED << "___WAAAARNING___EXCEPTION___01 :: " << (*inserted_node)->__pair.first << KNRM << std::endl;
                    (*inserted_node)->__index++;
                    if (get_max_index_of_child(*inserted_node)
                    && (*inserted_node)->__index - get_max_index_of_child(*inserted_node)->__index > 1)
                    {
                        (*inserted_node)->__index--;
                        std::cerr << KCYN << "___WAAAARNING___EXCEPTION___01__________________ :: " << KNRM << std::endl;
                    }
                }
            }
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
                this->__root->__next = nullptr;
                this->__root->__prev = nullptr;
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
                node*   inserted_node = append_node(&node_it, &parent_it, node_position, pair);

                if (inserted_node->__pair.first == 12)
                {
                    std::cout << "";
                }

                if (inserted_node->__position == LEFT_NODE)
                {
                    std::cout << KYEL << "__SET__IN__LEFT__NODE__" << KNRM << std::endl;
                    inserted_node->__next = inserted_node->__parent;
                    inserted_node->__prev = inserted_node->__parent->__prev;

                    if (inserted_node->__prev)
                        inserted_node->__prev->__next = inserted_node;
                    inserted_node->__parent->__prev = inserted_node;
                }
                else
                {
                    std::cout << KGRN << "__SET__IN__RIGHT__NODE__" << KNRM << std::endl;
                    inserted_node->__prev = inserted_node->__parent;
                    inserted_node->__next = inserted_node->__parent->__next;

                    if (inserted_node->__next)
                        inserted_node->__next->__prev = inserted_node;
                    inserted_node->__parent->__next = inserted_node;
                }
                this->balance_tree(&inserted_node);
            }
        }
    }; // class avl_sbbst
} // namespace avl_sbbst

#endif

