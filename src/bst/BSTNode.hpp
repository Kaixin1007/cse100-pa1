#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

template <typename Data>

class BSTNode {
  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;
    Data const data;  // the const Data in this node.

    /** TODO */
    BSTNode(const Data& d) : data(d) { left = right = parent = nullptr; }

    /** TODO */
    BSTNode<Data>* successor() {
        if (parent == nullptr)
            return nullptr;

        else if (right == nullptr) {
            return rightBranch(parent);
        } else
            minNode(right);
    }

  private:
    BSTNode<Data>* minNode(BSTNode<Data>* x1) {
        BSTNode<Data>* temp = x1;
        while (temp->left != nullptr) temp = temp->left;
        return temp;
    }
    BSTNode<Data>* rightBranch(BSTNode<Data>* x1) {
        BSTNode<Data>* temp = x1;
        while (x1->parent != nullptr)
            if (x1->parent->data < x1->data)
                x1 = x1->parent;
            else
                break;
    }
};

/** DO NOT CHANGE THIS METHOD
 *  Overload operator<< to print a BSTNode's fields to an ostream.
 */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
