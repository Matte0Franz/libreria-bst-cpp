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

Node* findMin(Node* root){
    if (root == nullptr){
        return nullptr;
    }
    Node* current = root;
    while (current -> lchild != nullptr){
        current = current -> lchild;
    }
    return current;
}

Node* findMax(Node* root){
    if (root == nullptr){
        return nullptr;
    }
    Node* current = root;
    while (current -> rchild != nullptr){
        current = current -> rchild;
    }
    return current;
}

int countNodes(Node* root){
    if(root == nullptr){
        return 0;
    }
    return 1 + countNodes(root->lchild) + countNodes(root->rchild);
}

int countLeaves(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->lchild == nullptr && root->rchild == nullptr) {
        return 1;
    }
    return countLeaves(root->lchild) + countLeaves(root->rchild);
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

    Node* min = findMin(root);

    if (min != nullptr){
        cout << "minimo: " << min->data << endl;
    }else{
        cout << "vuoto" << endl;
    }

    Node* max = findMax(root);

    if (max != nullptr){
        cout << "massimo: " << max->data << endl;
    }else{
        cout << "vuoto" << endl;
    }

    cout << "nodi: " << countNodes(root) << endl;
    cout << "foglie: " << countLeaves(root) << endl;
    
    return 0;
}
