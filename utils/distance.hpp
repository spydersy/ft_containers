
#ifndef __DISTANCE_HPP__
# define __DISTANCE_HPP__

# include "iterators_traits.hpp"

namespace ft
{
    template <class RandIter>
    typename    ft::iterator_traits<RandIter>::difference_type
                distance(RandIter first, RandIter last, typename ft::random_access_iterator_tag)
    {
            std::cout << "Heey ! 0 " << std::endl;
        return first - last;
    }

    template <class InputIter>
    typename    ft::iterator_traits<InputIter>::difference_type
                distance(InputIter first, InputIter last, typename ft::input_iterator_tag)
    {
        typename ft::iterator_traits<InputIter>::difference_type diff = 0;
        for (; first != last; ++first)
        {
            std::cout << "Heey !" << std::endl;
            diff++;
        }
        return  diff;
    }

}; // namespace ft


#endif
