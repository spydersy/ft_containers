#ifndef __SELF_BALANCED_BINARY_SEARCH_TREEUTILS__
# define __SELF_BALANCED_BINARY_SEARCH_TREEUTILS__

#include <iostream>
#include "pair.hpp"

namespace sbbst
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
    public:
        typedef ft::pair<const Key, T>                     value_type;

    private:
        value_type  __pair;
        TreeNode*   __left;
        TreeNode*   __right;
        TreeNode*   __parent;
    public:
    /*
    ** Canonical Form :
    */
        // Default Constructor :
        TreeNode( void ) { return; }

        // Pair Constructor :
        TreeNode( value_type pair ) :   this->__pair(pair),
                                        this->__left(nullptr),
                                        this->__right(nullptr),
                                        this->__parent(nullptr)
        { return; }

        // Copy Constructor :
        TreeNode( const TreeNode & src ) const
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
            }
            return *this;
        }

        // Destructor :
        ~TreeNode( void ) { return; }
    }; // class TreeNode
} // namespace sbbst


#endif
