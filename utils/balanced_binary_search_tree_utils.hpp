#ifndef __BALANCED_BINARY_SEARCH_TREEUTILS__
# define __BALANCED_BINARY_SEARCH_TREEUTILS__

# include <iostream>
# include "pair.hpp"

namespace tree
{
    template < class Key,                                              // map::key_type
               class T,                                                // map::mapped_type
               class Compare = std::less<Key>,                         // map::key_compare
               class Alloc = std::allocator<ft::pair<const Key,T> > >  // map::allocator_type
    class node
    {
    private:
        Key     __key;
        T       __value;
        node*   __left;
        node*   __right;
        size_t  __level;
    public:
        node( void ) {/* Do Something ... */}
        ~node( void ) {/* Do Something ... */}
    };

} // namespace tree


#endif

