
# include "self_balanced_binary_search_tree.hpp"
# include "make_pair.hpp"

template <typename BT>
void printBT(const std::string& prefix, const BT* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;
        std::cout << (isLeft ? "├──\x1B[32m(LEFT)\x1B[0m" : "└──\x1B[35m(RIGHT)\x1B[0m" );
        std::cout << "[" << node->get_pair().first << " | " << node->__position << "] " << std::endl;

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

        mp.insert(ft::make_pair(1 + 20, "10"));
        std::cin >> str;
        mp.insert(ft::make_pair(4 + 20, "40"));
        std::cin >> str;
        mp.insert(ft::make_pair(2 + 20, "20"));
        std::cin >> str;
        mp.insert(ft::make_pair(3 + 20, "30"));
        std::cin >> str;
        mp.insert(ft::make_pair(-10 + 20, "-100"));
        std::cin >> str;
        mp.insert(ft::make_pair(-20 + 20, "-100"));
        std::cin >> str;
        mp.insert(ft::make_pair(-4 + 20, "40"));

        std::cout << "ROOT_INDEX : " << mp.get_root()->__index << std::endl;
        printBT(mp.get_root());
    }
    system("leaks a.out");
    return 0;
}
