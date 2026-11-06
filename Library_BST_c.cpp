#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* lchild;
    Node* rchild;
    Node(int k) {
        data = k;
        lchild = nullptr;
        rchild = nullptr;
    }
};
Node* insert(Node* root, int k) {
    if (root == nullptr) {
        return new Node(k);
    }
    Node* current = root;
    Node* dad = nullptr;
    while (current != nullptr) {
        dad = current;
        if (k < current->data) {
            current = current->lchild;
        } else if (k > current->data) {
            current = current->rchild;
        } else {
            // Il valore esiste già: l'albero rimane invariato.
            return root;
        }
    }
    if (k < dad->data) {
        dad->lchild = new Node(k);
    } else {
        dad->rchild = new Node(k);
    }
    return root;
}
class Node {
private:
    int data;
    Node* rchild;
    Node* lchild;

public:
    Node(int k) {
        data = k;
        rchild = lchild = nullptr;
    }

    int getData() const {
        return data;
    }

    Node* getLchild() const {
        return lchild;
    }

    Node* getRchild() const {
        return rchild;
    }

    void setData(int key) {
        data = key;
    }

    void setLchild(Node* newLchild) {
        lchild = newLchild;
    }

    void setRchild(Node* newRchild) {
        rchild = newRchild;
    }

    bool isLeaf() {
        return (lchild == nullptr && rchild == nullptr);
    }
};

class BST {
private:
    Node* root;
    int nodeCount;

    bool searchNode(Node* node, int value) const {
        if (node == nullptr) {
            return false;
        }
        if (value == node->getData()) {
            return true;
        }
        if (value < node->getData()) {
            return searchNode(node->getLchild(), value);
        }
        return searchNode(node->getRchild(), value);
    }

    void printInOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        printInOrder(node->getLchild());
        cout << node->getData() << " ";
        printInOrder(node->getRchild());
    }

    int nodeHeight(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = nodeHeight(node->getLchild());
        int rightHeight = nodeHeight(node->getRchild());
        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        }
        return rightHeight + 1;
    }

    Node* removeNode(Node* node, int value, bool& found) {
        if (node == nullptr) {
            return nullptr;
        }
        if (value < node->getData()) {
            node->setLchild(removeNode(node->getLchild(), value, found));
        } else if (value > node->getData()) {
            node->setRchild(removeNode(node->getRchild(), value, found));
        } else {
            found = true;
            if (node->getLchild() == nullptr) {
                Node* child = node->getRchild();
                delete node;
                return child;
            }
            if (node->getRchild() == nullptr) {
                Node* child = node->getLchild();
                delete node;
                return child;
            }
            Node* successor = node->getRchild();
            while (successor->getLchild() != nullptr) {
                successor = successor->getLchild();
            }
            node->setData(successor->getData());
            node->setRchild(removeNode(node->getRchild(), successor->getData(), found));
        }
        return node;
    }

    void deleteNodes(Node* node) {
        if (node == nullptr) {
            return;
        }
        deleteNodes(node->getLchild());
        deleteNodes(node->getRchild());
        delete node;
    }

    int countLeaves(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        if (node->isLeaf()) {
            return 1;
        }
        return countLeaves(node->getLchild()) + countLeaves(node->getRchild());
    }

