
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
        { /*std::cout << KBLU << "__SBBST__DEFAULT__CONSTRUCTOR__CALLED__" << KNRM << std::endl;*/ }

        sbbst( const sbbst & src );
        sbbst&  operator=( const sbbst & src );

        ~sbbst( void )
        { /*std::cout << KBLU << "__SBBST__DESTRUCTOR__CALLED__" << KNRM << std::endl; */}

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

        bool    balance_factor(node* node1)
        {
            int     diff = node1->__index;
            node*   node2 = get_symmetrical_sutree(node1);

            if (node2 != nullptr)
                diff = node1->__index - node2->__index;
            return (-1 <= diff && diff <= 1);
        }

        node*   left_rotation( node* child_node, node* parent_node )
        {
            if (parent_node == parent_node->__parent)
            {
                std::cout << "__LEFT__ROTTION__CONDITION__00__ : ==================================== [" << parent_node->__pair.first << "] [" << child_node->__pair.first << "]" << std::endl;
                parent_node->__index = child_node->__index - 1;
                parent_node->__right = child_node->__left;
                parent_node->__parent = child_node;

                this->__root = child_node;
                child_node->__position = ROOT_NODE;
                child_node->__parent = child_node;
                this->__root->__left = parent_node;
                parent_node->__position = LEFT_NODE;
            }
            else
            {
                std::cout << "__LEFT__ROTTION__CONDITION__01__ : ==================================== [" << parent_node->__pair.first << "] [" << child_node->__pair.first << "]" << std::endl;
                child_node->__parent = parent_node->__parent;
                parent_node->__parent->__right = child_node;
                child_node->__left = parent_node;

                parent_node->__parent = child_node;
                parent_node->__right = nullptr;
                parent_node->__index = child_node->__index - 1;
            }
            return child_node;
        }

        node*   right_rotation( node* child_node, node* parent_node )
        {
            if (parent_node == parent_node->__parent)
            {
                std::cout << KRED << "__RIGHT__ROTTION__CONDITION__00__ : ==================================== [" << parent_node->__pair.first << "] [" << child_node->__pair.first << "]" << KNRM << std::endl;
                parent_node->__index = child_node->__index - 1;
                parent_node->__left = child_node->__right;
                parent_node->__parent = child_node;

                this->__root = child_node;
                child_node->__position = ROOT_NODE;
                child_node->__parent = child_node;
                this->__root->__right = parent_node;
                parent_node->__position = RIGHT_NODE;
            }
            else
            {
                std::cout << KRED << "__RIGHT__ROTTION__CONDITION__01__ : ==================================== [" << parent_node->__pair.first << "] [" << child_node->__pair.first << "]" << KNRM << std::endl;
                child_node->__parent = parent_node->__parent;
                parent_node->__parent->__right = child_node;
                child_node->__right = parent_node;
                child_node->__position = RIGHT_NODE;

                parent_node->__parent = child_node;
                parent_node->__left = nullptr;
                parent_node->__index = child_node->__index - 1;
            }
            return child_node;
        }

        void    left_right_rotation(node* n)
        {
            // node*   first_rotation = nullptr;
            std::cout << KRED << "__LEFT__RIGHT__ROTTION__CONDITION____ : ==================================== [" << n->__pair.first << "]" << KNRM << std::endl;
            // exit(12);
            // first_rotation = left_rotation(n, n->__parent);
            // std::cerr << KRED << "__CHECK__ROTATION__RETURN__ :: " << first_rotation->__pair.first << " || " << first_rotation->__parent->__pair.first << " || " << first_rotation->__right->__pair.first << KNRM << std::endl;
            // right_rotation(first_rotation, first_rotation->__parent);
        }

        void    right_left_rotation(node* n)
        {
            std::cout << KRED << "__RIGHT__LEFT__ROTTION__CONDITION____ : ==================================== [" << n->__pair.first << "]" << KNRM << std::endl;

            node*   parent1 = n->__parent;
            node*   parent2 = n->__parent->__parent;

            n->__right = parent1;
            n->__left = parent2;
            n->__index = 2;
            if (parent2 == parent2->__parent)
            {
                this->__root = n;
                n->__parent = n;
                n->__position = ROOT_NODE;
            }
            else
            {
                n->__parent = parent2->__parent;
                n->__position = parent2->__position;
            }
            parent1->__parent = n;
            parent2->__parent = n;

            parent1->__left = nullptr;
            parent1->__right = nullptr;
            parent1->__position = RIGHT_NODE;
            parent1->__index = n->__index - 1;

            parent2->__left = nullptr;
            parent2->__right = nullptr;
            parent2->__position = LEFT_NODE;
            parent2->__index = n->__index - 1;
        }

        void    do_some_magic( node* child_node, node* inserted_node )
        {
            int inserted_position = inserted_node->__position;
            int childe_position = child_node->__position;

            std::cerr << KBLU << "__DO__SOME__MAGIC__CALLED__" << KNRM << std::endl;
            std::cerr << KBLU << "__CHILD__POSITION__    : " << childe_position << KNRM << std::endl;
            std::cerr << KBLU << "__INSERTED__POSITION__ : " << inserted_position << KNRM << std::endl;
            std::cerr << KGRN << "============================================================================" << KNRM << std::endl;
            std::cerr << KGRN << "__CHILD__VALUE__    : " << child_node->__pair.first << KNRM << std::endl;
            std::cerr << KGRN << "__INSERTED__VALUE__ : " << inserted_node->__pair.first << KNRM << std::endl;

            // Right rotation
            if ((childe_position == LEFT_NODE || childe_position == ROOT_NODE) && childe_position == inserted_position)
            {
                std::cerr << KGRN << "__RIGHT_ROTATION__" << KNRM << std::endl;
                right_rotation(child_node, child_node->__parent);
            }
            // Left rotation
            else if ((childe_position == RIGHT_NODE || childe_position == ROOT_NODE) && childe_position == inserted_position)
            {
                std::cerr << KGRN << "__LEFT_ROTATION__" << KNRM << std::endl;
                left_rotation(child_node, child_node->__parent);
            }
            // Left Right Rotation
            else if (inserted_position == LEFT_NODE && childe_position == RIGHT_NODE)
            {
                right_left_rotation(inserted_node);
            }
            // Right Left Rotation
            else if (inserted_position == RIGHT_NODE && childe_position == LEFT_NODE)
            {
                left_right_rotation(inserted_node);
            }
        }

        void    balance_tree( node** inserted_node )
        {
            node*   node_it = *inserted_node;
            bool    balanced;

            while (*inserted_node != (*inserted_node)->__parent) // Only root_tree verify this condition aka [inserted_node = inserted_node->__parent]
            {
                balanced = false;
                if (*inserted_node != node_it)
                {
                    std::cerr << KRED << "___WAAAARNING___EXCEPTION___00 :: " << (*inserted_node)->__pair.first << KNRM << std::endl;
                    (*inserted_node)->__index++;
                    /*
                        if (get_symmetrical_sutree(*inserted_node)
                            && get_symmetrical_sutree(*inserted_node)->__index
                                == (*inserted_node)->__index - 1)
                        {
                            (*inserted_node)->__index--;
                        }
                    */
                }
                if (this->balance_factor(*inserted_node) == false)
                {
                    this->do_some_magic(*inserted_node, node_it);
                    balanced = true;
                }
                std::cout << "NODE_INDEX ************************************ : " << (*inserted_node)->__index << std::endl;;
                *inserted_node = (*inserted_node)->__parent;
                if (*inserted_node == (*inserted_node)->__parent && balanced == false)
                {
                    std::cerr << KRED << "___WAAAARNING___EXCEPTION___01 :: " << (*inserted_node)->__pair.first << KNRM << std::endl;
                    (*inserted_node)->__index++;
                }
            }
            // //std::cerr << KRED << "BALANCE_TREE_INPUT : **********************************" << KNRM << std::endl;
            // //std::cerr << "PARENT   : [" << (*inserted_node)->__parent << "]" << std::endl;
            // //std::cerr << "LEFT     : [" << (*inserted_node)->__left << "]" << std::endl;
            // //std::cerr << "RIGHTT   : [" << (*inserted_node)->__right << "]" << std::endl;
            // //std::cerr << "PAIR     : [" << (*inserted_node)->__pair.first << " | " << (*inserted_node)->__pair.second << "]" << std::endl;
            // //std::cerr << "POSITION : [" << (*inserted_node)->__position << "]" << std::endl;
            // //std::cerr << "INDEX    : [" << (*inserted_node)->__index << "]" << std::endl;
            // //std::cerr << "THIS     : [" << (*inserted_node) << "]" << std::endl;
            // //std::cerr << KRED << "*******************************************************" << KNRM << std::endl;
        }

        void insert( value_type pair )
        {
            node*   node_it = __root;
            node*   parent_it = __root;
            int     node_position = 0;

            if (pair.first == 3)
            {
                std::cout << "";
            }
            if (__root == NULL)
            {
                //std::cerr << KBLU << "__ROOT__IS__NULL__" << KNRM << std::endl;
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
                node*   inserted_node = append_node(&node_it, &parent_it, node_position, pair);
                this->balance_tree(&inserted_node);
            }
        }
    }; // class sbbst
} // namespace sbbst

#endif

