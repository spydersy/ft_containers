
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

int main()
{
    {
        std::string str;
        sbbst::sbbst<int, std::string> mp;

        // std::cerr << KCYN << "__MAIN_ROOT__CHECK__00 : " << mp.get_root()->__parent->__pair.first << KNRM << std::endl;
        // std::cerr << KCYN << "__MAIN_ROOT__CHECK__01 : " << mp.get_root()->__parent->__pair.first << KNRM << std::endl;
        // // std::cerr << KCYN << "__MAIN_ROOT__CHECK__02 : " << mp.get_root()->__parent->__pair.first << KNRM << std::endl;
        // // // std::cerr << "__INSERTION__04__ : =======================================================" << std::endl;

        while (true)
        {
            std::cout << std::endl << std::endl << " INSERT ELEMENT : ";
            std::cin >> str;

            std::cout << std::endl << std::endl;
            mp.insert(ft::make_pair(stoi(str), "30"));
            printBT(mp.get_root());
        }
    }
    return 0;
}
