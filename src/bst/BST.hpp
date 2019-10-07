#ifndef BST_HPP
#define BST_HPP
#include <math.h>
#include <iostream>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // number of Data items stored in this BST.
    unsigned int isize;

    // height of this BST.
    int iheight;

  public:
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
     *  Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /** TODO */
    virtual ~BST() { deleteAll(root); }

    /** TODO */
    virtual bool insert(const Data& item) {
        return insert(&root, item, nullptr);
    }

    /** TODO */
    virtual iterator find(const Data& item) const { return find(root, item); }

    /** TODO */
    unsigned int size() const { return isize; }

    /** TODO */
    int height() const { return height(root) - 1; }

    /** TODO */
    bool empty() const { return !(isize > 0); }

    /** TODO */
    iterator begin() const { return BST::iterator(first(root)); }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** TODO */
    vector<Data> inorder() const {
        vector<Data> sequences;
        inorder(root, sequences);
        return sequences;
    }

  private:
    int height(BSTNode<Data>* node) const {
        if (node == nullptr) return 0;
        int lheight = height(node->left);
        int rheight = height(node->right);
        if (lheight > rheight)
            return lheight + 1;
        else
            return rheight + 1;
    }
    void inorder(BSTNode<Data>* node, vector<Data>& seq) const {
        if (node == nullptr) return;
        inorder(node->left, seq);
        seq.push_back(node->data);
        inorder(node->right, seq);
        // return *seq;
    }
    bool insert(BSTNode<Data>** point, const Data& item,
                BSTNode<Data>* parents) {
        BSTNode<Data>* node = *point;
        if (*point == nullptr) {
            *point = new BSTNode<Data>(item);

            if (parents != nullptr) (*point)->parent = parents;

            isize++;

            // if (isize == pow(2, iheight + 1)) iheight++;
            return true;
        }
        if ((*point)->data < item)
            return insert(&((*point)->right), item, *point);
        else if (item < (*point)->data)
            return insert(&((*point)->left), item, *point);
        else
            return false;
    }

    iterator find(BSTNode<Data>* root, const Data& item) const {
        if (root == nullptr) {
            return end();
        } else if (root->data < item)
            return find(root->right, item);
        else if (item < root->data)
            return find(root->left, item);
        else
            return BST::iterator(root);
    }
    /** TODO */
    static BSTNode<Data>* first(BSTNode<Data>* root) {
        BSTNode<Data>* ptr = root;
        while (ptr->left != nullptr) ptr = ptr->left;
        return ptr;
    }

    /** TODO */
    static void deleteAll(BSTNode<Data>* n) {
        if (n == nullptr) return;
        deleteAll(n->left);
        deleteAll(n->right);
        delete (n);
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
        */
    }
};

#endif  // BST_HPP
