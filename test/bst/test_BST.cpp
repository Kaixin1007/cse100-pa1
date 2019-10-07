#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
#include "util.hpp"
using namespace std;
using namespace testing;

/* Empty BST test starts here */

TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;
    BST<int> Nullbst;

  public:
    SmallBSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, 100, -33, 2, 50, -333};
        insertIntoBST(input, bst);
    }

    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    ASSERT_EQ(bst.size(), 8);
    ASSERT_EQ(bst.height(), 3);
    ASSERT_EQ(bst.empty(), false);
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion

    cout << *(bst.begin()) << endl;
    // cout << (bst.begin().successorTest())->data << endl;
    cout << "test: " << endl;
    for (auto i = bst.begin(); i != bst.end(); ++i) cout << *i << endl;
    // cout << *(bst.find(-33)) << endl;
    ASSERT_FALSE(bst.insert(3));
    ASSERT_NE(bst.end(), bst.find(2));
    ASSERT_NE(bst.end(), bst.find(100));
    ASSERT_NE(bst.end(), bst.find(-33));
    ASSERT_NE(bst.end(), bst.find(3));
    ASSERT_NE(bst.end(), bst.begin());
    ASSERT_TRUE(bst.insert(22));
}
TEST_F(SmallBSTFixture, INORDER_TEST) {
    vector<int> test{-333, -33, 1, 2, 3, 4, 50, 100};
    ASSERT_EQ(bst.inorder(), test);
}
TEST_F(SmallBSTFixture, FIRST_TEST) {
    cout << "Nulltest: " << endl;
    // cout << *(Nullbst.begin()) << endl;
}

// TODO: add more BST tests here
