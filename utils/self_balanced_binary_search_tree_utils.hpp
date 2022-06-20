#ifndef __BALANCED_BINARY_SEARCH_TREEUTILS__
# define __BALANCED_BINARY_SEARCH_TREEUTILS__

# include <iostream>
# include "pair.hpp"

# define IS_LEFT    -1
# define IS_RIGHT   +1
# define IS_ROOT    +0

namespace tree
{
    template < class Key,                                              // map::key_type
               class T,                                                // map::mapped_type
               class Compare = std::less<Key>,                         // map::key_compare
               class Alloc = std::allocator<ft::pair<const Key,T> > >  // map::allocator_type
    class TreeNode
    {
    private:
        Key         __key;
        T           __value;
        TreeNode*   __left;
        TreeNode*   __right;
        TreeNode*   __parent;

    public:
        /*
        ** Canonical Form :
        */
        TreeNode( Key key, T value ) :  __key(key),
                                        __value(value),
                                        __left(nullptr),
                                        __right(nullptr),
                                        __parent(nullptr)
        { return; }

        TreeNode(const TreeNode& src)
        {
            if (this != &src)
            {
                this->__key = src.__key;
                this->__value = src.__value;
                this->__left = src.__left;
                this->__right = src.__right;
                this->__parent = src.__parent;
            }
        }

        TreeNode    &operator=(const TreeNode& rhs)
        {
            if (this != &rhs)
            {
                this->__key = rhs.__key;
                this->__value = rhs.__value;
                this->__left = rhs.__left;
                this->__right = rhs.__right;
                this->__parent = rhs.__parent;
            }
            return *this;
        }

        ~TreeNode( void )
        { return; }

        /*
        ** Getters :
        */
        Key         get_key( void ) { return this->__key; }
        T           get_value( void ) { return this->__value; }
        TreeNode*   get_left( void ) { return this->__left; }
        TreeNode*   get_right( void ) { return this->__right; }
        TreeNode*   get_parent( void ) { return this->__parent; }

        /*
        ** Setters :
        */
        void    set_key( const Key& key) { this->__key = key; }
        void    set_value( const T& value) { this->__value = value; }
        void    set_left( TreeNode* left) { this->__left = left; }
        void    set_right( TreeNode* right) { this->__right = right; }
        void    set_parent( TreeNode* parent) { this->__parent = parent; }

    };  // Class TreeNode

} // namespace tree;


#endif

