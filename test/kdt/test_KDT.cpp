#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
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
        vec.emplace_back(Point({5.7, 3.1}));
        vec.emplace_back(Point({1.8, 1.9}));
        vec.emplace_back(Point({4.4, 2.2}));
        kdt.build(vec);
        cout << kdt.height() << endl;
    }
};
double randNum(double min, double max) {
    return (max - min) * ((double)rand() / (double)RAND_MAX) + min;
}

/** Returns a vector of random double values with range [min, max] */
vector<double> randNums(unsigned int size, double min, double max) {
    vector<double> result;
    for (unsigned int i = 0; i < size; i++) {
        result.push_back(randNum(min, max));
    }
    return result;
}

/** Returns a vector of points with given dimensions of given size */
vector<Point> randomPoints(unsigned int numPoints, unsigned int numDim,
                           double min, double max) {
    vector<Point> result;
    for (unsigned int i = 0; i < numPoints; i++) {
        result.push_back(Point(randNums(numDim, min, max)));
    }
    return result;
}

/** Returns a random valid range with number of given dimensions
 *  The length of range at each dimension is given by length
 */
vector<pair<double, double>> rangeRange(unsigned int numDim, int length,
                                        double min, int max) {
    vector<pair<double, double>> range;
    for (unsigned int i = 0; i < numDim; i++) {
        double rand = randNum(min, max - length);
        range.push_back(make_pair(rand, rand + length));
    }
    return range;
}

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
    point.push_back(make_pair(1, 10));
    point.push_back(make_pair(1.0, 10));
    vector<Point> range0 = naiveSearch.rangeSearch(point);
    vector<Point> range1 = kdt.rangeSearch(point);
    // ASSERT_EQ(range0, range1);
    cout << "success!" << endl;
}
TEST_F(SmallKDTFixture, RANGE_SEARCH) {
    const int NUM_DATA = 100;    // number of random Build data
    const int NUM_TEST = 10;     // number of tests
    const int NUM_DIM = 3;       // number of dimension of random data
    const double MIN_VAL = 0;    // lower bound of random data features
    const double MAX_VAL = 10;   // upper bound of random data features
    const double RANGE_LEN = 3;  // length of random range (EC)
    vector<Point> buildData = randomPoints(NUM_DATA, NUM_DIM, MIN_VAL, MAX_VAL);
    vector<Point> testData = randomPoints(NUM_TEST, NUM_DIM, MIN_VAL, MAX_VAL);
    KDT kdtree;
    NaiveSearch naiveSearch;
    kdtree.build(buildData);
    naiveSearch.build(buildData);
    vector<vector<pair<double, double>>> ranges;

    for (int i = 0; i < NUM_TEST; i++) {
        ranges.push_back(rangeRange(NUM_DIM, RANGE_LEN, MIN_VAL, MAX_VAL));
    }
    for (vector<pair<double, double>>& range : ranges) {
        vector<Point> range1 = naiveSearch.rangeSearch(range);
        vector<Point> range0 = kdtree.rangeSearch(range);

        cout << "kdtree:";
        for (int i = 0; i < range0.size(); i++) cout << range0[i];
        cout << endl;
        cout << "naiveSearch:";
        for (int i = 0; i < range1.size(); i++) cout << range1[i];
        cout << endl;
        cout << "----------------------------------" << endl;
    }

    cout << "end!" << endl;
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
