#ifndef TREE_H
#define TREE_H
#include <initializer_list>
/**
 * Implementation of the Abstract Data Type (ADT) "Binary Search Tree" (BST).
 *
 * The BinaryTree class provides basic operations for working with a binary search tree:
 *
 * Constructors:
 *  - BinaryTree(): Initializes an empty binary tree.
 *  - BinaryTree(std::initializer_list<T> list): Constructs a binary tree from an initializer list of elements.
 *  - BinaryTree(const BinaryTree &other): Copy constructor, creates a deep copy of another binary tree.
 *  - BinaryTree(BinaryTree &&other) noexcept: Move constructor, transfers ownership of resources from another tree.
 *
 * Destructor:
 *  - ~BinaryTree(): Destroys the binary tree and deallocates all dynamically allocated nodes.
 *
 * Overloaded Operators:
 *  - BinaryTree& operator=(const BinaryTree &other): Copy assignment operator, deep copies another binary tree.
 *  - BinaryTree& operator=(BinaryTree &&other) noexcept: Move assignment operator, transfers ownership from another tree.
 *
 * Public Methods:
 *  - void Insert(const T &element): Inserts an element into the binary search tree, maintaining BST properties.
 *  - void Clear(): Removes all nodes from the tree, effectively clearing it.
 *  - void ShowInOrder(): Prints the elements of the tree in in-order traversal (left subtree, root, right subtree).
 *  - [[nodiscard]] int Size() const: Returns the number of nodes in the tree.
 *  - int Depth(): Returns the depth of the tree (the longest path from the root to a leaf node).
 *  - bool IsEmpty(): Returns true if the tree is empty, false otherwise.
 *  - bool IsBalanced(): Returns true if the tree is balanced (the difference between the depths of any two subtrees is no more than one).
 *  - const T &FindElement(const T &element): Finds and returns a reference to the specified element. Throws an exception if not found.
 *  - const T &FindMaxElement(): Returns a reference to the maximum element in the tree.
 *  - const T &FindMinElement(): Returns a reference to the minimum element in the tree.
 *  - void Remove(const T &element): Removes the specified element from the tree, if it exists.
 *
 * Time Complexity:
 *  - Insert: O(log n) on average, O(n) in the worst case (for unbalanced trees).
 *  - Clear: O(n) - Each node is visited and deleted.
 *  - ShowInOrder: O(n) - Visits every node in the tree once.
 *  - Size: O(n) - Recursively counts the number of nodes.
 *  - Depth: O(n) - Recursively calculates the depth of the tree.
 *  - IsEmpty: O(1) - Simply checks if the root is null.
 *  - IsBalanced: O(n) - Checks the depth of each subtree recursively.
 *  - FindElement: O(log n) on average, O(n) in the worst case.
 *  - FindMaxElement: O(log n) on average, O(n) in the worst case.
 *  - FindMinElement: O(log n) on average, O(n) in the worst case.
 *  - Remove: O(log n) on average, O(n) in the worst case.
 *
 * Features:
 * - The Binary Search Tree maintains its elements in sorted order, allowing efficient searching, insertion, and deletion operations.
 * - The tree can become unbalanced, leading to degraded performance for certain operations.
 *
 * @author Vlas Pototskyi
 */
template<typename T>
class BinaryTree {
    struct Node {
        T data;
        Node *left;
        Node *right;

        explicit Node(const T &elements, Node *left = nullptr, Node *right = nullptr) : data(elements), left(left),
            right(right) {
        }
    };

    Node *root;

    void Copy(Node *&tree1, const Node *tree2);

    void RemoveSubTree(Node *other);

    void InOrder(Node *node);

    int Size(Node *node) const;

    int DepthInTree(Node *node);

    bool IsBalancedInTree(Node *node);

    Node *FindMinimum(Node *node);

    Node *Delete(Node *node, const T &element);

public:
    // --- Constructors ---
    BinaryTree();

    BinaryTree(std::initializer_list<T> list);

    BinaryTree(const BinaryTree &other);

    BinaryTree(BinaryTree &&other) noexcept;

    // --- Destructor ---
    ~BinaryTree();

    // --- Overload operators ---
    BinaryTree &operator=(const BinaryTree &other);

    BinaryTree &operator=(BinaryTree &&other) noexcept;

    // --- Add elements ---
    void Insert(const T &element);

    // --- Remove methods ---
    void Clear();

    // Show Binary Tree elements
    void ShowInOrder();

    // --- Check size methods ---
    [[nodiscard]] int Size() const;

    int Depth();

    bool IsEmpty();

    bool IsBalanced();

    // --- Find methods ---
    const T &FindElement(const T &element);

    const T &FindMaxElement();

    const T &FindMinElement();

    // --- Remove merhod ---
    void Remove(const T &element);
};

template<typename T>
void BinaryTree<T>::Copy(Node *&tree1, const Node *tree2) {
    if (tree2 == nullptr) {
        return;
    }
    tree1 = new Node{tree2->data, nullptr, nullptr};
    if (tree2->right != nullptr) {
        Copy(tree1->right, tree2->right);
    }
    if (tree2->left != nullptr) {
        Copy(tree1->left, tree2->left);
    }
}

