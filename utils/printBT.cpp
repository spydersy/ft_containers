
# include "self_balanced_binary_search_tree.hpp"
# include "make_pair.hpp"

template <typename BT>
void printBT(const std::string& prefix, const BT* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;
        std::cout << (isLeft ? "├──\x1B[32m(LEFT)\x1B[0m" : "└──\x1B[35m(RIGHT)\x1B[0m" );
        std::cout << "[" << node->get_pair().first << " | " << node->__index << "] " << std::endl;

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

        mp.insert(ft::make_pair(1, "10"));
        mp.insert(ft::make_pair(2, "20"));
        mp.insert(ft::make_pair(3, "30"));
        // mp.insert(ft::make_pair(-11, "10"));
        // mp.insert(ft::make_pair(-5, "10"));
        // mp.insert(ft::make_pair(4, "40"));
        // mp.insert(ft::make_pair(-10, "-100"));
        // mp.insert(ft::make_pair(-20, "-100"));
        // mp.insert(ft::make_pair(-4, "40"));

        // std::cout << "ROOT_INDEX : " << mp.get_root()->__index << std::endl;
        printBT(mp.get_root());
    }
    // system("leaks a.out");
    return 0;
}
