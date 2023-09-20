#include <iostream>
#include <cmath>

using namespace std;

struct Point {
    double x;
    double y;
};

struct Segment {
    Point start;
    Point end;
};

struct AVLNode {
    Segment segment;
    AVLNode* left;
    AVLNode* right;
    int height;
};

AVLNode* createNode(Segment segment) {
    AVLNode* newNode = new AVLNode();
    newNode->segment = segment;
    newNode->left = newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}

int getHeight(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int getBalanceFactor(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void updateHeight(AVLNode* node) {
    if (node == nullptr)
        return;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

AVLNode* rotateRight(AVLNode* node) {
    AVLNode* newRoot = node->left;
    AVLNode* newChild = newRoot->right;

    newRoot->right = node;
    node->left = newChild;

    updateHeight(node);    
    updateHeight(newRoot); 

    return newRoot;
}

AVLNode* rotateLeft(AVLNode* node) {
    AVLNode* newRoot = node->right;
    AVLNode* newChild = newRoot->left;

    newRoot->left = node;
    node->right = newChild;

    updateHeight(node);    
    updateHeight(newRoot); 

    return newRoot;
}

AVLNode* balanceNode(AVLNode* node) {
    if (node == nullptr)
        return nullptr;

    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

AVLNode* insertSegment(AVLNode* root, Segment segment) {
    if (root == nullptr)
        return createNode(segment);

    if (segment.end.x < root->segment.end.x)
        root->left = insertSegment(root->left, segment);
    else
        root->right = insertSegment(root->right, segment);

    return balanceNode(root);
}


bool doSegmentsIntersect(Segment segment1, Segment segment2) {
    double x1 = segment1.start.x, y1 = segment1.start.y;
    double x2 = segment1.end.x, y2 = segment1.end.y;
    double x3 = segment2.start.x, y3 = segment2.start.y;
    double x4 = segment2.end.x, y4 = segment2.end.y;

    double direction1 = (x4 - x3) * (y1 - y3) - (x1 - x3) * (y4 - y3);
    double direction2 = (x4 - x3) * (y2 - y3) - (x2 - x3) * (y4 - y3);
    double direction3 = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
    double direction4 = (x2 - x1) * (y4 - y1) - (x4 - x1) * (y2 - y1);

    if (((direction1 > 0 && direction2 < 0) || (direction1 < 0 && direction2 > 0)) &&
        ((direction3 > 0 && direction4 < 0) || (direction3 < 0 && direction4 > 0))) {
        return true;
    }

    return false;
}

Point tionPoint(Segment segment1, Segment segment2) {
    double x1 = segment1.start.x, y1 = segment1.start.y;
    double x2 = segment1.end.x, y2 = segment1.end.y;
    double x3 = segment2.start.x, y3 = segment2.start.y;
    double x4 = segment2.end.x, y4 = segment2.end.y;

    double intersectionX = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) /
                           ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

    double intersectionY = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) /
                           ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4));

    Point intersectionPoint;
    intersectionPoint.x = intersectionX;
    intersectionPoint.y = intersectionY;

    return intersectionPoint;
}

Point tionInAVLTree(AVLNode* root, Segment segment) {
    if (root == nullptr)
        return {0.0, 0.0};

    Segment extendedSegment;
    extendedSegment.start.x = segment.start.x;
    extendedSegment.start.y = segment.start.y;
    extendedSegment.end.x = segment.end.x + 1.0; 
    extendedSegment.end.y = segment.end.y;

    if (doSegmentsIntersect(root->segment, extendedSegment))
        return tionPoint(root->segment, extendedSegment);

    if (segment.end.x < root->segment.start.x)
        return tionInAVLTree(root->left, segment);
    else if (segment.start.x > root->segment.end.x)
        return tionInAVLTree(root->right, segment);
    else {
        Point intersectionPoint = tionInAVLTree(root->left, segment);
        if (intersectionPoint.x != 0.0 || intersectionPoint.y != 0.0)
            return intersectionPoint;
        return tionInAVLTree(root->right, segment);
    }
}


int main() {
    AVLNode* root = nullptr;

    Segment segment1 = {{1.0, 1.0}, {5.0, 5.0}};
    Segment segment2 = {{2.0, 2.0}, {4.0, 4.0}};
    Segment segment3 = {{3.0, 1.0}, {3.0, 5.0}};
    Segment segment4 = {{6.0, 6.0}, {8.0, 8.0}};

    root = insertSegment(root, segment1);
    root = insertSegment(root, segment2);
    root = insertSegment(root, segment3);
    root = insertSegment(root, segment4);

    Point intersectionPoint = tionInAVLTree(root, segment1);

    cout << "Intersection Point: (" << intersectionPoint.x << ", " << intersectionPoint.y << ")" << endl;

    return 0;
}
