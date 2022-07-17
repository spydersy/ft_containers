
#ifndef __MAP_HPP__
# define __MAP_HPP__

# include <iostream>

# include "../ft_containers.hpp"
# include "../utils/bidirectional_iterator.hpp"
# include "../utils/pair.hpp"
# include "../utils/avl_self_balancing_binary_search_tree.hpp"

namespace ft
{

    template < class Key,                                          // map::key_type
               class T,                                            // map::mapped_type
               class Compare = std::less<Key>,                     // map::key_compare
               class Alloc = std::allocator<ft::pair<const Key,T> > >  // map::allocator_type
    class map
    {
        public:
        /*
        ** Member Types:
        */
        typedef Key                                                      key_type;
        typedef T                                                        mapped_type;
        typedef ft::pair<const key_type,mapped_type>                     value_type;
        typedef Compare                                                  key_compare;
      /*typedef value_compare                                            Something;*/
        typedef Alloc                                                    allocator_type;
        typedef value_type&                                              reference;
        typedef const value_type&                                        const_reference;
        typedef value_type*                                              pointer;
        typedef const value_type*                                        const_pointer;
        typedef ft::bidirectional_iterator<value_type>                   iterator;
        typedef ft::bidirectional_iterator<const value_type>             const_iterator;
        typedef ft::reverse_iterator<iterator>                           reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                     const_reverse_iterator;
		typedef	typename ft::iterator_traits<iterator>::difference_type  difference_type;
		typedef size_t													 size_type;
        typedef avl_sbbst::avl_sbbst<
                key_type, mapped_type,key_compare>                       SBBST;

        /*
        ** Member Functions:
        */
        private:
            SBBST          __sbbst;
            allocator_type __allocator;
            key_compare    __key_comp;

        public:

        explicit map (const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type()) : __sbbst(SBBST()),
                                                                        __allocator(alloc),
                                                                        __key_comp(comp)
        { return ; }


        template <class InputIterator>
        map (InputIterator first, InputIterator last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()) : __sbbst(SBBST()),
                                                                  __allocator(alloc),
                                                                  __key_comp(comp)
        { this->insert(first, last); }

        map (const map& x)
        {
            if (this != &x)
            {
                // DO SOMETHING . . .
            }
        }

    // INSERT METHODE :
        // single element (1)
        pair<iterator,bool> insert (const value_type& val)
        { this->__sbbst.insert(val); }

        // with hint (2)
        iterator insert (iterator position, const value_type& val)
        {
            (void)position;
            this->insert(val);
        }

        // range (3)
        template <class InputIterator>
        void insert (InputIterator first, InputIterator last)
        {
            while (first++ != last)
                this->insert(first);
        }

        size_type size() const
        { return this->__sbbst.__size; }

        iterator begin()
        { return iterator(this->__sbbst.get_left_most_node()); }

        const_iterator begin() const
        { return iterator(this->__sbbst.get_left_most_node()); }

        iterator end()
        { return iterator(this->__sbbst.get_right_most_node()->__left); }

        const_iterator end() const
        { return iterator(this->__sbbst.get_right_most_node()->__left); }

        reverse_iterator rbegin()
        { return reverse_iterator(this->__sbbst.get_left_most_node()); }

        const_reverse_iterator rbegin() const
        { return reverse_iterator(this->__sbbst.get_left_most_node()); }

        reverse_iterator rend()
        { return reverse_iterator(this->__sbbst.get_right_most_node()->__left); }

        const_reverse_iterator rend() const
        { return reverse_iterator(this->__sbbst.get_right_most_node()->__left); }

        bool empty() const { return this->__sbbst.__size == 0; }

        iterator find (const key_type& k)
        { return iterator(this->__sbbst.find(k)); }

        const_iterator find (const key_type& k) const
        { return const_iterator(this->__sbbst.find(k)); }

        mapped_type& operator[] (const key_type& k)
        {
            iterator element = this->find(k);

            if (element != this->end())
                return element.__ptr->second;
            return this->insert(ft::make_pair<key_type, mapped_type>(k, mapped_type())).first.__ptr->second;
        }

        void erase (iterator position)
        { this->__sbbst.erase(position->__ptr); }

        size_type erase (const key_type& k)
        {
            iterator element = this->find(k);
            if (element == this->end())
                return 0;
            this->erase(element);
            return 1;
        }

        void erase (iterator first, iterator last)
        {
            while (first++ != last)
                this->erase(first);
        }
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
