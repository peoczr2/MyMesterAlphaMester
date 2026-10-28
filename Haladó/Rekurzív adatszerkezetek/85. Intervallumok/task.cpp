/*
Megoldási ötlet:
Az intervallumhalmazt (l,r) szerint rendezett, véletlen prioritású fával (treap) tároljuk. Minden csúcs egy [l,r] intervallum,
és a részfájában eltároljuk a legnagyobb jobb végpontot. Egy intervallum a halmazban csak egyszer szerepel.

A MetszKeres lekérdezésnél az intervallumfa klasszikus logikáját használjuk: ha a bal részfában van olyan intervallum,
amelynek jobb vége eléri az [xa,xb] bal szélét, akkor balra megyünk, különben a jelenlegi csúcsot vizsgáljuk, majd jobbra.
Minden művelet várhatóan O(log n) idejű.
*/
/*
Hint 1: || Egy intervallum akkor metsz egy másikat, ha a kezdete nem nagyobb a másik végénél és fordítva. ||
Hint 2: || Tárolj minden csúcsban részfa-szintű maximum jobb véget. ||
Hint 3: || A keresés mindig abba az irányba halad, ahol még lehet metsző intervallum. ||
*/

#include "interval.h"
#include <algorithm>
#include <random>

using namespace std;

struct Node {
    int l, r;
    int pr;
    int subtreeMaxR;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int l, int r, int pr) : l(l), r(r), pr(pr), subtreeMaxR(r) {}
};

static mt19937 rng(998244353);
static Node* root = nullptr;

static int maxR(Node* node) { return node ? node->subtreeMaxR : -1; }
static void pull(Node* node) {
    if (node) node->subtreeMaxR = max(node->r, max(maxR(node->left), maxR(node->right)));
}

static Node* merge(Node* a, Node* b) {
    if (!a || !b) return a ? a : b;
    if (a->pr > b->pr) {
        a->right = merge(a->right, b);
        pull(a);
        return a;
    }
    b->left = merge(a, b->left);
    pull(b);
    return b;
}

static bool lessInterval(int l1, int r1, int l2, int r2) {
    return l1 < l2 || (l1 == l2 && r1 < r2);
}

static void split(Node* node, int l, int r, Node*& left, Node*& right) {
    if (!node) { left = right = nullptr; return; }
    if (lessInterval(node->l, node->r, l, r)) {
        split(node->right, l, r, node->right, right);
        left = node;
        pull(left);
    } else {
        split(node->left, l, r, left, node->left);
        right = node;
        pull(right);
    }
}

static Node* insertNode(Node* node, Node* item) {
    if (!node) return item;
    if (item->pr > node->pr) {
        split(node, item->l, item->r, item->left, item->right);
        pull(item);
        return item;
    }
    if (lessInterval(item->l, item->r, node->l, node->r)) node->left = insertNode(node->left, item);
    else node->right = insertNode(node->right, item);
    pull(node);
    return node;
}

static bool contains(const Node* node, int l, int r) {
    while (node) {
        if (node->l == l && node->r == r) return true;
        node = lessInterval(l, r, node->l, node->r) ? node->left : node->right;
    }
    return false;
}

static Node* eraseNode(Node* node, int l, int r) {
    if (!node) return nullptr;
    if (node->l == l && node->r == r) return merge(node->left, node->right);
    if (lessInterval(l, r, node->l, node->r)) node->left = eraseNode(node->left, l, r);
    else node->right = eraseNode(node->right, l, r);
    pull(node);
    return node;
}

static bool intersects(const Node* node, int xa, int xb) {
    return node && node->l <= xb && node->r >= xa;
}

static bool search(Node* node, int xa, int xb, int& a, int& b) {
    if (!node || maxR(node) < xa) return false;
    if (node->left && maxR(node->left) >= xa) return search(node->left, xa, xb, a, b);
    if (intersects(node, xa, xb)) {
        a = node->l;
        b = node->r;
        return true;
    }
    if (node->l <= xb) return search(node->right, xa, xb, a, b);
    return false;
}

void Bovit(int a, int b) {
    if (contains(root, a, b)) return;
    root = insertNode(root, new Node(a, b, static_cast<int>(rng())));
}

void Torol(int a, int b) {
    root = eraseNode(root, a, b);
}

void MetszKeres(int xa, int xb, int &a, int &b) {
    if (!search(root, xa, xb, a, b)) {
        a = b = 0;
    }
}
