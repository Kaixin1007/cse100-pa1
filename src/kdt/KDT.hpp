#ifndef KDT_HPP
#define KDT_HPP

#include <math.h>     // pow, abs
#include <algorithm>  // sort, max, min
#include <limits>     // numeric_limits<type>::max()
#include <vector>     // vector<typename>
#include "Point.hpp"

using namespace std;

class KDT {
  private:
    /** Inner class which defines a KD tree node */
    class KDNode {
      public:
        KDNode* left;
        KDNode* right;
        Point point;

        KDNode(Point point) : point(point) { left = right = nullptr; }
    };

    // root of KD tree
    KDNode* root;

    // number of dimension of data points
    unsigned int numDim;

    // smallest squared distance to query point so far
    double threshold;

    unsigned int isize;
    int iheight;

    // current nearest neighbor
    Point nearestNeighbor;

    // Extra Credit: smallest bounding box containing all points
    vector<pair<double, double>> boundingBox;

    // Extra Credit: result container
    // (Set during searching, and clear before another search)
    vector<Point> pointsInRange;

  public:
    /** Constructor of KD tree */
    KDT()
        : root(0),
          numDim(0),
          threshold(numeric_limits<double>::max()),
          isize(0),
          iheight(-1) {}

    /** Destructor of KD tree */
    virtual ~KDT() { deleteAll(root); }

    /** TODO */
    void build(vector<Point>& points) {
        root = buildSubtree(points, 0, points.size(), 0, iheight);
    }

    /** TODO */
    Point* findNearestNeighbor(Point& queryPoint) {
        threshold = numeric_limits<double>::max();
        findNNHelper(root, queryPoint, 0);
        return &nearestNeighbor;
    }

    /** Extra credit */
    vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
        pointsInRange.clear();

        return pointsInRange;
    }

    /** TODO */
    unsigned int size() const { return isize; }

    /** TODO */
    int height() const { return iheight + 1; }

  private:
    /** TODO */
    KDNode* buildSubtree(vector<Point>& F, unsigned int start, unsigned int end,
                         unsigned int curDim, int height) {
        if (F.size() == 0) return nullptr;
        if (F.size() == 1) {
            isize++;
            if (iheight < height) iheight = height;
            return new KDNode(F[0]);
        }
        sort(F.begin(), F.end(), CompareValueAt(curDim));
        int median = floor((start + end) / 2);
        vector<Point> leftresult(F.begin(), F.begin() + median);
        vector<Point> rightresult(F.begin() + median + 1, F.end());
        KDNode* leftSub = buildSubtree(leftresult, 0, median,
                                       (curDim + 1) % F[0].numDim, height + 1);
        KDNode* rightSub = buildSubtree(rightresult, 0, end - median - 1,
                                        (curDim + 1) % F[0].numDim, height + 1);
        KDNode* node = new KDNode(F[median]);
        node->left = leftSub;
        node->right = rightSub;
        isize++;
        return node;
    }

    /** TODO */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {
        // recursive to the botoom

        if (queryPoint.features[curDim] <= node->point.features[curDim]) {
            //  whether is the leaf point
            if (node->left != nullptr)
                findNNHelper(node->left, queryPoint,
                             (curDim + 1) % queryPoint.numDim);
            else
                updateThreshold(node, queryPoint);
            // recursive to the head
            // if the node less than threshold, go to the other side
            if (queryPoint.distToQuery >
                pow(queryPoint.features[curDim] - node->point.features[curDim],
                    2.0)) {
                updateThreshold(node, queryPoint);
                if (node->right != nullptr)
                    findNNHelper(node->right, queryPoint,
                                 (curDim + 1) % queryPoint.numDim);
            }
        } else {
            if (node->right != nullptr)
                findNNHelper(node->right, queryPoint,
                             (curDim + 1) % queryPoint.numDim);
            else
                updateThreshold(node, queryPoint);

            if (queryPoint.distToQuery >
                pow(queryPoint.features[curDim] - node->point.features[curDim],
                    2.0)) {
                updateThreshold(node, queryPoint);
                if (node->left != nullptr)
                    findNNHelper(node->left, queryPoint,
                                 (curDim + 1) % queryPoint.numDim);
            }
        }
    }

    /** TODO */
    static void deleteAll(KDNode* n) {
        if (n == nullptr) return;
        deleteAll(n->left);
        deleteAll(n->right);
        delete (n);
    }

    // Add your own helper methods here
    void updateThreshold(KDNode* node, Point& queryPoint) {
        double threshold_query = calDistToQuery(node, queryPoint);
        if (threshold > threshold_query) {
            queryPoint.setDistToQuery(node->point);
            nearestNeighbor = node->point;
            threshold = threshold_query;
        }
    }
    double calDistToQuery(KDNode* node, Point& queryPoint) {
        double result = 0;
        for (unsigned int i = 0; i < queryPoint.numDim; i++) {
            result +=
                pow(queryPoint.features[i] - node->point.features[i], 2.0);
        }
        return result;
    }
    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {
        if (curBB[curDim].first > queryRegion[curDim].second ||
            curBB[curDim].second < queryRegion[curDim].first) {
            // disjoint
            return;

        } else if (curBB[curDim].first > queryRegion[curDim].first &&
                   curBB[curDim].second < queryRegion[curDim].second) {
            // subset
        }

        else {
            // intersect
            return;
        }
        return;
    }

    void outPutSubtree(KDNode* node){
        if(node == nullptr)
            return;
        outPutSubtree(node->left);
        outPutSubtree(node->right);
        pointsInRange.push_back(node->point);
    }
};
#endif  // KDT_HPP
