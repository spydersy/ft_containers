
# include "../containers/map.hpp"
# include "make_pair.hpp"


#ifndef SEED
# define SEED sickl
# endif


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
    std::cout << "********************************************************" << " INORDER ELEMENTS : " << "********************************************************" << std::endl;
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
    std::cout << std::endl;
}

#include <sys/time.h>

int main()
{
    ft::map<int, int>   m;
    struct timeval s;

    gettimeofday(&s, NULL);

    long sickl = (long)time(nullptr) * 1000000L + s.tv_usec;
    std::srand((unsigned int)SEED);
    int n = 50;
    int ratio = 3;

    std::cout << "seed = " << sickl << std::endl;
    std::cout << "ratio = " << ratio << std::endl;
    std::cout << "n = " << n << std::endl;

    for (int i = 1; i <= n; i++)
    {
        int r = abs(rand()) % (n + 1);
        bool condition = r% ratio;
        r = abs(rand()) % (n + 1);
        if (condition) {
            std::cout << "INSERTION : " << r << std::endl;
            m.insert(ft::make_pair(r, 0));
        }
        else {
            std::cout << "ERASE : " << r << std::endl;
            m.erase(r);
        }
        printBT(m.get_root());
    }
    // printBT(m.get_root());
    return 0;
}