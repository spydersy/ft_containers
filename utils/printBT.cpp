
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

        mp.insert(ft::make_pair(20 + 1, "10"));
        std::cerr << KCYN << "__MAIN_ROOT__CHECK__00 : " << mp.get_root()->__parent->__pair.first << KNRM << std::endl;
        mp.insert(ft::make_pair(20 + 2, "20"));
        // std::cerr << KCYN << "__MAIN_ROOT__CHECK__01 : " << mp.get_root()->__parent->__pair.first << KNRM << std::endl;
        mp.insert(ft::make_pair(20 + 3, "30"));
        // // std::cerr << KCYN << "__MAIN_ROOT__CHECK__02 : " << mp.get_root()->__parent->__pair.first << KNRM << std::endl;
        // // // std::cerr << "__INSERTION__04__ : =======================================================" << std::endl;
        mp.insert(ft::make_pair(20 + 4, "30"));
        mp.insert(ft::make_pair(20 + 5, "30"));
        mp.insert(ft::make_pair(20 + 6, "30"));
        mp.insert(ft::make_pair(20 + 7, "30"));
        // std::cerr << KCYN << "__MAIN_ROOT__CHECK__03 : " << mp.get_root()->__parent->__pair.first << KNRM << std::endl;
        // mp.insert(ft::make_pair(20 + -11, "10"));
        // mp.insert(ft::make_pair(20 + -5, "10"));
        // mp.insert(ft::make_pair(20 + 4, "40"));
        // mp.insert(ft::make_pair(20 + -10, "-100"));
        // mp.insert(ft::make_pair(20 + -20, "-100"));
        // mp.insert(ft::make_pair(20 + -4, "40"));
        // std::cout << "ROOT_INDEX : " << mp.get_root()->__index << std::endl;
        printBT(mp.get_root());
        std::cerr << "ROOT : " << mp.get_root() << " | " << mp.get_root()->__parent << " | " << mp.get_root()->__pair.first << std::endl;
        std::cerr << "LEFT : " << mp.get_root()->__left << " | " << mp.get_root()->__left->__parent << " | " << mp.get_root()->__left->__pair.first << std::endl;
    }
    // system("leaks a.out");
    return 0;
}
