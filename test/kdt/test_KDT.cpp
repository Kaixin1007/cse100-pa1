#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "KDT.hpp"
#include "NaiveSearch.hpp"
#include "Point.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/**
 * A simple test fixture from which multiple tests can
 * be written. The structure of the KDT built from this
 * may vary. See test_BST.cpp for more information on
 * test fixtures.
 */
class SmallKDTFixture : public ::testing::Test {
  protected:
    vector<Point> vec;
    KDT kdt;

  public:
    //                (3.2,1.0)
    //       (1,0,3,2)         (5.7,3.2)
    //   (1.8,1.9)           (4.4,2.2)
    SmallKDTFixture() {
        vec.emplace_back(Point({1.0, 3.2}));
        vec.emplace_back(Point({3.2, 1.0}));
        vec.emplace_back(Point({5.7, 3.2}));
        vec.emplace_back(Point({1.8, 1.9}));
        vec.emplace_back(Point({4.4, 2.2}));
        kdt.build(vec);
        cout << kdt.height() << endl;
    }
};

TEST_F(SmallKDTFixture, TEST_SIZE) {
    // Assert that the kd tree has the correct size
    ASSERT_EQ(kdt.size(), 5);
    ASSERT_EQ(kdt.height(), 2);
}

TEST_F(SmallKDTFixture, TEST_NEAREST_POINT) {
    NaiveSearch naiveSearch;
    naiveSearch.build(vec);
    Point queryPoint({5.81, 3.21});
    Point queryPoint1({1.01, 1.5});
    Point queryPoint2({1.81, 1.91});

    Point* closestPoint = naiveSearch.findNearestNeighbor(queryPoint);

    Point* neareastPoint = kdt.findNearestNeighbor(queryPoint);

    ASSERT_EQ(*neareastPoint, *closestPoint);
    closestPoint = naiveSearch.findNearestNeighbor(queryPoint1);
    ASSERT_EQ(*kdt.findNearestNeighbor(queryPoint1), *closestPoint);
    closestPoint = naiveSearch.findNearestNeighbor(queryPoint2);
    ASSERT_EQ(*kdt.findNearestNeighbor(queryPoint2), *closestPoint);

    vector<pair<double, double>> point;
    point.push_back(make_pair(2, 5.8));
    point.push_back(make_pair(0.8, 3.2));
    vector<Point> range0 = naiveSearch.rangeSearch(point);
    vector<Point> range1 = kdt.rangeSearch(point);
    // ASSERT_EQ(range0, range1);
    cout << "success!" << endl;
}
TEST_F(SmallKDTFixture, TIME_TEST) {
    // vector<pair<double, double>> test = kdt.getboundingBox();
    // cout << "first" << endl;
    // cout << test[0].first << "---" << test[0].second << endl;
    // cout << "second" << endl;
    // cout << test[1].first << "---" << test[1].second << endl;
    // cout << "end" << endl;
}
TEST_F(SmallKDTFixture, POINT_TEST) {
    Point queryPoint1({5.81, 3.21});
    Point queryPoint2({5.81, 3.21});
    Point queryPoint3({1, 2});
    ASSERT_EQ(queryPoint1.valueAt(0), 5.81);
    ASSERT_EQ(queryPoint1 == queryPoint2, true);
    ASSERT_EQ(queryPoint1 != queryPoint3, true);
    cout << queryPoint1 << endl;
}