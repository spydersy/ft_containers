
#ifndef __ITERATOR_TRAITS__
# define __ITERATOR_TRAITS__

namespace ft
{

    // Iterators Category :
    struct  input_iterator_tag {};
    struct  output_iterator_tag {};
    struct  forward_iterator_tag       : public input_iterator_tag {};
    struct  bidirectional_iterator_tag : public forward_iterator_tag {};
    struct  random_access_iterator_tag : public bidirectional_iterator_tag {};

    // Iterators Traits : 
    template <class Iterator>
    class iterator_traits
    {
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
        // Member Types :
        typedef  ptrdiff_t   difference_type;
        typedef  T        value_type;
        typedef  T*           pointer;
        typedef  T&         reference;
        typedef  typename random_access_iterator_tag:: iterator_category;
    };

    template <class T>
    class iterator_traits<const T*>
    {
        // Member Types :
        typedef  typename    T::difference_type   difference_type;
        typedef  typename    T::value_type        value_type;
        typedef  typename    T::pointer           pointer;
        typedef  typename    T::reference         reference;
        typedef  typename    T::iterator_category iterator_category;
    };
};

#endif