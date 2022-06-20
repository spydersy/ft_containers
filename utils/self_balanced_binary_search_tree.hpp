
#ifndef __BALANCED_BINARY_SEARCH_TREE__
# define __BALANCED_BINARY_SEARCH_TREE__

# include <iostream>
# include "pair.hpp"
# include "self_balanced_binary_search_tree_utils.hpp"

namespace tree
{
    template < class Key,                                              // map::key_type
               class T,                                                // map::mapped_type
               class Compare = std::less<Key>,                         // map::key_compare
               class Alloc = std::allocator<ft::pair<const Key,T> > >  // map::allocator_type
    class balanced_binary_search_tree
    {
    private:
        size_t  __size;
    public:
        balanced_binary_search_tree(/* args */);
        ~balanced_binary_search_tree();

        /*
        ** Getters :
        */
        size_t  get_size( void ) const { return this->__size; }

        /*
        ** Setters :
        */
        void    set_size( size_t n ) { this->__size = n; }
    };
};

#endif