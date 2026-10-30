#include <algorithm>
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

int height(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftHeight = height(root->lchild);
    int rightHeight = height(root->rchild);

    return 1 + max(leftHeight, rightHeight);
}

void inOrder(Node* root) {
    if (root == nullptr) {
        return;
    }

    inOrder(root->lchild);
    cout << root->data << " ";
    inOrder(root->rchild);
}

void printRange(Node* root, int low, int high) {
    if (root == nullptr || low > high) {
        return;
    }

    if (low < root->data) {
        printRange(root->lchild, low, high);
    }

    if (low <= root->data && root->data <= high) {
        cout << root->data << " ";
    }

    if (high > root->data) {
        printRange(root->rchild, low, high);
    }
}

int main() {
    Node* root = new Node(2);

    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 3); // Doppione: non modifica l'albero.

    cout << "Altezza: " << height(root) << endl;

    cout << "Inorder: ";
    inOrder(root);
    cout << endl;

    cout << "Chiavi tra 3 e 6: ";
    printRange(root, 3, 6);
    cout << endl;

    return 0;
}
