#include <iostream>
#include <string>

# include "self_balanced_binary_search_tree.hpp"
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
    cout << " " << root->get_pair().first << endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->get_left(), trunk, false);
}

int main()
{
    {
        std::string str;
        sbbst::sbbst<int, std::string> mp;

        mp.insert(ft::make_pair(1 + 20, "10"));
        mp.insert(ft::make_pair(4 + 20, "40"));
        mp.insert(ft::make_pair(2 + 20, "20"));
        mp.insert(ft::make_pair(3 + 20, "30"));
        mp.insert(ft::make_pair(-10 + 20, "-100"));
        mp.insert(ft::make_pair(-20 + 20, "-100"));
        mp.insert(ft::make_pair(-4 + 20, "40"));
        printTree(mp.get_root(), nullptr, false);
        system("leaks a.out");
    }
    return 0;
}