#ifndef __AVL_SELF_BALANCED_BINARY_SEARCH_TREEUTILS__
# define __AVL_SELF_BALANCED_BINARY_SEARCH_TREEUTILS__

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

    template < class Key,                                              // map::key_type
               class T,                                                // map::mapped_type
               class Compare = std::less<Key> >                        // map::key_compare
    class TreeNode
    {
    /*
    ** Member Types :
    */
    private:
        typedef ft::pair<const Key, T>  value_type;

    public:
        value_type      __pair;

        TreeNode*       __left;
        TreeNode*       __right;
        TreeNode*       __parent;

        TreeNode*       __next;
        TreeNode*       __prev;

        int             __index;
        int             __position;

    public:
    /*
    ** Canonical Form :
    */
        // Default Constructor :
        TreeNode( void ) :  __pair(value_type()),
                            __left(nullptr),
                            __right(nullptr),
                            __parent(this),
                            __next(nullptr),
                            __prev(nullptr),
                            __index(1),
                            __position(0)
        { std::cout << KGRN << "__TREE__NODE__DEFAULT__CONSTRUCTOR__CALLED__" << KNRM << std::endl; }

        // Pair Constructor :
        TreeNode( const value_type& pair, int position ) : __pair(pair),
                                                           __left(nullptr),
                                                           __right(nullptr),
                                                           __parent(nullptr),
                                                           __next(nullptr),
                                                           __prev(nullptr),
                                                           __index(1),
                                                           __position(position)
        { return; }

        // Copy Constructor :
        // TreeNode( const TreeNode & src )
        // {
        //     if (this != &src)
        //     {
        //         *this = src;
        //     }
        // }

        // Operator= :
        TreeNode&   operator=( const TreeNode & src )
        {
            if (this != &src)
            {
                this->__pair = src.__pair;
                this->__left = src.__left;
                this->__right = src.__right;
                this->__parent = src.__parent;
                this->__next = src.__next;
                this->__prev = src.__prev;
                this->__index = src.__index;
                this->__position = src.__position;
            }
            return *this;
        }

        // Destructor :
        ~TreeNode( void )
        { std::cout << KGRN << "__TREE__NODE__DESTRUCTOR__CALLED__" << KNRM << std::endl; }          

    /*
    ** Getters :
    */
        value_type  get_pair( void ) const { return this->__pair; }
        TreeNode*   get_left( void ) const { return this->__left; }
        TreeNode*   get_right( void ) const { return this->__right; }

        TreeNode*   get_prev_node( void )
        { return this->__prev; }

        TreeNode*   get_next_node( void )
        { return this->__next; }
    }; // class TreeNode

#endif
