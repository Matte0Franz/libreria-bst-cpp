#include <iostream>
using namespace std;

struct Nodo {
    int data;
    Nodo* lchild;
    Nodo* rchild;
    Nodo(int val) {
        data = val;
        lchild = nullptr;
        rchild = nullptr;
    }
};
Nodo* inserisci(Nodo* root, int val) {
    if (root == nullptr) {
        return new Nodo(val);
    }
    Nodo* current = root;
    Nodo* dad = nullptr;
    while (current != nullptr) {
        dad = current;
        if (val < current->data) {
            current = current->lchild;
        } else if (val > current->data) {
            current = current->rchild;
        } else {
            // Il valore esiste già: l'albero rimane invariato.
            return root;
        }
    }
    if (val < dad->data) {
        dad->lchild = new Nodo(val);
    } else {
        dad->rchild = new Nodo(val);
    }
    return root;
}
int main() {
    Nodo* root = new Nodo(2);
    root = inserisci(root, 5);
    root = inserisci(root, 3);
    root = inserisci(root, 7);
    root = inserisci(root, 3); // doppione: non modifica l'albero
    return 0;
}