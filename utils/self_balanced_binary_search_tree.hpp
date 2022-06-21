
#ifndef __SELF_BALANCED_BINARY_SEARCH_TREE__
# define __SELF_BALANCED_BINARY_SEARCH_TREE__

# include <iostream>
# include "pair.hpp"
# include "self_balanced_binary_search_tree_utils.hpp"

namespace tree
{
    template < class Key,                                              // map::key_type
               class T,                                                // map::mapped_type
               class Compare = std::less<Key>,                         // map::key_compare
               class Alloc = std::allocator<ft::pair<const Key,T> > >  // map::allocator_type
    class self_balanced_binary_search_tree
    {
        typedef tree::TreeNode<Key, T, Compare, Alloc> TreeNode;
    private:
        size_t                                  __size;
        tree::TreeNode<Key, T, Compare, Alloc>* __root;
        Alloc                                   __allocator;
    public:
        // Default Constructor :
        self_balanced_binary_search_tree( void )
        {
            std::cerr << "BEGIN : SBBST_CONSTRUCTOR" << std::endl;
            this->__size = 0;
            this->__root = nullptr;
            std::cerr << "END   : SBBST_CONSTRUCTOR" << std::endl;
            return ;
        }

        // Destructor :
        ~self_balanced_binary_search_tree() { return; }

        void    insert(Key key, T value)
        {
            TreeNode* node =  new TreeNode(key, value);

            if (this->__size == 0)
            {
                this->__root = node;
            }
        }

        /*
        ** Getters :
        */
        size_t  get_size( void ) const { return this->__size; }

    };
};

#endif