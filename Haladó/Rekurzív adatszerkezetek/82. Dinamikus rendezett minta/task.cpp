/*
Megoldási ötlet:
A műveletek egy rendezett halmazon kérnek beszúrást, sorszám szerinti kiválasztást és ranglekérdezést. Erre egy
kulcs szerint rendezett kiegyensúlyozott BST, például treap elég.

Az Adat(x) csak akkor hat, ha x még sosem szerepelt. A Hanyadik(x) a kulcs rangját adja, ha jelen van, különben 0.
A csomópontokban a részfájuk méretét tároljuk, ezért a k-adik elem és a rang is logaritmikus időben lekérdezhető.
*/
/*
Hint 1: || A halmazhoz tartozó elemeket kulcs szerint rendezd egy BST-ben. ||
Hint 2: || Minden csúcsban tartsd nyilván a részfa elemszámát. ||
Hint 3: || A k-adik elem és az x rangja ugyanabból a szerkezetből jön ki. ||
*/

#include "rendminta.h"
#include <algorithm>
#include <random>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
    int key;
    int pr;
    int sz;
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(int key, int pr) : key(key), pr(pr), sz(1) {}
};

static mt19937 rng(71236721);
static Node* root = nullptr;
static unordered_set<int> seen;

static int size(Node* node) { return node ? node->sz : 0; }

static void pull(Node* node) {
    if (node) node->sz = 1 + size(node->left) + size(node->right);
}

static void split(Node* node, int key, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    if (node->key < key) {
        split(node->right, key, node->right, right);
        left = node;
        pull(left);
    } else {
        split(node->left, key, left, node->left);
        right = node;
        pull(right);
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

static bool contains(Node* node, int key) {
    while (node) {
        if (key == node->key) return true;
        node = key < node->key ? node->left : node->right;
    }
    return false;
}

static void insertKey(int key) {
    Node *a, *b;
    split(root, key, a, b);
    root = merge(merge(a, new Node(key, static_cast<int>(rng()))), b);
}

static void eraseKey(int key) {
    Node *a, *b, *c;
    split(root, key, a, b);
    split(b, key + 1, b, c);
    root = merge(a, c);
}

static int kth(Node* node, int k) {
    int leftSize = size(node->left);
    if (k <= leftSize) return kth(node->left, k);
    if (k == leftSize + 1) return node->key;
    return kth(node->right, k - leftSize - 1);
}

static int rankOf(Node* node, int key, int passed = 0) {
    if (!node) return 0;
    if (key < node->key) return rankOf(node->left, key, passed);
    if (key > node->key) return rankOf(node->right, key, passed + size(node->left) + 1);
    return passed + size(node->left) + 1;
}

void Adat(int x) {
    if (seen.insert(x).second) insertKey(x);
}

int Elemszam() {
    return size(root);
}

int Kadik(int k) {
    return kth(root, k);
}

int Hanyadik(int x) {
    if (!contains(root, x)) return 0;
    return rankOf(root, x);
}
