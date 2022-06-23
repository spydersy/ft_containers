
# include <iostream>
# include <map>
# include "../ft_containers.hpp"

int main()
{
    ft::map<int, std::string>   mymap;

    mymap.insert( ft::make_pair<int, std::string>(12, "test") );

    return 0;
}
