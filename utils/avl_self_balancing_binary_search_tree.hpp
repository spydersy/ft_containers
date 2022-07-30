
#ifndef __AVL_SELF_BALANCING_BINARY_SEARCH_TREE__
# define __AVL_SELF_BALANCING_BINARY_SEARCH_TREE__

# include "avl_self_balancing_binary_search_tree_utils.hpp"
# include "pair.hpp"

# define LEFT_NODE    -1
# define ROOT_NODE    0
# define RIGHT_NODE   1
# define END_NODE     INT_MAX
# define BEGIN_NODE   INT_MIN

# include <unistd.h>

template < class Key,                         // map::key_type
           class T,                           // map::mapped_type
           class Compare,                     // map::key_compare
           class Alloc, class node_allocator> // map::allocator_type
class avl_sbbst
{
private:
/*
** Private Member Types: **************************************************************************
*/
    typedef TreeNode<Key, T, Compare, Alloc>   node;
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
private:
/*
** Private Attributes: ****************************************************************************
*/
    node_allocator __node_allocator;
    allocator_type __allocator;
    key_compare    __key_comp;
    node*          __root;
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
        this->__node_allocator.construct(this->__end + 0, end_node);
        this->__end->__prev = nullptr;
        this->__end->__next = nullptr;

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
        this->__node_allocator.construct(this->__end + 0, end_node);
        this->__end->__prev = nullptr;
        this->__end->__next = nullptr;

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
    { this->clear(); }
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
            this->__node_allocator.construct(this->__end + 0, end_node);

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
    {
        if (this->__size == 0)
            return this->end();
        return iterator(this->get_left_most_node());
    }

    const_iterator begin() const
    {
        if (this->__size == 0)
            return this->end();
        return const_iterator(this->get_left_most_node());
    }

    iterator end()
    {
        node* most_right = this->get_right_most_node();

        if (most_right != nullptr)
        {
            most_right->__next = this->__end;
            this->__end->__prev = most_right;
        }
        else
            this->__end->__prev = nullptr;
        return iterator(this->__end);
    }

    const_iterator end() const
    {
        node* most_right = this->get_right_most_node();

        if (most_right != nullptr)
        {
            most_right->__next = this->__end;
            this->__end->__prev = most_right;
        }
        else
            this->__end->__prev = nullptr;
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
                    return node_it->get_pair()->second;
                else if (this->__key_comp(k, node_it->get_pair()->first))
                {
                    parent_it = node_it;
                    node_it = node_it->get_left();
                    node_position = LEFT_NODE;
                }
                else if (this->__key_comp(node_it->get_pair()->first, k))
                {
                    parent_it = node_it;
                    node_it = node_it->get_right();
                    node_position = RIGHT_NODE;
                }
            }
            value_type val_type = ft::make_pair<key_type, mapped_type>(k, mapped_type());
            node    val(val_type, node_position);
            node*   inserted_node = append_node(&node_it, &parent_it, node_position, val_type);
            node*   tmp_inserted_node = inserted_node;

            set_next_prev_insertion(&inserted_node);

            this->balance_tree(&inserted_node);
            return tmp_inserted_node->__pair->second;
        }
    }
