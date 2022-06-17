
#ifndef __STACK_HPP__
# define __STACK_HPP__

# include "vector.hpp"

namespace ft
{
    template< class T,class Container = ft::vector<T> >
    class stack
    {
    public:
    /*
    ** Member Types :
    */
        typedef          Container                   container_type;
        typedef typename Container::value_type       value_type;
        typedef typename Container::size_type        size_type;
        typedef typename Container::reference        reference;
        typedef typename Container::const_reference  const_reference;

    /*
    ** Member Functions :
    */
        // Default Constructor :
        explicit stack( const Container& cont = Container() ) : __container(cont) { return ; }

        // Destructor :
        ~stack( void ) { return ; }

        // Operator= :
        stack& operator=( const stack& other )
        {
            if (this != &other)
                this->__container = other.__container;
            return *this;
        }
    /*
    ** Elements Accessors :
    */
        // Top :
        reference top()
        {
            return this->__container.front();
        }

        // Const Top :
        const_reference top() const
        {
            return this->__container.front();
        }

        // Empty :
        bool empty() const
        {
            return this->__container.empty();
        }

        // Size :
        size_type size() const
        {
            return this->__container.size();
        }

        // Push :
        void push( const value_type& value )
        {
            this->__container.push_back(value);
        }

        // Pop :
        void pop()
        {
            this->__container.pop_back();
        }

    template <class FT, class FContainer>
        friend bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs ); /* { return lhs.__container == rhs.__container; } */

    template <class FT, class FContainer>
        friend bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ); /* { return lhs.__container != rhs.__container; } */

    template <class FT, class FContainer>
        friend bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs ); /* { return lhs.__container < rhs.__container; } */

    template <class FT, class FContainer>
        friend bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ); /* { return lhs.__container <= rhs.__container; } */

    template <class FT, class FContainer>
        friend bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs ); /* { return lhs.__container > rhs.__container; } */

    template <class FT, class FContainer>
        friend bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ); /* { return lhs.__container >= rhs.__container; } */

    protected:
        container_type  __container;
    };  // Class Stack;

    /*
    ** Non-member functions
    */
    template< class T, class Container >
    bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
    {
        return  lhs.__container == rhs.__container;
    }

    template< class T, class Container >
    bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
    {
        return  lhs.__container != rhs.__container;
    }

    template< class T, class Container >
    bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
    {
        return  lhs.__container < rhs.__container;
    }

    template< class T, class Container >
    bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
    {
        return  lhs.__container <= rhs.__container;
    }

    template< class T, class Container >
    bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
    {
        return  lhs.__container > rhs.__container;
    }

    template< class T, class Container >
    bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
    {
        return  lhs.__container >= rhs.__container;
    }
};  // Namespace FT;

#endif
