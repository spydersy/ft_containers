
#ifndef __ENABLE_IF_HPP__
# define __ENABLE_IF_HPP__

namespace ft
{
    template<bool B, class T = void> struct enable_if {};
    template<class T> struct enable_if<true, T> { typedef T type; };
};

#endif