/*
** Modifiers: *************************************************************************************
*/
    void    set_next_prev_insertion(node** inserted_node)
    {
        if ((*inserted_node)->__position == LEFT_NODE)
        {
            (*inserted_node)->__next = (*inserted_node)->__parent;
            (*inserted_node)->__prev = (*inserted_node)->__parent->__prev;
            if ((*inserted_node)->__prev)
                (*inserted_node)->__prev->__next = *inserted_node;
            (*inserted_node)->__parent->__prev = *inserted_node;
        }
        else
        {
            (*inserted_node)->__prev = (*inserted_node)->__parent;
            (*inserted_node)->__next = (*inserted_node)->__parent->__next;
            if ((*inserted_node)->__next)
                (*inserted_node)->__next->__prev = *inserted_node;
            (*inserted_node)->__parent->__next = *inserted_node;
        }
    }

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
            this->__root->__next = this->__end;
            this->__end->__prev = this->__root;
            this->__root->__prev = nullptr;
            return ft::make_pair<iterator, bool>(iterator(this->__root), true);
        }
        else
        {
            while (node_it != nullptr)
            {
                if (val.first == node_it->get_pair()->first)
                    return ft::make_pair<iterator, bool>(iterator(node_it), false);
                else if (this->__key_comp(val.first, node_it->get_pair()->first))
                {
                    parent_it = node_it;
                    node_it = node_it->get_left();
                    node_position = LEFT_NODE;
                }
                else if (this->__key_comp(node_it->get_pair()->first, val.first))
                {
                    parent_it = node_it;
                    node_it = node_it->get_right();
                    node_position = RIGHT_NODE;
                }
            }
            node*   inserted_node = append_node(&node_it, &parent_it, node_position, val);
            node*   tmp_inserted_node = inserted_node;

            set_next_prev_insertion(&inserted_node);
            balance_tree(&inserted_node);
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

    // node*   _erase_leaf_node(node* n, bool SET)
    // { }

    // node*   _erase_one_child_node(node* n, int child_position)
    // { }

    // node*   _erase_two_childs_node(node* n)
    // { }

    void erase (iterator position)
    {
        (void)position;
    }

    size_type erase (const key_type& k)
    {
        iterator it = find(k);

        if (it == this->end())
            return 0;
        this->erase(it);
        return 1;
    }

    void erase (iterator first, iterator last)
    {
        iterator tmp(first);

        while (first != last)
        {
            tmp = first.__ptr->__next;
            this->erase(first);
            first = tmp;
        }
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
        node*   node_begin = get_left_most_node();
        node*   node_end = get_right_most_node();
        node*   next_node = node_begin;

        if (this->__size)
        {
            while (node_begin != node_end)
            {
                next_node = node_begin->__next;
                //__DEALLOCATE__NODE__02__0__ : [" << node_begin << "]" << std::endl;
                deallocate_node(node_begin);
                node_begin = nullptr;
                node_begin = next_node;
                this->__size--;
            }
            // deallocate_node(node_begin);
        }
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
        return it;
    }

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

    node*   get_root( void ) const
    { return this->__root; }

    node*   get_left_most_node() const
    {
        node*   it = this->__root;

       if (it == nullptr)
            return it;
        while (it->__left != nullptr)
            it = it->__left;
        return it;
    }

/*
** Private Methods: *******************************************************************************
*/
private:
    int calc_height(node* n)
    {
        if (n->__left == nullptr && n->__right == nullptr)
            return 1;
        else if (n->__left == nullptr && n->__right != nullptr)
            return n->__right->__height + 1;
        else if (n->__left != nullptr && n->__right == nullptr)
            return n->__left->__height + 1;
        else
            return get_max_index_of_child(n)->__height + 1;
    }

    void   set_next_prev_deletion(node** n)
    {
        node* next = (*n)->__next;
        node* prev = (*n)->__prev;

        if ((*n)->__next)
            (*n)->__next->__prev = prev;
        if ((*n)->__prev)
            (*n)->__prev->__next = next;
    }

    node*   get_right_most_node() const
    {
        node*   it = this->__root;
        if (it == nullptr)
            return it;
        while (it->__right != nullptr)
            it = it->__right;
        return it;
    }

    void    deallocate_pair(value_type* p)
    {
        this->__allocator.deallocate(p, 1);
        p = nullptr;
    }

    void    deallocate_node(node* n)
    {

        deallocate_pair(n->__pair);
        n->__pair = nullptr;
        this->__node_allocator.destroy(&n[0]);
        this->__node_allocator.deallocate(n, 1);
        n = nullptr;
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

    void    balance_tree( node** action_node )
    {
        // node*   node_it = *action_node;

        while (*action_node != (*action_node)->__parent)
        {
            (*action_node)->__height = calc_height(*action_node);

            if (this->balance_factor_bool(*action_node) == false)
            {
                this->do_some_magic(action_node);
            }
            *action_node = (*action_node)->__parent;
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
        return n->__left->__height <= n->__right->__height ? n->__right : n->__left;
    }

    bool    balance_factor_bool(node* n)
    {
        node*   left = n->__left;
        node*   right = n->__right;
        int     diff = 0;

        if (left == nullptr && right == nullptr)
            return (-1 <= diff && diff <= 1);
        else if (left == nullptr && right != nullptr)
            diff = right->__height;
        else if (left != nullptr && right == nullptr)
            diff = left->__height;
        else
            diff = left->__height - right->__height;
        return (-1 <= diff && diff <= 1);
    }

    void    do_some_magic( node** unbalanced_node )
    {
        if (balance_factor_value(*unbalanced_node) == 2)
        {
            if (balance_factor_value((*unbalanced_node)->__left) == 1)
            {   //Case A:
                // std::cout << "__UNBALANCED__NODE__ " << (*unbalanced_node)->__pair->first << " | __BALANCE__FACTOR__ : 2 | CHILD : 1" << std::endl;
                right_rotation(*unbalanced_node, true);
            }
            else if (balance_factor_value((*unbalanced_node)->__left) == -1)
            {   //Case B:
                // std::cout << "__UNBALANCED__NODE__ " << (*unbalanced_node)->__pair->first << " | __BALANCE__FACTOR__ : 2 | CHILD : -1" << std::endl;
                left_right_rotation((*unbalanced_node)->__left);
            }
        }
        else if (balance_factor_value(*unbalanced_node) == -2)
        {
            if (balance_factor_value((*unbalanced_node)->__right) == 1)
            {   //Case C:
                // std::cout << "__UNBALANCED__NODE__ " << (*unbalanced_node)->__pair->first << " | __BALANCE__FACTOR__ : -2 | CHILD : 1" << std::endl;
                right_left_rotation((*unbalanced_node)->__right);
            }
            else if (balance_factor_value((*unbalanced_node)->__right) == -1)
            {   //Case D:
                // std::cout << "__UNBALANCED__NODE__ " << (*unbalanced_node)->__pair->first << " | __BALANCE__FACTOR__ : -2 | CHILD : -1" << std::endl;
                left_rotation(*unbalanced_node, true);
            }
        }
    }

    node*   get_non_null_child(node* parent)
    {
        if (parent->__left != nullptr)
            return parent->__left;
        if (parent->__right != nullptr)
            return parent->__right;
        return nullptr;
    }

    int balance_factor_value(node* n)
    {
        node*   left_node = n->__left;
        node*   right_node = n->__right;

        if(left_node != nullptr && right_node != nullptr)
            return left_node->__height - right_node->__height;
        else if(left_node != nullptr && right_node == nullptr)
            return left_node->__height;
        else if(left_node == nullptr && right_node != nullptr)
            return -right_node->__height;
        return 0;
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
        node* t2 = nullptr;

        t2 = y->__left;
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
        z->__parent = y;
        z->__position = LEFT_NODE;
        if (CHANGE_INDEX)
            z->__height = y->__height - 1;
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
        node* t3 = nullptr;

        t3 = y->__right;
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
            z->__height = y->__height - 1;
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

        int old_index = ret->__height;
        ret->__height = get_max_index_of_child(ret)->__height;

        if (ret->__left)
            ret->__left->__height = old_index;
        if (ret->__right)
            ret->__right->__height = old_index;
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

        old_index = ret->__height;
        ret->__height = get_max_index_of_child(ret)->__height;
        if (ret->__left)
            ret->__left->__height = old_index;
        if (ret->__right)
            ret->__right->__height = old_index;
    }

    }; // Class avl_sbbst;

#endif








// If BF(node) = +2 and BF(node -> left-child) = +1, perform LL rotation.
// If BF(node) = -2 and BF(node -> right-child) = 1, perform RR rotation.
// If BF(node) = -2 and BF(node -> right-child) = +1, perform RL rotation.
// If BF(node) = +2 and BF(node -> left-child) = -1, perform LR rotation.
