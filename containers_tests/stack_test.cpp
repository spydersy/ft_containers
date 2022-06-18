
# include "../ft_containers.hpp"
# include <stack>

int main()
{
    {
        int sum(0);
        std::stack<int> mystack;

        for (int i=0; i<5; ++i) mystack.push(i);

        while (!mystack.empty())
        {
            sum += mystack.top();
            mystack.pop();
        }
    }
    std::cerr << "======================================" << std::endl;
    {
        int sum(0);
        ft::stack<int> mystack;

        for (int i=0; i<5; ++i) mystack.push(i);

        while (!mystack.empty())
        {
            sum += mystack.top();
            mystack.pop();
        }
    }
}