template<typename T>
void BinaryTree<T>::RemoveSubTree(Node *other) {
    if (other == nullptr) {
        return;
    }
    if (other->left != nullptr) {
        RemoveSubTree(other->left);
    }
    if (other->right != nullptr) {
        RemoveSubTree(other->right);
    }
    delete other;
}

template<typename T>
void BinaryTree<T>::InOrder(Node *node) {
    if (node == nullptr) {
        return;
    }
    if (node->left != nullptr) {
        InOrder(node->left);
    }
    std::cout << node->data << " ";
    if (node->right != nullptr) {
        InOrder(node->right);
    }
}

template<typename T>
int BinaryTree<T>::Size(Node *node) const {
    return node != nullptr ? Size(node->left) + 1 + Size(node->right) : 0;
}

template<typename T>
int BinaryTree<T>::DepthInTree(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    const int rDepth = DepthInTree(node->right);
    const int lDepth = DepthInTree(node->left);
    return 1 + std::max(rDepth, lDepth); // one it`s a root
}

template<typename T>
bool BinaryTree<T>::IsBalancedInTree(Node *node) {
    if (node == nullptr) {
        return true;
    }
    const int rDepth = DepthInTree(node->right);
    const int lDepth = DepthInTree(node->left);
    if (abs(rDepth - lDepth) <= 1 && IsBalancedInTree(node->right) &&
        IsBalancedInTree(node->left)) {
        return true;
    }
    return false;
}

template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::FindMinimum(Node *node) {
    while (node != nullptr & node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template<typename T>
typename BinaryTree<T>::Node *BinaryTree<T>::Delete(Node *node, const T &element) {
    if (node == nullptr) {
        return node;
    }
    if (element > node->data) {
        node->right = Delete(node->right, element);
    } else if (element < node->data) {
        node->left = Delete(node->left, element);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            Node *temp = node->right;
            delete node;
            node = temp;
        } else if (node->right == nullptr) {
            Node *temp = node->left;
            delete node;
            node = temp;
        } else {
            Node *temp = FindMinimum(node->right);
            node->data = temp->data;
            node->right = Delete(node->right, temp->data);
        }
    }
    return node;
}

template<typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {
}

template<typename T>
BinaryTree<T>::BinaryTree(std::initializer_list<T> list) : root(nullptr) {
    for (const T *element = list.begin(); element != list.end(); ++element) {
        Insert(*element);
    }
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree &other) : root(nullptr) {
    if (this != &other) {
        Clear();
        Copy(this->root, other.root);
    }
}

template<typename T>
BinaryTree<T>::BinaryTree(BinaryTree &&other) noexcept {
    if (this != &other) {
        Clear();
        root = other.root;
        other.root = nullptr;
    }
}

template<typename T>
BinaryTree<T>::~BinaryTree() {
    Clear();
}

template<typename T>
BinaryTree<T> &BinaryTree<T>::operator=(const BinaryTree &other) {
    if (this != &other) {
        Clear();
        Copy(this->root);
    }
    return *this;
}

template<typename T>
BinaryTree<T> &BinaryTree<T>::operator=(BinaryTree &&other) noexcept {
    if (this != &other) {
        Clear();
        root = other.root;
        other.root = nullptr;
    }
    return *this;
}

template<typename T>
void BinaryTree<T>::Insert(const T &element) {
    if (root == nullptr) {
        root = new Node{element, nullptr, nullptr};
    }
    Node *current = root;
    while (current != nullptr) {
        if (current->data == element) {
            return;
        }
        if (element > current->data) {
            if (current->right == nullptr) {
                current->right = new Node{element, nullptr, nullptr};
                return;
            }
            current = current->right;
        }
        if (element < current->data) {
            if (current->left == nullptr) {
                current->left = new Node{element, nullptr, nullptr};
                return;
            }
            current = current->left;
        }
    }
}

template<typename T>
void BinaryTree<T>::Clear() {
    RemoveSubTree(root);
}

template<typename T>
void BinaryTree<T>::ShowInOrder() {
    InOrder(root);
}

template<typename T>
int BinaryTree<T>::Size() const {
    return Size(root);
}

template<typename T>
int BinaryTree<T>::Depth() {
    return DepthInTree(root);
}

template<typename T>
bool BinaryTree<T>::IsEmpty() {
    return root == nullptr;
}

template<typename T>
bool BinaryTree<T>::IsBalanced() {
    return IsBalancedInTree(root);
}

template<typename T>
const T &BinaryTree<T>::FindElement(const T &element) {
    if (root == nullptr) {
        throw std::runtime_error("The tree is empty.");
    }
    Node *current = root;
    while (current != nullptr) {
        if (current->data == element) {
            return element;
        }
        if (element > current->data) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    throw std::runtime_error("Element not found.");
}

template<typename T>
const T &BinaryTree<T>::FindMaxElement() {
    if (root == nullptr) {
        throw std::runtime_error("The tree is empty.");
    }
    Node *current = root;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current->data;
}

template<typename T>
const T &BinaryTree<T>::FindMinElement() {
    if (root == nullptr) {
        throw std::runtime_error("The tree is empty.");
    }
    Node *current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->data;
}

template<typename T>
void BinaryTree<T>::Remove(const T &element) {
    root = Delete(root, element);
}


#endif
