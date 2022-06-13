
#ifndef __ITERATOR_TRAITS__
# define __ITERATOR_TRAITS__

# include <iostream>

namespace ft
{
    // Iterators Category :
    struct  input_iterator_tag          : public std::input_iterator_tag {};
    struct  output_iterator_tag         : public std::output_iterator_tag {};
    struct  forward_iterator_tag        : public input_iterator_tag {};
    struct  bidirectional_iterator_tag  : public forward_iterator_tag {};
    struct  random_access_iterator_tag  : public bidirectional_iterator_tag {};

    // Iterators Traits :
    template <class Iterator>
    class iterator_traits
    {
        public:
            // Member Types :
            typedef  typename    Iterator::difference_type   difference_type;
            typedef  typename    Iterator::value_type        value_type;
            typedef  typename    Iterator::pointer           pointer;
            typedef  typename    Iterator::reference         reference;
            typedef  typename    Iterator::iterator_category iterator_category;
    };

    template <class T>
    class iterator_traits<T*>
    {
        public:
            // Member Types :
            typedef std::ptrdiff_t                  difference_type;
            typedef T                               value_type;
            typedef T*                              pointer;
            typedef T&                              reference;
            typedef std::random_access_iterator_tag iterator_category;
    };

    template <class T>
    class iterator_traits<const T*>
    {
        public:
            // Member Types :
            typedef std::ptrdiff_t                  difference_type;
            typedef T                               value_type;
            typedef const T*                        pointer;
            typedef const T&                        reference;
            typedef ft::random_access_iterator_tag  iterator_category;
    };
};

#endif