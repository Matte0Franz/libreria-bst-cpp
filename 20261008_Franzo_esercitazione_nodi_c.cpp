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

// Cerca un valore nel BST senza modificare l'albero.
bool search(Node* root, int k) {
    Node* current = root;

    while (current != nullptr) {
        if (k == current->data) {
            return true;
        } else if (k < current->data) {
            current = current->lchild;
        } else {
            current = current->rchild;
        }
    }

    return false;
}

int main() {
    Node* root = new Node(2);
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 3); // doppione: non modifica l'albero

    int valoreDaCercare = 3;
    if (search(root, valoreDaCercare)) {
        cout << "Valore trovato." << endl;
    } else {
        cout << "Valore non trovato." << endl;
    }

    return 0;
}
