
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
            std::cout << node->get_prev_node()->__pair.first;

        std::cout << " | " << node->get_pair()->first << " | ";

        if (node->get_next_node() == nullptr)
            std::cout << "nullptr";
        else
            std::cout << node->get_next_node()->__pair.first;

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

int main()
{

    ft::map<int, int>   m;
    std::string         str;

    for (int c = 1; c != 21; c++)
    {
        m.insert(ft::make_pair<int, int>(c, 50));
    }
    std::cout << "__MAP__BEFORE__ERASE__ : " << std::endl;
    printBT(m.get_root());

    for (ft::map<int, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        std::cout << std::endl << "__ERASE__THIS__NODE__ : [" << it->first << "] ";

        std::cout << " OK ?? : " << std::endl;
        std::cin >> str;

        m.erase(it);

        printBT(m.get_root());
    }

    std::cout << m.size() << std::endl;
}
