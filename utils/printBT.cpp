
# include "self_balanced_binary_search_tree.hpp"
# include "make_pair.hpp"

template <typename BT>
void printBT(const std::string& prefix, const BT* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;
        std::cout << (isLeft ? "├──\x1B[32m(LEFT)\x1B[0m" : "└──\x1B[35m(RIGHT)\x1B[0m" );
        std::cout << "[" << node->get_pair().first << " | " << node->get_pair().second << "] " << std::endl;

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
    // sbbst::sbbst<int, std::string> _sbbst;

    // int x = 0;

    // _sbbst.insert(ft::make_pair<int, std::string>(1337, "hello") );
    // _sbbst.insert(ft::make_pair<int, std::string>(13, "hello_again") );
    // _sbbst.insert(ft::make_pair<int, std::string>(130000, "hello_again") );
    // _sbbst.insert(ft::make_pair<int, std::string>(1300009, "hello_again") );
    // _sbbst.insert(ft::make_pair<int, std::string>(1300005, "hello_again") );
    // _sbbst.insert(ft::make_pair<int, std::string>(1300007, "hello_again") );
    // printBT(_sbbst.get_root());

sbbst::sbbst<int, int> mp;

mp.insert(ft::make_pair(1, 10));
mp.insert(ft::make_pair(2, 20));
mp.insert(ft::make_pair(3, 30));
mp.insert(ft::make_pair(4, 40));
mp.insert(ft::make_pair(-10, -100));
mp.insert(ft::make_pair(-4, 40));
printBT(mp.get_root());

    return 0;
}
