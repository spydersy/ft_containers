
#ifndef __MAP_HPP__
# define __MAP_HPP__

# include <iostream>

# include "../ft_containers.hpp"
# include "../utils/bidirectional_iterator.hpp"
# include "../utils/pair.hpp"
# include "../utils/self_balanced_binary_search_tree.hpp"

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
        typedef tree::self_balanced_binary_search_tree<
                key_type, mapped_type,key_compare, allocator_type>       SBBST;

        /*
        ** Member Functions:
        */
        private:
            SBBST          __sbbst;
            size_type      __size;
            allocator_type __allocator;
            key_compare    __key_comp;
        public:
        // Default Constructors :
        explicit map (const key_compare& comp = key_compare(),
                    const allocator_type& alloc = allocator_type()) :   __sbbst(SBBST()),
                                                                        __size(0),
                                                                        __allocator(alloc),
                                                                        __key_comp(comp)
        {

        }

        // Range Constructors :
        template <class InputIterator>
        map (InputIterator first, InputIterator last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()) :   __sbbst(SBBST()),
                                                                    __size(0),
                                                                    __allocator(alloc),
                                                                    __key_comp(comp)

        { this->insert(first, last); }

        // Copy Constructors :
        map (const map& x)
        {
            if (this != &x)
            {
                this->__sbbst = x.__sbbst;
                this->__size = x.__size;
            }
        }
        // Operator= :
        map& operator= (const map& x)
        {
            if (this != &x)
            {
                this->__sbbst = x.__sbbst;
                this->__size = x.__size;
            }
            return *this;
        }


        // Destructor :
        ~map()
        {
            this->__sbbst.~self_balanced_binary_search_tree();
        }
        // Insert (Single Element) :
        // pair<iterator,bool> insert (const value_type& val)
        void insert (const value_type& val)
        {
            this->__sbbst.insert(val);
        }

        // Insert (With Hint) :
        // iterator insert (iterator position, const value_type& val);

        // Insert (Range) :
        // template <class InputIterator>
        // void insert (InputIterator first, InputIterator last)
        // {

        // }

        // Size :
        size_type size() const { return this->__sbbst.get_size(); }

        // Max_size :
        size_type max_size() const { return this->__allocator.max_size(); }

        // Emty :
        bool empty() const { return this->__sbbst.get_size() == 0; }
    }; // Class MAP;

    template <class Key, class T, class Compare, class Alloc>
    bool operator== ( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    {
        if (lhs.size() != rhs.size())
            return (false);
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!= ( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    { return !operator==(lhs,rhs); }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<  ( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<= ( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    { return !operator<(rhs, lhs); }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>  ( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    { return operator<(rhs, lhs);}

    template <class Key, class T, class Compare, class Alloc>
    bool operator>= ( const ft::map<Key,T,Compare,Alloc>& lhs,
                        const ft::map<Key,T,Compare,Alloc>& rhs )
    { return !operator<(lhs, rhs); }

    template <class Key, class T, class Compare, class Alloc>
    void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
    { x.swap(y); }
};  // Namespace FT;

#endif
