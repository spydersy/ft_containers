#ifndef __AVL_SELF_BALANCED_BINARY_SEARCH_TREE_UTILS__
# define __AVL_SELF_BALANCED_BINARY_SEARCH_TREE_UTILS__

#include <iostream>
#include "pair.hpp"

# define KNRM       "\x1B[0m"
# define KRED       "\x1B[31m"
# define KGRN       "\x1B[32m"
# define KYEL       "\x1B[33m"
# define KBLU       "\x1B[34m"
# define KMAG       "\x1B[35m"
# define KCYN       "\x1B[36m"
# define KWHT       "\x1B[37m"

    template < class Key,                                          // map::key_type
               class T,                                            // map::mapped_type
               class Compare,                                      // map::key_compare
               class Alloc>                                        // map::allocator_type
    class TreeNode
    {
    /*
    ** Member Types :
    */
    private:
        typedef ft::pair<const Key, T>  value_type;

    public:
        int             __height;
        int             __position;

        TreeNode*       __left;
        TreeNode*       __right;
        TreeNode*       __parent;

        TreeNode*       __next;
        TreeNode*       __prev;

        Alloc           __allocator;
        value_type*     __pair;

    public:
        // Constructor :
        template <typename VALUE_TYPE>
        TreeNode( VALUE_TYPE& pair, int position ) : __height(1),
                                                           __position(position),
                                                           __left(nullptr),
                                                           __right(nullptr),
                                                           __parent(this),
                                                           __next(nullptr),
                                                           __prev(nullptr),
                                                           __pair(nullptr)
        {
            this->__pair = this->__allocator.allocate(1);
            this->__allocator.construct(&(this->__pair[0]), pair);
        }

        // Destructor :
        ~TreeNode( void )
        { return; }

    /*
    ** Getters :
    */
        value_type* get_pair( void ) const { return this->__pair; }
        TreeNode*   get_left( void ) const { return this->__left; }
        TreeNode*   get_right( void ) const { return this->__right; }

        TreeNode*   get_prev_node( void )
        { return this->__prev; }

        TreeNode*   get_next_node( void )
        { return this->__next; }
    }; // class TreeNode

#endif
