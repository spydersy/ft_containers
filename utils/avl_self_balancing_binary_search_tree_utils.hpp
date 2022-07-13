#ifndef __SELF_BALANCED_BINARY_SEARCH_TREEUTILS__
# define __SELF_BALANCED_BINARY_SEARCH_TREEUTILS__

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

# define LEFT_NODE  -1
# define RIGHT_NODE +1
# define ROOT_NODE  +0

namespace sbbst /* SIKS SAAAAKHIN __ONLY__FOR__AMZIL__ */
{

    template < class Key,                                              // ft::map::key_type
               class T,                                                // ft::map::mapped_type
               class Compare = std::less<Key>,                         // ft::map::key_compare
               class Alloc = std::allocator<ft::pair<const Key,T> > >  // ft::map::allocator_type
    class TreeNode
    {
    /*
    ** Member Types :
    */
    private:
        typedef ft::pair<const Key, T> value_type;

    public:
        value_type  __pair;
        TreeNode*   __left;
        TreeNode*   __right;
        TreeNode*   __parent;
        int         __index;
        int         __position;

    public:
    /*
    ** Canonical Form :
    */
        // Default Constructor :
        TreeNode( void ) :  __pair(value_type()),
                            __left(nullptr),
                            __right(nullptr),
                            __parent(this),
                            __index(1),
                            __position(0)
        { std::cout << KGRN << "__TREE__NODE__DEFAULT__CONSTRUCTOR__CALLED__" << KNRM << std::endl; }

        // Pair Constructor :
        TreeNode( value_type pair, int position ) : __pair(pair),
                                                    __left(nullptr),
                                                    __right(nullptr),
                                                    __parent(nullptr),
                                                    __index(1),
                                                    __position(position)
        { /*std::cout << KGRN << "__TREE__NODE__PAIR__CONSTRUCTOR__CALLED__" << KNRM << std::endl;*/ }

        // Copy Constructor :
        TreeNode( const TreeNode & src )
        {
            if (this != &src)
            {
                *this = src;
            }
        }

        // Operator= :
        TreeNode&   operator=( const TreeNode & src )
        {
            if (this != &src)
            {
                this->__pair = src.__pair;

                this->__left = nullptr;
                this->__right = nullptr;
                this->__parent = nullptr;
                this->__index = 1;
                this->__position = 0;
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

    }; // class TreeNode
} // namespace sbbst


#endif
