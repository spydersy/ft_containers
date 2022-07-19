
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
** Public Member Types: ***************************************************************************
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

private:
/*
** Private Member Types: **************************************************************************
*/
            typedef std::allocator<node>        node_allocator;
            typedef TreeNode<Key, T, Compare>   node;

/*
** Private Attributes: ****************************************************************************
*/
            const int     LEFT_NODE;
            const int     ROOT_NODE;
            const int     RIGHT_NODE;

            node_allocator __node_allocator;
            allocator_type __allocator;
            key_compare    __key_comp;
            node*          __root;
            size_type      __size;

/*
** Public Methods: ********************************************************************************
*/
public:
    /*
    ** Constructors: **********************************************************************************
    */
        explicit map (const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type()) : LEFT_NODE(-1),
                                                                        ROOT_NODE(0),
                                                                        RIGHT_NODE(1),
        {
            this->__key_comp = comp;
            this->__allocator = alloc;
            this->__root = nullptr;
            this->__size = 0;
        }
        
        template <class InputIterator>
          map (InputIterator first, InputIterator last,
               const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type()) : LEFT_NODE(-1),
                                                                 ROOT_NODE(0),
                                                                 RIGHT_NODE(1),
        {
            this->__key_comp = comp;
            this->__allocator = alloc;
            this->__root = nullptr;
            this->__size = 0;
            this->insert(first, last);
        }
        
        // map (const map& x)
        // {
        //     // Do Something . . .
        // }

    /*
    ** Destructors: ***********************************************************************************
    */
        // ~map()
        // {
        //     // Do Something . . .
        // }


    /*
    ** operator= : ************************************************************************************
    */
        // map& operator= (const map& x)
        // {
        //     // Do Something . . .
        // }

    /*
    ** Iterators: *************************************************************************************
    */

        iterator begin()
        { return iterator(this->get_left_most_node()); }

        const_iterator begin() const
        { return const_iterator(this->get_left_most_node()); }

        iterator end()
        { return iterator(this->get_right_most_node()->__left); }

        const_iterator end() const
        { return const_iterator(this->get_right_most_node()->__left); }
        
        reverse_iterator rbegin()
        { return reverse_iterator(iterator(this->get_right_most_node())); }
        
        const_reverse_iterator rbegin() const
        { return const_reverse_iterator(const_iterator(this->get_right_most_node())); }
        
        reverse_iterator rend()
        { return reverse_iterator(const_iterator(this->get_left_most_node()->__prev)); }
        
        const_reverse_iterator rend() const
        { return const_reverse_iterator(const_iterator(this->get_left_most_node()->__prev)); }

    /*
    ** Capacity: **************************************************************************************
    */
        bool empty() const
        { return this->__size == 0; }

        size_type size() const
        { return this->__size; }

        size_type max_size() const
        { return this->__allocator.max_size(); }


    /*
    ** Element access: ********************************************************************************
    */
        mapped_type& operator[] (const key_type& k)
        {
            node*   node_it = __root;
            node*   parent_it = __root;
            int     node_position = 0;

            if (__root == nullptr)
            {
                node node_val(ft::make_pair<key_type, mapped_type>(k, mapped_type()), ROOT_NODE);
                this->__root = this->__node_allocator.allocate(1);
                this->__node_allocator.construct(&this->__root, node_val);
                __root->__parent = __root;
                this->__root->__next = nullptr;
                this->__root->__prev = nullptr;
                return __root->__pair.second;
            }
            else
            {
                while (node_it != nullptr)
                {
                    if (ft::equal(k, node_it->get_pair().first))
                    {
                        std::cout << "Duplicated Element" << std::endl;
                        return node_it->get_pair().second;
                    }
                    else if (this->__key_comp(k, node_it->get_pair().first))
                    {
                        std::cout << KYEL << "<< TO_LEFT" << KNRM << std::endl;
                        parent_it = node_it;
                        node_it = node_it->get_left();
                        node_position = LEFT_NODE;
                    }
                    else if (this->__key_comp(node_it->get_pair().first, k))
                    {
                        std::cout << KYEL << ">> TO_RIGHT" << KNRM << std::endl;
                        parent_it = node_it;
                        node_it = node_it->get_right();
                        node_position = RIGHT_NODE;
                    }
                }
                node    val(ft::make_pair<key_type, mapped_type>(k, mapped_type()), node_position);
                node*   inserted_node = append_node(&node_it, &parent_it, node_position, val);
                node*   tmp_inserted_node = inserted_node;
                if (inserted_node->__position == LEFT_NODE)
                {
                    std::cout << KYEL << "__SET__IN__LEFT__NODE__" << KNRM << std::endl;
                    inserted_node->__next = inserted_node->__parent;
                    inserted_node->__prev = inserted_node->__parent->__prev;
                    if (inserted_node->__prev)
                        inserted_node->__prev->__next = inserted_node;
                    inserted_node->__parent->__prev = inserted_node;
                }
                else
                {
                    std::cout << KGRN << "__SET__IN__RIGHT__NODE__" << KNRM << std::endl;
                    inserted_node->__prev = inserted_node->__parent;
                    inserted_node->__next = inserted_node->__parent->__next;
                    if (inserted_node->__next)
                        inserted_node->__next->__prev = inserted_node;
                    inserted_node->__parent->__next = inserted_node;
                }
                this->balance_tree(&inserted_node);
                return tmp_inserted_node->__pair.second;
            }
        }

    /*
    ** Modifiers: *************************************************************************************
    */
        pair<iterator,bool> insert (const value_type& val)
        {
            node*   node_it = __root;
            node*   parent_it = __root;
            int     node_position = 0;

            if (__root == nullptr)
            {
                node node_val(val, ROOT_NODE);
                this->__root = this->__node_allocator.allocate(1);
                this->__node_allocator.construct(&this->__root, *node_val);
                __root->__parent = __root;
                this->__root->__next = nullptr;
                this->__root->__prev = nullptr;
                return ;
            }
            else
            {
                while (node_it != nullptr)
                {
                    if (ft::equal(val.first, node_it->get_pair().first))
                    {
                        std::cout << "Duplicated Element" << std::endl;
                        return ft::make_pair<iterator, bool>(iterator(node_it), false);
                    }
                    else if (this->__key_comp(val.first, node_it->get_pair().first))
                    {
                        std::cout << KYEL << "<< TO_LEFT" << KNRM << std::endl;
                        parent_it = node_it;
                        node_it = node_it->get_left();
                        node_position = LEFT_NODE;
                    }
                    else if (this->__key_comp(node_it->get_pair().first, val.first))
                    {
                        std::cout << KYEL << ">> TO_RIGHT" << KNRM << std::endl;
                        parent_it = node_it;
                        node_it = node_it->get_right();
                        node_position = RIGHT_NODE;
                    }
                }
                node*   inserted_node = append_node(&node_it, &parent_it, node_position, val);
                node*   tmp_inserted_node = inserted_node;
                if (inserted_node->__position == LEFT_NODE)
                {
                    std::cout << KYEL << "__SET__IN__LEFT__NODE__" << KNRM << std::endl;
                    inserted_node->__next = inserted_node->__parent;
                    inserted_node->__prev = inserted_node->__parent->__prev;
                    if (inserted_node->__prev)
                        inserted_node->__prev->__next = inserted_node;
                    inserted_node->__parent->__prev = inserted_node;
                }
                else
                {
                    std::cout << KGRN << "__SET__IN__RIGHT__NODE__" << KNRM << std::endl;
                    inserted_node->__prev = inserted_node->__parent;
                    inserted_node->__next = inserted_node->__parent->__next;
                    if (inserted_node->__next)
                        inserted_node->__next->__prev = inserted_node;
                    inserted_node->__parent->__next = inserted_node;
                }
                this->balance_tree(&inserted_node);
                return ft::make_pair<iterator, bool>(iterator(tmp_inserted_node), true);
            }
        }

        iterator insert (iterator position, const value_type& val)
        {
            (void)position;
            return this->insert(val).first;
        }

        template <class InputIterator>
          void insert (InputIterator first, InputIterator last)
          {
            while (first++ != last)
                this->insert(first);
          }

        void erase (iterator position)
        {
            // Do Something . . .
        }

        size_type erase (const key_type& k)
        {
            iterator it = find(k);

            if (it == end())
                return 0;
            this->erase(it);
            return 1;
        }

        void erase (iterator first, iterator last)
        {
            while (first++ != last)
                this->erase(first);
        }

        // void swap (map& x)
        // {
        //     // Do Something . . .
        // }

        void clear()
        {
            node*   node_begin;
            node*   node_end;
            node*   next;

            if (this->size() == 0)
                return;
            node_begin = get_left_most_node();
            node_end   = get_right_most_node();
            next = node_begin->__next;

            while (node_begin != node_end)
            {
                next = node_begin->__next;
                this->__node_allocator.destroy(node_begin);
                this->__node_allocator.deallocate(node_begin, 1);
                this->__size--;
                node_begin = next;
            }
            this->__root = nullptr;
        }

    /*
    ** Observers: *************************************************************************************
    */
        // key_compare key_comp() const
        // {
        //     // Do Something . . .
        // }

        // value_compare value_comp() const
        // {
        //     // Do Something . . .
        // }



    /*
    ** Operations: ************************************************************************************
    */
        iterator find (const key_type& k)
        {
            node*   it = this->__root;

            while (it != nullptr)
            {
                if (this->__key_comp(it->__pair.first, key))
                    it = it->__right;
                else if (this->__key_comp(key, it->__pair.first))
                    it = it->__left;
                else
                    return iterator(it);
            }
            return iterator(this->get_right_most_node()->__left);
        }

        const_iterator find (const key_type& k) const
        {
            node*   it = this->__root;

            while (it != nullptr)
            {
                if (this->__key_comp(it->__pair.first, key))
                    it = it->__right;
                else if (this->__key_comp(key, it->__pair.first))
                    it = it->__left;
                else
                    return const_iterator(it);
            }
            return const_iterator(this->get_right_most_node()->__left);
        }


        // size_type count (const key_type& k) const
        // {
        //     // Do Something . . .
        // }


        // iterator lower_bound (const key_type& k)
        // {
        //     // Do Something . . .
        // }

        // const_iterator lower_bound (const key_type& k) const
        // {
        //     // Do Something . . .
        // }


        // iterator upper_bound (const key_type& k)
        // {
        //     // Do Something . . .
        // }

        // const_iterator upper_bound (const key_type& k) const
        // {
        //     // Do Something . . .
        // }


        // pair<const_iterator,const_iterator> equal_range (const key_type& k) const
        // {
        //     // Do Something . . .
        // }

        // pair<iterator,iterator>             equal_range (const key_type& k)
        // {
        //     // Do Something . . .
        // }
    /*
    ** Allocator: *************************************************************************************
    */
        allocator_type get_allocator() const
        { return this->__allocator; }















