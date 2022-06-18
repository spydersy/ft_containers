
# include "../ft_containers.hpp"
# include <stack>

int main()
{
    ft::pair<int, std::string> p;

    p = ft::make_pair(12, "hello");
    std::cout << p.first << " | " << p.second << std::endl;
    return 0;
}