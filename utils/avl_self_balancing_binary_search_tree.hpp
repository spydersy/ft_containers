
#ifndef __AVL_SELF_BALANCING_BINARY_SEARCH_TREE__
# define __AVL_SELF_BALANCING_BINARY_SEARCH_TREE__

# include "avl_self_balancing_binary_search_tree_utils.hpp"
# include "pair.hpp"

# define LEFT_NODE    -1
# define ROOT_NODE    +0
# define RIGHT_NODE   +1
# define END_NODE     INT_MAX
# define BEGIN_NODE   INT_MIN

template < class Key,                                          // map::key_type
               class T,                                            // map::mapped_type
               class Compare = std::less<Key>,                     // map::key_compare
               class Alloc = std::allocator<ft::pair<const Key,T> > >  // map::allocator_type
    class avl_sbbst
    {
private:
/*
** Private Member Types: **************************************************************************
*/
            typedef TreeNode<Key, T, Compare>   node;
            typedef std::allocator<node>        node_allocator;
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
** Private Attributes: ****************************************************************************
*/
            node_allocator __node_allocator;
            allocator_type __allocator;
            key_compare    __key_comp;
            node*          __root;
            node*          __begin;
            node*          __end;
            size_type      __size;

/*
** Public Methods: ********************************************************************************
*/
public:
    /*
    ** Constructors: **********************************************************************************
    */
        explicit avl_sbbst (const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type())
        {
            this->__key_comp = comp;
            this->__key_comp = comp;
            this->__allocator = alloc;
            this->__root = nullptr;

            value_type end_val = ft::make_pair<key_type, mapped_type>(key_type(), mapped_type());
            node end_node( end_val, END_NODE);
            this->__end = this->__node_allocator.allocate(1);
            this->__node_allocator.construct(&(this->__end[0]), end_node);

            value_type begin_val = ft::make_pair<key_type, mapped_type>(key_type(), mapped_type());
            node begin_node( begin_val, BEGIN_NODE);
            this->__begin = this->__node_allocator.allocate(1);
            this->__node_allocator.construct(&(this->__begin[0]), begin_node);

            this->__size = 0;
        }

        template <class InputIterator>
          avl_sbbst (InputIterator first, InputIterator last,
               const key_compare& comp = key_compare(),
               const allocator_type& alloc = allocator_type())
        {
            this->__key_comp = comp;
            this->__allocator = alloc;
            this->__root = nullptr;
            this->__size = 0;

            value_type end_val = ft::make_pair<key_type, mapped_type>(key_type(), mapped_type());
            node end_node( end_val, END_NODE);
            this->__end = this->__node_allocator.allocate(1);
            this->__node_allocator.construct(&(this->__end[0]), end_node);


            value_type begin_val = ft::make_pair<key_type, mapped_type>(key_type(), mapped_type());
            node begin_node( begin_val, BEGIN_NODE);
            this->__begin = this->__node_allocator.allocate(1);
            this->__node_allocator.construct(&(this->__begin[0]), begin_node);

            this->insert(first, last);
        }

        avl_sbbst (const avl_sbbst& x)
        {
            this->__root = nullptr;
            this->__size = 0;
            if (this != &x)
                this->operator=(x);
        }

    /*
    ** Destructors: ***********************************************************************************
    */
        ~avl_sbbst()
        { }


    /*
    ** operator= : ************************************************************************************
    */
        avl_sbbst& operator= (const avl_sbbst& x)
        {
            if (this != &x)
            {
                if (this->__size)
                    this->clear();
                this->__key_comp = x.__key_comp;
                this->__node_allocator = x.__node_allocator;
                this->__allocator = x.__allocator;
                this->__key_comp = x.__key_comp;
                this->__size = 0;
                this->__root = nullptr;

                value_type end_val = ft::make_pair<key_type, mapped_type>(key_type(), mapped_type());
                node end_node( end_val, END_NODE);
                this->__end = this->__node_allocator.allocate(1);
                this->__node_allocator.construct(&(this->__end[0]), end_node);


                value_type begin_val = ft::make_pair<key_type, mapped_type>(key_type(), mapped_type());
                node begin_node( begin_val, BEGIN_NODE);
                this->__begin = this->__node_allocator.allocate(1);
                this->__node_allocator.construct(&(this->__begin[0]), begin_node);

                if (x.__root == nullptr)
                    return *this;
                this->insert(x.begin(), x.end());
            }
            return *this;
        }

    /*
    ** Iterators: *************************************************************************************
    */

        iterator begin()
        { return iterator(this->get_left_most_node()); }

        const_iterator begin() const
        { return const_iterator(this->get_left_most_node()); }

        iterator end()
        {
            if (this->__size == 0)
                return iterator(nullptr);
            node* most_right = this->get_right_most_node();

            most_right->__next = this->__end;
            // this->__end = most_right;
            most_right->__next->__prev = most_right;
            return iterator(this->__end);
        }

        const_iterator end() const
        {
            if (this->__size == 0)
                return const_iterator(nullptr);
            node* most_right = this->get_right_most_node();

            most_right->__next = this->__end;
            most_right->__next->__prev = most_right;

            // this->__end = most_right;
            return const_iterator(this->__end);
        }

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
            value_type val_type = ft::make_pair<key_type, mapped_type>(k, mapped_type());

            if (__root == nullptr)
            {
                node node_val(val_type, ROOT_NODE);
                this->__root = this->__node_allocator.allocate(1);
                this->__node_allocator.construct(&(this->__root[0]), node_val);
                __root->__parent = __root;
                this->__root->__next = nullptr;
                this->__root->__prev = nullptr;
                this->__size++;
                return __root->__pair->second;
            }
            else
            {
                while (node_it != nullptr)
                {
                    if (k == node_it->get_pair()->first)
                    {
                        // std::cout << "Duplicated Element" << std::endl;
                        return node_it->get_pair()->second;
                    }
                    else if (this->__key_comp(k, node_it->get_pair()->first))
                    {
                        // std::cout << KYEL << "<< TO_LEFT" << KNRM << std::endl;
                        parent_it = node_it;
                        node_it = node_it->get_left();
                        node_position = LEFT_NODE;
                    }
                    else if (this->__key_comp(node_it->get_pair()->first, k))
                    {
                        // std::cout << KYEL << ">> TO_RIGHT" << KNRM << std::endl;
                        parent_it = node_it;
                        node_it = node_it->get_right();
                        node_position = RIGHT_NODE;
                    }
                }
                value_type val_type = ft::make_pair<key_type, mapped_type>(k, mapped_type());
                node    val(val_type, node_position);
                node*   inserted_node = append_node(&node_it, &parent_it, node_position, val_type);
                node*   tmp_inserted_node = inserted_node;
                if (inserted_node->__position == LEFT_NODE)
                {
                    // std::cout << KYEL << "__SET__IN__LEFT__NODE__" << KNRM << std::endl;
                    inserted_node->__next = inserted_node->__parent;
                    inserted_node->__prev = inserted_node->__parent->__prev;
                    if (inserted_node->__prev)
                        inserted_node->__prev->__next = inserted_node;
                    inserted_node->__parent->__prev = inserted_node;
                }
                else
                {
                    // std::cout << KGRN << "__SET__IN__RIGHT__NODE__" << KNRM << std::endl;
                    inserted_node->__prev = inserted_node->__parent;
                    inserted_node->__next = inserted_node->__parent->__next;
                    if (inserted_node->__next)
                        inserted_node->__next->__prev = inserted_node;
                    inserted_node->__parent->__next = inserted_node;
                }
                this->balance_tree(&inserted_node);
                return tmp_inserted_node->__pair->second;
            }
        }

    /*
    ** Modifiers: *************************************************************************************
    */
        ft::pair<iterator,bool> insert (const value_type& val)
        {
            node*   node_it = __root;
            node*   parent_it = __root;
            int     node_position = 0;

            if (__root == nullptr)
            {
                node node_val(val, ROOT_NODE);
                this->__root = this->__node_allocator.allocate(1);
                this->__node_allocator.construct(&this->__root[0], node_val);
                __root->__parent = __root;
                this->__size++;
                this->__root->__next = nullptr;
                this->__root->__prev = nullptr;
                return ft::make_pair<iterator, bool>(iterator(this->__root), true);
            }
            else
            {
                while (node_it != nullptr)
                {
                    if (val.first == node_it->get_pair()->first)
                    {
                        // std::cout << "Duplicated Element" << std::endl;
                        return ft::make_pair<iterator, bool>(iterator(node_it), false);
                    }
                    else if (this->__key_comp(val.first, node_it->get_pair()->first))
                    {
                        // std::cout << KYEL << "<< TO_LEFT" << KNRM << std::endl;
                        parent_it = node_it;
                        node_it = node_it->get_left();
                        node_position = LEFT_NODE;
                    }
                    else if (this->__key_comp(node_it->get_pair()->first, val.first))
                    {
                        // std::cout << KYEL << ">> TO_RIGHT" << KNRM << std::endl;
                        parent_it = node_it;
                        node_it = node_it->get_right();
                        node_position = RIGHT_NODE;
                    }
                }
                node*   inserted_node = append_node(&node_it, &parent_it, node_position, val);
                node*   tmp_inserted_node = inserted_node;
                if (inserted_node->__position == LEFT_NODE)
                {
                    // std::cout << KYEL << "__SET__IN__LEFT__NODE__" << KNRM << std::endl;
                    inserted_node->__next = inserted_node->__parent;
                    inserted_node->__prev = inserted_node->__parent->__prev;
                    if (inserted_node->__prev)
                        inserted_node->__prev->__next = inserted_node;
                    inserted_node->__parent->__prev = inserted_node;
                }
                else
                {
                    // std::cout << KGRN << "__SET__IN__RIGHT__NODE__" << KNRM << std::endl;
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
            while (first != last)
            {
                this->insert(*first);
                first++;
            }
        }

        void erase (iterator position)
        {
            node*   parent;
            if (position.__ptr->__left == nullptr && position.__ptr->__right == nullptr)
                parent = __erase__leaf__node(position.__ptr, true);
            else if (position.__ptr->__left == nullptr && position.__ptr->__right != nullptr)
                parent = __erase__one__subtree(position.__ptr, RIGHT_NODE, true);
            else if (position.__ptr->__left != nullptr && position.__ptr->__right == nullptr)
                parent = __erase__one__subtree(position.__ptr, LEFT_NODE, true);
            // else if (position.__ptr->__left != nullptr && position.__ptr->__right != nullptr)
            //     parent = __erase__both__subtrees(position);
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

        void swap (avl_sbbst& x)
        {
            if (this != &x)
            {
                node_allocator tmp__node_allocator = x.__node_allocator;
                allocator_type tmp__allocator = x.__allocator;
                key_compare    tmp__key_comp = x.__key_comp;
                node*          tmp__root = x.__root;
                size_type      tmp__size = x.__size;

                x.__node_allocator = this->__node_allocator;
                x.__allocator = this->__allocator;
                x.__key_comp = this->__key_comp;
                x.__root = this->__root;
                x.__size = this->__size;

                this->__node_allocator = tmp__node_allocator;
                this->__allocator = tmp__allocator;
                this->__key_comp = tmp__key_comp;
                this->__root = tmp__root;
                this->__size = tmp__size;
            }
        }

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
                node_begin = next;
                this->__size--;
            }
            this->__root = nullptr;
        }

    /*
    ** Observers: *************************************************************************************
    */
        key_compare key_comp() const
        { return this->__key_comp; }

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
                if (this->__key_comp(it->__pair->first, k))
                    it = it->__right;
                else if (this->__key_comp(k, it->__pair->first))
                    it = it->__left;
                else
                    return iterator(it);
            }
            return this->end();
        }

        const_iterator find (const key_type& k) const
        {
            node*   it = this->__root;

            while (it != nullptr)
            {
                if (this->__key_comp(it->__pair->first, k))
                    it = it->__right;
                else if (this->__key_comp(k, it->__pair->first))
                    it = it->__left;
                else
                    return const_iterator(it);
            }
            return const_iterator(this->get_right_most_node()->__left);
        }


        size_type count (const key_type& k) const
        {
            const_iterator it = this->find(k);

            if (it == this->end())
                return 0;
            return 1;
        }

        iterator lower_bound (const key_type& k)
        {
            iterator it = this->begin();
            iterator end_it = this->end();

            while (it != end_it)
            {
                if (this->__key_comp(k, it->first))
                    break ;
            }
            return it;
        }

        const_iterator lower_bound (const key_type& k) const
        {
            const_iterator it = this->begin();
            const_iterator end_it = this->end();

            while (it != end_it)
            {
                if (it->first == k)
                    return it;
                else if (this->__key_comp(it->first, k))
                    break ;
                it++;
            }
            return it;
        }


        iterator upper_bound (const key_type& k)
        {
            iterator it = this->begin();
            iterator end_it = this->end();

            while (it != end_it)
            {
                if (it->first == k)
                    return it;
                else if (this->__key_comp(it->first, k))
                    break ;
                it++;
            }
            return it;
        }

        const_iterator upper_bound (const key_type& k) const
        {
            const_iterator it = this->begin();
            const_iterator end_it = this->end();

            while (it != end_it)
            {
                if (it->first == k)
                    return it;
                else if (this->__key_comp(it->first, k))
                    break ;
                it++;
            }
            return it;        }


        ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
        {
            if (k == k) {}
            return ft::make_pair<const_iterator,const_iterator>(this->begin(), this->begin());
        }

        ft::pair<iterator,iterator>             equal_range (const key_type& k)
        {
            if (k == k) {}
            return ft::make_pair<iterator, iterator>(this->begin(), this->begin());
        }
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

        void    set_next_prev_deletion(node* n)
        {
            node* next = n->__next;
            node* prev = n->__prev;

            if (next)
                next->__prev = n->__next;
            if (prev)
                prev->__next = n->__next;
        }

        node*   get_root( void ) const { return this->__root; }

        node*   get_left_most_node() const
        {
            node*   it = this->__root;

           if (it == nullptr)
                return it;
            while (it->__left != nullptr)
                it = it->__left;
            if (it->__position == BEGIN_NODE)
                return it->__next;
            return it;
        }

        node*   get_right_most_node() const
        {
            node*   it = this->__root;
            if (it == nullptr)
                return it;
            while (it->__right != nullptr)
                it = it->__right;
            // if (it->__position == END_NODE)
            //     return it->__prev;
            return it;
        }

        node*    append_node(node** node_it, node** parent_it, int node_position, value_type pair)
        {
            node* n = this->__node_allocator.allocate(1);
            node  val(pair, node_position);
            this->__node_allocator.construct(&n[0], val);

            *node_it = n;
            (*node_it)->__parent = *parent_it;
            this->__size++;
            if (node_position == LEFT_NODE)
                return (*parent_it)->__left = *node_it;
            else
                return (*parent_it)->__right = *node_it;
        }


        void    balance_tree( node** inserted_node )
        {
            node*   node_it = *inserted_node;

            while (*inserted_node != (*inserted_node)->__parent) // Only root_tree verify this condition aka [inserted_node = inserted_node->__parent]
            {
                if (*inserted_node != node_it)
                {
                    (*inserted_node)->__index++;
                    if (get_max_index_of_child(*inserted_node)
                    && (*inserted_node)->__index - get_max_index_of_child(*inserted_node)->__index > 1)
                    {
                        (*inserted_node)->__index--;
                    }
                }
                if (this->balance_factor_bool(*inserted_node) == false)
                {
                    this->do_some_magic(*inserted_node, node_it);
                }
                // std::cout << "NODE_INDEX ************************************ : " << (*inserted_node)->__index << std::endl;;
                *inserted_node = (*inserted_node)->__parent;
                if (*inserted_node == (*inserted_node)->__parent && balance_factor_value(get_non_null_child(*inserted_node)) != 0)
                {
                    // std::cerr << KRED << "___WAAAARNING___EXCEPTION___01 :: " << (*inserted_node)->__pair->first << KNRM << std::endl;
                    (*inserted_node)->__index++;
                    if (get_max_index_of_child(*inserted_node)
                    && (*inserted_node)->__index - get_max_index_of_child(*inserted_node)->__index > 1)
                    {
                        (*inserted_node)->__index--;
                        // std::cerr << KCYN << "___WAAAARNING___EXCEPTION___01__________________ :: " << KNRM << std::endl;
                    }
                }
            }
        }

        node*   get_max_index_of_child(node* n)
        {
            if (n->__left == nullptr && n->__right == nullptr)
                return nullptr;
            if (n->__left != nullptr && n->__right == nullptr)
                return n->__left;
            if (n->__left == nullptr && n->__right != nullptr)
                return n->__right;
            return n->__left->__index <= n->__right->__index ? n->__right : n->__left;
        }

        bool    balance_factor_bool(node* node1)
        {
            int     diff = node1->__index;
            node*   node2 = get_symmetrical_sutree(node1);

            if (node2 != nullptr)
                diff = node1->__index - node2->__index;
            return (-1 <= diff && diff <= 1);
        }

        node*    __erase__leaf__node(node* n, bool SET_NEXT_PREV)
        {
            node*   parent = n->__parent;

            if (SET_NEXT_PREV == true)
                set_next_prev_deletion(n);
            if (n->__position == ROOT_NODE)
            {
                n->__parent = nullptr;
                this->__root = nullptr;
            }
            else if (n->__position == LEFT_NODE)
                n->__parent->__left = nullptr;
            else
                n->__parent->__right = nullptr;
            this->__node_allocator.destroy(n);
            this->__node_allocator.deallocate(&n[0], 1);
            return parent;
        }

        void    do_some_magic( node* child_node, node* inserted_node )
        {
            int inserted_position = inserted_node->__position;
            int childe_position = child_node->__position;

            // Right rotation
            if ((childe_position == LEFT_NODE || childe_position == ROOT_NODE) && childe_position == inserted_position)
            {
                // std::cerr << KGRN << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_RIGHT_-_ROTATION_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << KNRM << std::endl;
                right_rotation(child_node->__parent, true);
            }
            // Left rotation
            else if ((childe_position == RIGHT_NODE || childe_position == ROOT_NODE) && childe_position == inserted_position)
            {
                // std::cerr << KGRN << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_LEFT_-_ROTATION_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << KNRM << std::endl;
                left_rotation(child_node->__parent, true);
            }
            // Right Left Rotation
            else if (inserted_position == LEFT_NODE && childe_position == RIGHT_NODE)
            {
                // std::cerr << KGRN << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_RIGHT_-_LEFT_-_ROTATION_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << KNRM << std::endl;
                right_left_rotation(child_node);
            }
            // Left Right Rotation
            else if (inserted_position == RIGHT_NODE && childe_position == LEFT_NODE)
            {
                // std::cerr << KGRN << "_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_LEFT_-_RIGHT_-_ROTATION_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_" << KNRM << std::endl;
                left_right_rotation(child_node);
            }
        }


        node*    __erase__one__subtree(node* n, int position, bool SET_NEXT_PREV)
        {
            node*   parent = n->__parent;
            node*   subtree = n->__left;

            if (SET_NEXT_PREV == true)
                set_next_prev_deletion(n);
            if (position == RIGHT_NODE)
                subtree = n->__right;

            if (n->__position == ROOT_NODE)
            {
                this->__root = subtree;
                subtree->__parent = subtree;
                subtree->__position = ROOT_NODE;
                this->__node_allocator.destroy(n);
                this->__node_allocator.deallocate(&n[0], 1);
                return parent;
            }
            else if (n->__position == LEFT_NODE)
                parent->__left = subtree;
            else
                parent->__right = subtree;
            subtree->__parent = parent;

            this->__node_allocator.destroy(n);
            this->__node_allocator.deallocate(&n[0], 1);


            return parent;
        }

        node*   get_non_null_child(node* parent)
        {
            if (parent->__left != nullptr)
                return parent->__left;
            if (parent->__right != nullptr)
                return parent->__right;
            return nullptr;
        }

        int balance_factor_value(node* node1)
        {
            node*   node2 = get_symmetrical_sutree(node1);

            if (node1 != nullptr && node2 == nullptr)
                return node1->__index;
            if (node1 == nullptr && node2 != nullptr)
                return node2->__index;
            if (node1 == nullptr && node2 == nullptr)
                return 0;
            return node1->__index - node2->__index;
        }

        node* get_symmetrical_sutree( node* sutree )
        {
            if (sutree == nullptr)
                return nullptr;
            if (sutree->__position == LEFT_NODE)
            {
                return sutree->__parent->__right;
            }
            else if (sutree->__position == RIGHT_NODE)
            {
                return sutree->__parent->__left;
            }
            else
            {
                return sutree;
            }
        }


        /* ************************************************************************************ *
         *                                                                                      *
         *  T1, T2, T3 and T4 are subtrees.                                                     *
         *                                                                                      *
         *             Z                                                      Y                 *
         *           /  \                                                   /  \                *
         *          /    \                                                 /    \               *
         *         /      \                                               /      \              *
         *        T1      Y                Left Rotate (z)               Z       X              *
         *               / \               =============>               / \     / \             *
         *              /   \                                          /   \   /   \            *
         *            T2    X                                         T1   T2 T3   T4           *
         *                 / \                                                                  *
         *                /   \                                                                 *
         *               T3   T4                                                                *
         *                                                                                      *
         * ************************************************************************************ */
        node*   left_rotation( node* z, bool CHANGE_INDEX )
        {
            node* y = z->__right;
            node* t2 = y->__left;

            if (t2)
            {
                t2->__parent = z;
                t2->__position = RIGHT_NODE;
            }
            if (z->__position == ROOT_NODE)
            {
                this->__root = y;
                y->__parent = y;
                y->__position = ROOT_NODE;
            }
            else
            {
                y->__parent = z->__parent;
                y->__position = z->__position;
                if (y->__position == LEFT_NODE)
                    z->__parent->__left = y;
                else
                    z->__parent->__right = y;
            }
            y->__left = z;
            z->__right = t2;
            // std::cerr << "Z->PARENT : [" << z->__parent->__pair->first << "] | Y : [" << y->__pair->first << "]" << std::endl;
            z->__parent = y;
            z->__position = LEFT_NODE;
            if (CHANGE_INDEX)
                z->__index = y->__index - 1;
            return y;
        }

        /* ************************************************************************************ *
         *                                                                                      *
         *  T1, T2, T3 and T4 are subtrees.                                                     *
         *                                                                                      *
         *                   Z                                       Y                          *
         *                 /  \                                    /  \                         *
         *                /    \                                  /    \                        *
         *               /      \                                /      \                       *
         *              Y      T4       Right Rotate (z)        X       Z                       *
         *            /  \              =============>         / \     / \                      *
         *           /    \                                   /   \   /   \                     *
         *          X     T3                                 T1   T2 T3   T4                    *
         *         / \                                                                          *
         *        /   \                                                                         *
         *       T1   T2                                                                        *
         *                                                                                      *
         * ************************************************************************************ */
        node*   right_rotation( node* z, bool CHANGE_INDEX )
        {
            node* y = z->__left;
            node* t3 = y->__right;

            if (t3)
            {
                t3->__parent = z;
                t3->__position = LEFT_NODE;
            }
            if (z->__position == ROOT_NODE)
            {
                this->__root = y;
                y->__parent = y;
                y->__position = ROOT_NODE;
            }
            else
            {
                y->__parent = z->__parent;
                y->__position = z->__position;
                if (y->__position == LEFT_NODE)
                    z->__parent->__left = y;
                else
                    z->__parent->__right = y;
            }
            y->__right = z;
            z->__left = t3;
            z->__parent = y;
            z->__position = RIGHT_NODE;
            if (CHANGE_INDEX)
                z->__index = y->__index - 1;
            return y;
        }

        /* ************************************************************************************ *
         *                                                                                      *
         *  T1, T2, T3 and T4 are subtrees.                                                     *
         *                                                                                      *
         *           Z                             Z                               X            *
         *          / \                           / \                            /   \          *
         *         /   \                         /   \                          /     \         *
         *        Y    T4                       X    T4                        /       \        *
         *      /  \        Left Rotate (y)    / \       Right Rotate(z)      Y         Z       *
         *     /   \       =============>     /   \      =============>      / \       / \      *
         *    T1   X                         Y    T3                        /   \     /   \     *
         *        / \                       / \                            /     \   /     \    *
         *       /   \                     /   \                          T1    T2  T3     T4   *
         *      T2   T3                   T1   T2                                               *
         *                                                                                      *
         * ************************************************************************************ */
        void    left_right_rotation(node* y)
        {
            node* x = left_rotation(y, false);
            node* ret = right_rotation(x->__parent, false);

            int old_index = ret->__index;
            ret->__index = get_max_index_of_child(ret)->__index;

            if (ret->__left)
                ret->__left->__index = old_index;
            if (ret->__right)
                ret->__right->__index = old_index;
        }

        /* ************************************************************************************ *
         *                                                                                      *
         *  T1, T2, T3 and T4 are subtrees.                                                     *
         *                                                                                      *
         *       Z                              Z                                    X          *
         *     /  \                            / \                                 /   \        *
         *    /    \                          /   \                               /     \       *
         *   T1     Y                       T1     X                             /       \      *
         *         / \     Right Rotate(y)        / \      Left Rotate(z)       Z         Y     *
         *        /  \     =============>        /   \     =============>      / \       / \    *
         *       X   T4                         T2   Y                        /   \     /   \   *
         *      / \                                 / \                      /     \   /     \  *
         *     /   \                               /   \                    T1    T2  T3     T4 *
         *    T2   T3                             T3   T4                                       *
         *                                                                                      *
         * ************************************************************************************ */
        void    right_left_rotation(node* y)
        {
            int old_index;
            node* x = right_rotation(y, false);
            node* ret = left_rotation(x->__parent, false);

            old_index = ret->__index;
            ret->__index = get_max_index_of_child(ret)->__index;
            if (ret->__left)
                ret->__left->__index = old_index;
            if (ret->__right)
                ret->__right->__index = old_index;
        }

    }; // Class avl_sbbst;

#endif

