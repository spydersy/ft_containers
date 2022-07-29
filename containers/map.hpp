
#ifndef __MAP_HPP__
# define __MAP_HPP__

# include <iostream>

# include "../ft_containers.hpp"
# include "../utils/bidirectional_iterator.hpp"
# include "../utils/pair.hpp"
# include "../utils/avl_self_balancing_binary_search_tree.hpp"
# include "../utils/avl_self_balancing_binary_search_tree_utils.hpp"

namespace ft
{
    template < class Key,                                          // map::key_type
               class T,                                            // map::mapped_type
               class Compare = std::less<Key>,                     // map::key_compare
               class Alloc = std::allocator<ft::pair<const Key,T> > >  // map::allocator_type
    class map
    {
private:
/*
** Private Member Types: **************************************************************************
*/
    typedef TreeNode<Key, T, Compare, Alloc>                     node;
    typedef typename Alloc::template rebind<node>::other         node_allocator;
public:
/*
** Public Member Types: ***************************************************************************
*/
        typedef Key                                                      key_type;
        typedef T                                                        mapped_type;
        typedef Compare                                                  key_compare;
        typedef ft::pair<const key_type,mapped_type>                     value_type;
        /*typedef value_compare                                            Something;*/
        typedef Alloc                                                    allocator_type;
        typedef value_type&                                              reference;
        typedef const value_type&                                        const_reference;
        typedef value_type*                                              pointer;
        typedef const value_type*                                        const_pointer;
        typedef ft::bidirectional_iterator<node, value_type>             iterator;
        typedef ft::bidirectional_iterator<node, const value_type>       const_iterator;
        typedef ft::reverse_iterator<iterator>                           reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                     const_reverse_iterator;
		typedef	typename ft::iterator_traits<iterator>::difference_type  difference_type;
		typedef size_t													 size_type;
        // typedef TreeNode<Key, T, Compare>                                node;

private:
/*
** Private Member Types: **************************************************************************
*/
        typedef avl_sbbst<key_type, mapped_type, key_compare, allocator_type, node_allocator>   avl_tree;

/*
** Private Attributes: ****************************************************************************
*/
    private:
        avl_tree       __sbbst;

/*
** Public Methods: ********************************************************************************
*/
public:
    /*
    ** Constructors: **********************************************************************************
    */
        explicit map (const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type()) : __sbbst(avl_tree())
        {
            (void)comp;
            (void)alloc;
        }

        template <class InputIterator>
          map (InputIterator first, InputIterator last,
               const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type()) : __sbbst(first, last, comp, alloc)
        { return; }

        map (const map& x) : __sbbst(x.__sbbst)
        { return; }

    /*
    ** Destructors: ***********************************************************************************
    */
        ~map()
        {
            // std::cout << "__MAP__DESTRUCTOR__CALLED__" << std::endl;
        }


    /*
    ** operator= : ************************************************************************************
    */
        map& operator= (const map& x)
        {
            if (this != &x)
            {
                this->__sbbst = x.__sbbst;
            }
            return *this;
        }

    /*
    ** Iterators: *************************************************************************************
    */

        iterator begin()
        { return iterator(this->__sbbst.begin()); }

        const_iterator begin() const
        { return const_iterator(this->__sbbst.begin()); }

        iterator end()
        { return this->__sbbst.end(); }

        const_iterator end() const
        { return this->__sbbst.end(); }

        reverse_iterator rbegin()
        { return reverse_iterator(this->end()); }

        const_reverse_iterator rbegin() const
        { return const_reverse_iterator(this->end()); }

        reverse_iterator rend()
        { return reverse_iterator(this->begin()); }

        const_reverse_iterator rend() const
        { return const_reverse_iterator(this->begin()); }

    /*
    ** Capacity: **************************************************************************************
    */
        bool empty() const
        { return this->__sbbst.empty(); }

        size_type size() const
        { return this->__sbbst.size(); }

        size_type max_size() const
        { return this->__allocator.max_size(); }

    /*
    ** Element access: ********************************************************************************
    */
        mapped_type& operator[] (const key_type& k)
        { return this->__sbbst.operator[](k); }

    /*
    ** Modifiers: *************************************************************************************
    */
        pair<iterator,bool> insert (const value_type& val)
        { return this->__sbbst.insert(val); }

        iterator insert (iterator position, const value_type& val)
        { return this->__sbbst.insert(position, val); }

        template <class InputIterator>
        void insert (InputIterator first, InputIterator last)
        { this->__sbbst.insert(first, last); }

        void erase (iterator position)
        { this->__sbbst.erase(position); }

        size_type erase (const key_type& k)
        { return this->__sbbst.erase(k); }

        void erase (iterator first, iterator last)
        { this->__sbbst.erase(first, last); }

        void swap (map& x)
        {
            if (this != &x)
                this->__sbbst.swap(x.__sbbst);
        }

        void clear()
        {   this->__sbbst.clear(); }

        node* get_root() const
        { return this->__sbbst.get_root(); }

        node*   get_left_most_node() const
        { return this->__sbbst.get_left_most_node(); }

    /*
    ** Observers: *************************************************************************************
    */
        key_compare key_comp() const
        { return this->__sbbst.key_comp(); }

        // value_compare value_comp() const
        // {
        //     // Do Something . . .
        // }



    /*
    ** Operations: ************************************************************************************
    */
        iterator find (const key_type& k)
        { return this->__sbbst.find(k); }

        const_iterator find (const key_type& k) const
        { return this->__sbbst.find(k); }


        size_type count (const key_type& k) const
        { return this->__sbbst.count(k); }

        iterator lower_bound (const key_type& k)
        { return this->__sbbst.lower_bound(k); }

        const_iterator lower_bound (const key_type& k) const
        { return this->__sbbst.lower_bound(k); }


        iterator upper_bound (const key_type& k)
        { return this->__sbbst.upper_bound(k); }

        const_iterator upper_bound (const key_type& k) const
        { return this->__sbbst.upper_bound(k); }


        pair<const_iterator,const_iterator> equal_range (const key_type& k) const
        { return this->__sbbst.equal_range(k); }

        pair<iterator,iterator> equal_range (const key_type& k)
        { return this->__sbbst.equal_range(k); }

    /*
    ** Allocator: *************************************************************************************
    */
        allocator_type get_allocator() const
        { return this->__sbbst.get_allocator(); }
    }; // Class MAP;

    template <class Key, class T, class Compare, class Alloc>
    bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        if (lhs.size() != rhs.size())
            return (false);
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    { return !operator==(lhs,rhs); }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    { return !operator<(rhs, lhs); }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    { return operator<(rhs, lhs);}

    template <class Key, class T, class Compare, class Alloc>
    bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    { return !operator<(lhs, rhs); }

    template <class Key, class T, class Compare, class Alloc>
    void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
    { x.swap(y); }
};  // Namespace FT;

#endif
