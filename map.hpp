
#ifndef __MAP_HPP__
# define __MAP_HPP__

# include <iostream>

# include "ft_containers.hpp"

namespace ft
{

    template<
        class Key,
        class T,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<ft::pair<const Key, T> >
        >
    class map
    {

    }; // Class MAP;
};  // Namespace FT;

#endif
