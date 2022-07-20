
# include "avl_self_balancing_binary_search_tree.hpp"
# include "make_pair.hpp"

template <typename BT>
void printBT(const std::string& prefix, const BT* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::string position = std::string(KCYN) + std::string("XXXXXXXX") + std::string(KNRM);

        std::cout << prefix;
        std::cout << (isLeft ? "├──\x1B[32m(LEFT)\x1B[0m" : "└──\x1B[35m(RIGHT)\x1B[0m" );
        std::cout << "[" << node->get_pair().first << " | " << node->__index;
        if (node->__position == ROOT_NODE)
            position = std::string(KCYN) + std::string("IS_ROOT") + std::string(KNRM);
        else if (node->__position == LEFT_NODE)
            position = std::string("\x1B[32mIS_LEFT") + std::string(KNRM);
        else if (node->__position == RIGHT_NODE)
            position = std::string("\x1B[35mIS_RIGHT") + std::string(KNRM);
        std::cout << " |" << position << "|" << node->__parent->__pair.first << "] " << std::endl;

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

        std::cout << " | " << node->get_pair().first << " | ";

        if (node->get_next_node() == nullptr)
            std::cout << "nullptr";
        else
            std::cout << node->get_next_node()->__pair.first;

        std::cout << "] ";
        node = node->__next;
    }
    std::cout << std::endl << "********************************************************";
}

int     main()
{
    std::string str;
    avl_sbbst<int, std::string> mp;

    while (true)
    {
        std::cout << std::endl << std::endl << " INSERT ELEMENT : ";
        std::cin >> str;

        std::cout << std::endl << std::endl;
        mp.insert(ft::make_pair(stoi(str), "30"));
        print_elements_in_order(mp.get_left_most_node());
    }
}

// int main()
// {
//     std::string str;
//     avl_sbbst<int, std::string> mp;

//     while (true)
//     {
//         std::cout << std::endl << std::endl << " INSERT ELEMENT : ";
//         std::cin >> str;

//         std::cout << std::endl << std::endl;
//         mp.insert(ft::make_pair(stoi(str), "30"));
//         printBT(mp.get_root());
//     }
//     return 0;
// }
