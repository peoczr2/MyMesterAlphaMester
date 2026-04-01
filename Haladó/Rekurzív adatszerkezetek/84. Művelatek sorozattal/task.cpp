/*
Megoldási ötlet:
A sorozat pozíció alapú műveleteihez implicit treap kell. A csomópontokban a részfa méretét tartjuk nyilván, így
a k-adik elem, a beszúrás és a törlés is két split és egy merge művelettel megoldható.

A módosítás egyszerűen a k-adik csomópont értékének átírása. A teljes sorozat kiolvasása inorder bejárással történik.
*/
/*
Hint 1: || Pozíció szerinti műveletekhez nem kulcs, hanem a részfa mérete alapján kell vágni. ||
Hint 2: || A beszúrás, törlés és módosítás mind két splitre vezethető vissza. ||
Hint 3: || A k-adik elem az implicit treapben a részfa-méretekből közvetlenül megtalálható. ||
*/

#include "sorozat.h"
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

struct Node {
    int value;
    int pr;
    int sz;
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(int value, int pr) : value(value), pr(pr), sz(1) {}
};

static mt19937 rng(1234567);
static Node* root = nullptr;

static int size(Node* node) { return node ? node->sz : 0; }
static void pull(Node* node) { if (node) node->sz = 1 + size(node->left) + size(node->right); }

static void split(Node* node, int count, Node*& left, Node*& right) {
    if (!node) { left = right = nullptr; return; }
    if (size(node->left) >= count) {
        split(node->left, count, left, node->left);
        right = node;
        pull(right);
    } else {
        split(node->right, count - size(node->left) - 1, node->right, right);
        left = node;
        pull(left);
    }
}

static Node* merge(Node* left, Node* right) {
    if (!left || !right) return left ? left : right;
    if (left->pr > right->pr) {
        left->right = merge(left->right, right);
        pull(left);
        return left;
    }
    right->left = merge(left, right->left);
    pull(right);
    return right;
}

static Node* buildNode(int value) {
    return new Node(value, static_cast<int>(rng()));
}

static int kth(Node* node, int k) {
    int leftSize = size(node->left);
    if (k <= leftSize) return kth(node->left, k);
    if (k == leftSize + 1) return node->value;
    return kth(node->right, k - leftSize - 1);
}

static void setKth(Node* node, int k, int value) {
    int leftSize = size(node->left);
    if (k <= leftSize) setKth(node->left, k, value);
    else if (k == leftSize + 1) node->value = value;
    else setKth(node->right, k - leftSize - 1, value);
}

static void collect(Node* node, vector<int>& result) {
    if (!node) return;
    collect(node->left, result);
    result.push_back(node->value);
    collect(node->right, result);
}

void Beszur(int i, int x) {
    Node *a, *b;
    split(root, i - 1, a, b);
    root = merge(merge(a, buildNode(x)), b);
}

int Kadik(int k) {
    return kth(root, k);
}

void Torol(int k) {
    Node *a, *b, *c;
    split(root, k - 1, a, b);
    split(b, 1, b, c);
    root = merge(a, c);
}

void Modosit(int k, int x) {
    setKth(root, k, x);
}

int Elemszam() {
    return size(root);
}