/*
** Private Methods: *******************************************************************************
*/
private:
    /*
    ** Getters: ***********************************************************************************
    */
        node*   get_root( void ) const { return this->__root; }

        node*   get_left_most_node() const
        {
            node*   it = this->__root;

           if (it == nullptr)
                return it;
            while (it->__left != nullptr)
                it = it->__left;
            return it;
        }

        node*   get_right_most_node() const
        {
            node*   it = this->__root;
            if (it == nullptr)
                return it;
            while (it != nullptr)
                it = it->__right;
            return it->__parent;
        }

        node*    append_node(node** node_it, node** parent_it, int node_position, value_type pair)
        {
            node* n = this->__node_allocator.allocate(1);
            node  val(pair, node_position);
            this->__node_allocator.construct(&n, val);

            *node_it = n;
            (*node_it)->__parent = *parent_it;

            this->__size++;
            if (node_position == LEFT_NODE)
                return (*parent_it)->__left = *node_it;
            else
                return (*parent_it)->__right = *node_it;
        }






    }; // Class MAP;

    // template <class Key, class T, class Compare, class Alloc>
    // bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
    //                     const ft::map<Key,T,Compare,Alloc>& rhs )
    // {
    //     if (lhs.size() != rhs.size())
    //         return (false);
    //     return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    // }

    // template <class Key, class T, class Compare, class Alloc>
    // bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
    //                     const ft::map<Key,T,Compare,Alloc>& rhs )
    // { return !operator==(lhs,rhs); }

    // template <class Key, class T, class Compare, class Alloc>
    // bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
    //                     const ft::map<Key,T,Compare,Alloc>& rhs )
    // { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

    // template <class Key, class T, class Compare, class Alloc>
    // bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
    //                     const ft::map<Key,T,Compare,Alloc>& rhs )
    // { return !operator<(rhs, lhs); }

    // template <class Key, class T, class Compare, class Alloc>
    // bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
    //                     const ft::map<Key,T,Compare,Alloc>& rhs )
    // { return operator<(rhs, lhs);}

    // template <class Key, class T, class Compare, class Alloc>
    // bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
    //                     const ft::map<Key,T,Compare,Alloc>& rhs )
    // { return !operator<(lhs, rhs); }

    // template <class Key, class T, class Compare, class Alloc>
    // void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
    // { x.swap(y); }
};  // Namespace FT;

#endif
