#include <iostream>
#include <string>

# include "../containers/map.hpp"
# include "make_pair.hpp"

using namespace std;

// Data structure to store a binary tree node
struct Node
{
    int data;
    Node *left, *right;

    Node(int data)
    {
        this->data = data;
        this->left = this->right = nullptr;
    }
};

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr) {
        return;
    }

    showTrunks(p->prev);
    cout << p->str;
}

template <typename BT>
void printTree(BT* root, Trunk *prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->get_right(), trunk, true);

    if (!prev) {
        trunk->str = "———";
    }
    else if (isLeft)
    {
        trunk->str = ".———\x1B[32m (LEFT)\x1B[0m";
        prev_str = "   |";
    }
    else {
        trunk->str = "`———\x1B[35m (RIGHT)\x1B[0m";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << " [" << root->get_pair()->first << " | " << root->__index << "]" << endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->get_left(), trunk, false);
}

template <typename BT>
void    dbg(BT* root)
{
    while (root != nullptr)
    {
        std::cout << KCYN << "==========================" << KNRM << std::endl;
        std::cout << "THIS        : [" << root << "]" << std::endl;
        std::cout << "INDEX       : [" << root->__index << "]" << std::endl;
        std::cout << "VALUE       : [" << root->get_pair()->first << "]" << std::endl;
        std::cout << "POSITION    : [" << root->__position << "]" << std::endl << std::endl;

        std::cout << "PARENT      : [" << root->__parent << "]" << std::endl;
        std::cout << "LEFT_CHILD  : [" << root->__left << "]" << std::endl;
        std::cout << "RIGHT_CHILD : [" << root->__right << "]" << std::endl;

        root = root->__right;
    }
}

int main()
{
    std::string str;

    ft::map<int, std::string> mp;

    std::cout << KRED << "DBG : ***********************************************************" << KNRM << std::endl;
    mp.insert(ft::make_pair(1, "10"));
    // std::cin >> str;
    dbg(mp.get_root());

    std::cout << KRED << "DBG : ***********************************************************" << KNRM << std::endl;
    mp.insert(ft::make_pair(2, "20"));
    // std::cin >> str;
    dbg(mp.get_root());

    std::cout << KRED << "DBG : ***********************************************************" << KNRM << std::endl;
    mp.insert(ft::make_pair(3, "30"));
    dbg(mp.get_root());

    // std::cout << KRED << "DBG : ***********************************************************" << KNRM << std::endl;
    // mp.insert(ft::make_pair(4, "30"));
    // dbg(mp.get_root());

    // std::cin >> str;

    // mp.insert(ft::make_pair(4, "30"));
    // std::cin >> str;

    // mp.insert(ft::make_pair(5, "30"));
    // std::cin >> str;

    // mp.insert(ft::make_pair(6, "30"));
    // std::cin >> str;


    // mp.insert(ft::make_pair(7, "30"));
    // std::cin >> str;

    // dbg(mp.get_root());

    printTree(mp.get_root(), nullptr, false);
    exit(0);





        // mp.insert(ft::make_pair(4 + 20, "40"));
        // std::cin >> str;
        // mp.insert(ft::make_pair(-10 + 20, "-100"));
        // std::cin >> str;
        // mp.insert(ft::make_pair(-20 + 20, "-100"));
        // std::cin >> str;
        // mp.insert(ft::make_pair(-4 + 20, "40"));
        // std::cin >> str;
        // printTree(mp.get_root(), nullptr, false);
    return 0;
}