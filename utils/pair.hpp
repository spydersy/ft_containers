
#ifndef __PAIR_HPP__
# define __PAIR_HPP__

namespace ft
{
        template< class T1, class T2 >
        struct pair
        {
            public:
            /*
            ** Member Types :
            */
                typedef T1  first_type;
                typedef T2  second_type;

            /*
            ** Member Objects :
            */
                first_type  first;
                second_type second;

            /*
            ** Member Functions :
            */
            pair() : first(first_type()), second(second_type()) { return ; }

            template<class U, class V>
            pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) { return ; }

            pair (const first_type& a, const second_type& b) :  first(a), second(b) { return ; }

            pair& operator=( const pair& other )
            {
                if (this != &other)
                {
                    this->first = other.first;
                    this->second = other.second;
                }
                return *this;
            }

            ~pair() { return; }
        };

        template <class T1, class T2>
        bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        { return lhs.first==rhs.first && lhs.second==rhs.second; }

        template <class T1, class T2>
        bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        { return !(lhs==rhs); }

        template <class T1, class T2>
        bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

        template <class T1, class T2>
        bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        { return !(rhs<lhs); }

        template <class T1, class T2>
        bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        { return rhs<lhs; }

        template <class T1, class T2>
        bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
        { return !(lhs<rhs); }
};  // Namespace FT

#endif