public:
    BST() {
        root = nullptr;
        nodeCount = 0;
    }

    bool isEmpty() {
        return root == nullptr;
    }

    int size() {
        return nodeCount;
    }

    bool insert(int value) {
        if (root == nullptr) {
            root = new Node(value);
            nodeCount++;
            return true;
        }
        Node* current = root;
        while (true) {
            if (value == current->getData()) {
                return false;
            }
            if (value < current->getData()) {
                if (current->getLchild() == nullptr) {
                    current->setLchild(new Node(value));
                    nodeCount++;
                    return true;
                }
                current = current->getLchild();
            } else {
                if (current->getRchild() == nullptr) {
                    current->setRchild(new Node(value));
                    nodeCount++;
                    return true;
                }
                current = current->getRchild();
            }
        }
    }

    bool search(int value) const {
        return searchNode(root, value);
    }

    void inOrder() const {
        printInOrder(root);
    }

    int height() const {
        return nodeHeight(root);
    }

    int minimum() const {
        if (root == nullptr) {
            return -1;
        }
        Node* current = root;
        while (current->getLchild() != nullptr) {
            current = current->getLchild();
        }
        return current->getData();
    }

    int maximum() const {
        if (root == nullptr) {
            return -1;
        }
        Node* current = root;
        while (current->getRchild() != nullptr) {
            current = current->getRchild();
        }
        return current->getData();
    }

    bool remove(int value) {
        bool found = false;
        root = removeNode(root, value, found);
        if (found) {
            nodeCount--;
        }
        return found;
    }

    void clear() {
        deleteNodes(root);
        root = nullptr;
        nodeCount = 0;
    }

    int countLeaves() const {
        return countLeaves(root);
    }
int main() {
    Node* root = new Node(2);
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 3); // doppione: non modifica l'albero
    title("Part A: Node");
    Node a(50);
    Node b(30);

    cout << "a: " << a.getData()
         << " leaf: " << (a.isLeaf() ? "yes" : "no") << endl;

    a.setLchild(&b);

    cout << "a has left child " << a.getLchild()->getData()
         << ", leaf: " << (a.isLeaf() ? "yes" : "no") << endl;

    cout << "a has right child: "
         << (a.getRchild() == nullptr ? "no" : "yes") << endl;

    b.setData(35);

    cout << "after b.setData(35), a's left child has value "
         << a.getLchild()->getData() << endl;


    title("Part B: BST");
    BST t;

    cout << "empty tree: " << (t.isEmpty() ? "yes" : "no")
         << ", nodes: " << t.size() << endl;

    int keys[] = {50, 30, 70, 20, 40, 60, 80, 45};

    for (int k : keys) {
        t.insert(k);
    }

    cout << "trying to insert 40 again: "
         << (t.insert(40) ? "inserted" : "already present") << endl;

    cout << "nodes: " << t.size() << ", height: " << t.height() << endl;

    cout << "in order: ";
    t.inOrder();
    cout << endl;

    cout << "searching for 60: "
         << (t.search(60) ? "found" : "not found") << endl;

    cout << "searching for 65: "
         << (t.search(65) ? "found" : "not found") << endl;

    cout << "minimum: " << t.minimum()
         << ", maximum: " << t.maximum() << endl;


    title("Part C: removal and memory");
    cout << "leaves: " << t.countLeaves() << endl;

    cout << "removing 20 (leaf): "
         << (t.remove(20) ? "ok" : "not found")
         << ", nodes: " << t.size() << endl;

    cout << "removing 40 (one child): "
         << (t.remove(40) ? "ok" : "not found")
         << ", nodes: " << t.size() << endl;

    cout << "removing 50 (two children): "
         << (t.remove(50) ? "ok" : "not found")
         << ", nodes: " << t.size() << endl;

    cout << "removing 99 (absent): "
         << (t.remove(99) ? "ok" : "not found")
         << ", nodes: " << t.size() << endl;

    cout << "in order: ";
    t.inOrder();
    cout << endl;

    cout << "height: " << t.height()
         << ", leaves: " << t.countLeaves() << endl;

    cout << "keys between 30 and 70 (bonus): "
         << t.countRange(30, 70) << endl;

    t.clear();

    cout << "after clear -> empty: " << (t.isEmpty() ? "yes" : "no")
         << ", nodes: " << t.size()
         << ", height: " << t.height()
         << ", minimum: " << t.minimum() << endl;

    t.clear();
    t.insert(5);

    cout << "after a new insertion, nodes: " << t.size()
         << ", minimum: " << t.minimum() << endl;

    t.clear();
    return 0;
}
