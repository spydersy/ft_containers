#include<map>
#include<iostream>
#include<string>
int main()
{
    std::map<int , int> map;
    std::map<int , int>::iterator it;

    int  i = 0;
    map.insert(std::make_pair(i++, 2));
    map.insert(std::make_pair(i++, 2));
    map.insert(std::make_pair(i++, 2));
    map.insert(std::make_pair(i++, 2));
    map.insert(std::make_pair(i++, 2));
    map.insert(std::make_pair(i++, 2));
    map.insert(std::make_pair(i++, 2));
    map.insert(std::make_pair(i++, 2));
    map.insert(std::make_pair(i++, 2));
    map.insert(std::make_pair(i++, 2));

    for (it = map.begin(); it != map.end(); it++)
    {
        std::cout << "BEF : [" << (*it).first << "]" << std::endl;
        if((*it).first == 4)
        {
            map.erase(it);
            std::cout << "DOOOOOOOOOOOOOONE : " << (*it).first << std::endl;
            break;
        }
        std::cout << "AFT : [" << (*it).first << "]" << std::endl;
    }

    std::cout << "****************" << std::endl;

    for (it = map.begin(); it != map.end(); it++)
    {
        std::cout << "BEF : [" << (*it).first << "]" << std::endl;
        if((*it).first == 4)
        {
            std::cout << "DOOOOOOOOOOOOOONE" << std::endl;
        }
        std::cout << "AFT : [" << (*it).first << "]" << std::endl;
    }
}