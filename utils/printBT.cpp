
# include "../containers/map.hpp"
# include "make_pair.hpp"

template <typename BT>
void printBT(const std::string& prefix, const BT* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::string position = std::string(KCYN) + std::string("XXXXXXXX") + std::string(KNRM);

        std::cout << prefix;
        std::cout << (isLeft ? "├──\x1B[32m(LEFT)\x1B[0m" : "└──\x1B[35m(RIGHT)\x1B[0m" );
        std::cout << "[" << node->get_pair()->first << " | " << node->__height;
        if (node->__position == ROOT_NODE)
            position = std::string(KCYN) + std::string("IS_ROOT") + std::string(KNRM);
        else if (node->__position == LEFT_NODE)
            position = std::string("\x1B[32mIS_LEFT") + std::string(KNRM);
        else if (node->__position == RIGHT_NODE)
            position = std::string("\x1B[35mIS_RIGHT") + std::string(KNRM);
        std::cout << " |" << position << "|" << node->__parent->__pair->first << "] " << std::endl;

        printBT( prefix + (isLeft ? "│   " : "    "), node->get_left(), true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->get_right(), false);
    }
    else
        ; //std::cout << "EMPTY_TREE" << std::endl;
}

template <typename BT>
void printBT(const BT* node)
{
    printBT("", node, false);
}

template <typename BT>
void    print_elements_in_order(BT* node)
{
    std::cout << "INORDER ELEMENTS : " << "********************************************************" << std::endl;
    while (node != nullptr)
    {
        std::cout << " [";
        if (node->get_prev_node() == nullptr)
            std::cout << "nullptr";
        else
            std::cout << node->get_prev_node()->__pair->first;

        std::cout << " | " << node->get_pair()->first << " | ";

        if (node->get_next_node() == nullptr)
            std::cout << "nullptr";
        else
            std::cout << node->get_next_node()->__pair->first;

        std::cout << "] ";
        node = node->__next;
    }
    std::cout << std::endl << "********************************************************";
}

// int     main()
// {
//     std::string str;
//     ft::map<int, std::string> mp;

//     while (true)
//     {
//         std::cout << std::endl << std::endl << " INSERT ELEMENT : ";
//         std::cin >> str;

//         std::cout << std::endl << std::endl;
//         mp.insert(ft::make_pair(stoi(str), "30"));
//         printBT(mp.get_root());
//     }
// }

// int main()
// {
//     std::string str;
//     ft::map<int, std::string> mp;

//     for (int i = 0; i <= 10; i++)
//         mp.insert(ft::make_pair<int, std::string>(i, "Yoooo"));

//     while (true)
//     {
//         // std::cout << std::endl << std::endl << " COMMAND : ";
//         // std::cin >> str;

//         // if (str == "i")
//         // {
//         //     std::cout << " INSERT ELEMENT : ";
//         //     std::cin >> str;
//         //     std::cout << std::endl << std::endl;

//         //     mp.insert(ft::make_pair(stoi(str), "30"));
//         //     printBT(mp.get_root());
//         // }
//         // if (str == "d")
//         // {
//             std::cout << " DELETE ELEMENT : ";
//             std::cin >> str;
//             std::cout << std::endl << std::endl;

//             mp.erase(stoi(str));
//             printBT(mp.get_root());
//         // }


//     }
//     return 0;
// }

// int main()
// {

//     ft::map<int, int>   m;
//     std::string         str;

//     for (int c = 1; c != 21; c++)
//     {
//         m.insert(ft::make_pair<int, int>(c, 50));
//         print_elements_in_order(m.get_left_most_node());
//     }
//     std::cout << "__MAP__BEFORE__ERASE__ : " << std::endl;
//     print_elements_in_order(m.get_left_most_node());
//     std::cout << std::endl;
//     printBT(m.get_root());

//     for (ft::map<int, int>::iterator it = m.begin(); it != m.end(); it++)
//     {
//         std::cout << std::endl << "__ERASE__THIS__NODE__ : [" << it->first << "] ";

//         std::cout << " OK ?? : " << std::endl;
//         std::cin >> str;

//         m.erase(it);

//         print_elements_in_order(m.get_left_most_node());
//         std::cout << std::endl;
//         printBT(m.get_root());
//     }

//     std::cout << m.size() << std::endl;
// }

// int main()
// {
//     ft::map<char, int>           ft_m;
//     ft::map<char, int>::iterator ft_it;

//     // insert some values:
//     ft_m['a'] = 10;
//     ft_m['b'] = 20;
//     ft_m['c'] = 30;
//     ft_m['d'] = 40;
//     ft_m['e'] = 50;
//     ft_m['f'] = 60;
//     std::cout << "AA : ========================================================" << std::endl;
//     print_elements_in_order(ft_m.get_left_most_node());
//     std::cout << "BB : ========================================================" << std::endl;

//     ft_it = ft_m.find('b');
//     std::cout << "CC : ========================================================" << std::endl;

//     ft_m.erase(ft_it); // erasing by iterator
//     std::cout << "DD : ========================================================" << std::endl;
//     print_elements_in_order(ft_m.get_left_most_node());
//     printBT(ft_m.get_root());
//     std::cout << "EE : ========================================================" << std::endl;


//     int ft_ret = ft_m.erase('c'); // erasing by key
//     print_elements_in_order(ft_m.get_left_most_node());
//     printBT(ft_m.get_root());
//     std::cout << "FF : ========================================================" << std::endl;
//     std::cout << "ft_ret : " << ft_ret << std::endl;
// }

int main()
{
    ft::map<int, int> m;

    for (int i = 1; i <= 20; i++)
    {
        m.insert(ft::make_pair<int, int>(i, 42));
    }
    printBT(m.get_root());
    print_elements_in_order(m.get_left_most_node());

    m.erase(19);
    std::cout << "===========================================" << std::endl;

    printBT(m.get_root());
    print_elements_in_order(m.get_left_most_node());

    return 0;
}