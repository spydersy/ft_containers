
#ifndef __SELF_BALANCED_BINARY_SEARCH_TREE__
# define __SELF_BALANCED_BINARY_SEARCH_TREE__

# include "self_balanced_binary_search_tree_utils.hpp"

namespace sbbst
{
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
        typedef ft::pair<const Key, T>                     value_type;
        typedef sbbst::TreeNode<Key, T, Compare, Alloc>    node;
    private:
        node    __root;
    public:
        sbbst(/* args */);
        ~sbbst();
    }; // class sbbst
} // namespace sbbst


#endif