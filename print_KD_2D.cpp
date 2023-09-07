#include <iostream>
#include <vector>

const int k = 2;

struct Node
{
    int point[k];
    Node* left;
    Node* right;
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

void printKDTree(Node* root, int depth = 0, char ch = ' ')
{
    if (root == NULL)
        return;

    // Print the current node
    std::cout << "Depth " << depth << ", " << ch << ": (" << root->point[0] << ", " << root->point[1] << ")\n";

    // Recursively print the left and right subtrees
    printKDTree(root->left, depth + 1, 'L');
    printKDTree(root->right, depth + 1, 'R');
}

int main()
{
    Node* root = NULL;
    int points[][k] = {{3, 6}, {17, 15}, {13, 15}, {6, 12}, {9, 1}, {2, 7}, {10, 19}};
    int n = sizeof(points) / sizeof(points[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, points[i]);

    printKDTree(root);

    return 0;
}
