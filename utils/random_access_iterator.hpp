
#ifndef __RANDOM_ACCESS_ITERATOR_HPP__
# define __RANDOM_ACCESS_ITERATOR_HPP__

# include "iterators_traits.hpp"

namespace ft
{
    template <class T>
    class random_access_iterator : public iterator_traits<T>
    {
        private:
            /* data */
        public:
            random_access_iterator(/* args */);
            ~random_access_iterator();
    }; 
}

#endif
