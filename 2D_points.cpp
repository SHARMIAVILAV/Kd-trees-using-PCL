#include <bits/stdc++.h>
using namespace std;

const int k = 2;

struct Node
{
    int point[k];
    Node *left, *right;
};

Node* newNode(int arr[])
{
    Node* temp = new Node;
    for (int i = 0; i < k; i++)
        temp->point[i] = arr[i];

    temp->left = temp->right = NULL;
    return temp;
}

Node* insertRec(Node* root, int point[], unsigned depth)
{
    if (root == NULL)
        return newNode(point);

    unsigned cd = depth % k;

    if (point[cd] < root->point[cd])
        root->left = insertRec(root->left, point, depth + 1);
    else
        root->right = insertRec(root->right, point, depth + 1);

    return root;
}

Node* insert(Node* root, int point[])
{
    return insertRec(root, point, 0);
}

bool arePointsSame(int point1[], int point2[])
{
    for (int i = 0; i < k; ++i)
        if (point1[i] != point2[i])
            return false;

    return true;
}

bool searchRec(Node* root, int point[], unsigned depth)
{
    if (root == NULL)
        return false;
    if (arePointsSame(root->point, point))
        return true;

    unsigned cd = depth % k;

    if (point[cd] < root->point[cd])
        return searchRec(root->left, point, depth + 1);

    return searchRec(root->right, point, depth + 1);
}

bool search(Node* root, int point[])
{
    return searchRec(root, point, 0);
}

int squaredDistance(int point1[], int point2[])
{
    int distance = 0;
    for (int i = 0; i < k; ++i)
    {
        int diff = point1[i] - point2[i];
        distance += diff * diff;
    }
    return distance;
}

// Function to find the k-nearest neighbors of a given point in the KD tree within a specified distance limit
void findKNearestNeighbors(Node* root, int target[], int k, double limit, vector<pair<int, Node*>>& nearest, unsigned depth)
{
    if (root == NULL)
        return;

    int currentDist = squaredDistance(root->point, target);

    if (currentDist <= limit)
    {
        nearest.push_back({currentDist, root});
        sort(nearest.begin(), nearest.end());
        if (nearest.size() > k)
            nearest.pop_back();
    }

    unsigned cd = depth % k;

    if (target[cd] < root->point[cd])
    {
        findKNearestNeighbors(root->left, target, k, limit, nearest, depth + 1);
        if (target[cd] + sqrt(limit) >= root->point[cd])
            findKNearestNeighbors(root->right, target, k, limit, nearest, depth + 1);
    }
    else
    {
        findKNearestNeighbors(root->right, target, k, limit, nearest, depth + 1);
        if (target[cd] - sqrt(limit) <= root->point[cd])
            findKNearestNeighbors(root->left, target, k, limit, nearest, depth + 1);
    }
}

int main()
{
    Node* root = NULL;
    int points[][k] = {{3, 6}, {17, 15}, {13, 15}, {6, 12}, {9, 1}, {2, 7}, {10, 19}};
    int n = sizeof(points) / sizeof(points[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, points[i]);

    int target[] = {12, 19};
    int k_nearest = 5;
    double limit = DBL_MAX; // No limit initially
    vector<pair<int, Node*>> nearest;

    findKNearestNeighbors(root, target, k_nearest, limit, nearest, 0);

    cout << "K Nearest Neighbors within distance " << sqrt(limit) << " of the target point (" << target[0] << ", " << target[1] << "):\n";

    for (const auto& p : nearest)
    {
        cout << "(" << p.second->point[0] << ", " << p.second->point[1] << ") - Distance: " << sqrt(p.first) << "\n";
    }

    return 0;
}
