/*
Megoldási ötlet:
Az intervallumok lefedettségét egy eseményfában tároljuk: [a,b] hozzáadása +1-et tesz a és -1-et b+1 helyre. A teljes
lefedettség így egy prefixösszeg, amelynek maximumát és helyét egy kiegyensúlyozott fában tudjuk karbantartani.

Minden csúcsban tároljuk a részfa összegét, a legnagyobb prefixösszeget és azt a koordinátát, ahol ez a maximum először
elérhető. Bovit és Torol csak két eseményt módosít.
*/
/*
Hint 1: || Zárt intervallumoknál az [a,b] lefedését a +1@a és -1@(b+1) események adják. ||
Hint 2: || A legnagyobb fedettség a rendezett események prefixösszegének maximuma. ||
Hint 3: || A pont és a darabszám ugyanabban a fában tartható karban. ||
*/

#include "maxipont.h"
#include <algorithm>
#include <random>

using namespace std;

struct Node {
    long long key;
    int delta;
    int pr;
    long long sum;
    long long bestPref;
    long long bestPoint;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(long long key, int delta, int pr)
        : key(key), delta(delta), pr(pr), sum(delta), bestPref(delta), bestPoint(key) {}
};

static mt19937 rng(1239871);
static Node* root = nullptr;

static long long totalSum(Node* node) { return node ? node->sum : 0; }
static long long totalBest(Node* node) { return node ? node->bestPref : 0; }

static void pull(Node* node) {
    if (!node) return;
    node->sum = totalSum(node->left) + node->delta + totalSum(node->right);
    node->bestPref = totalBest(node->left);
    node->bestPoint = node->left ? node->left->bestPoint : node->key;
    long long prefixHere = totalSum(node->left) + node->delta;
    if (prefixHere > node->bestPref) {
        node->bestPref = prefixHere;
        node->bestPoint = node->key;
    }
    long long prefixRight = prefixHere + totalBest(node->right);
    if (prefixRight > node->bestPref) {
        node->bestPref = prefixRight;
        node->bestPoint = node->right ? node->right->bestPoint : node->key;
    }
}

static void split(Node* node, long long key, Node*& left, Node*& right) {
    if (!node) { left = right = nullptr; return; }
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

static Node* insertOrAdd(Node* node, long long key, int delta, int pr) {
    if (!node) return new Node(key, delta, pr);
    if (node->key == key) {
        node->delta += delta;
        if (node->delta == 0) {
            Node* res = merge(node->left, node->right);
            return res;
        }
        pull(node);
        return node;
    }
    if (key < node->key) {
        Node* child = insertOrAdd(node->left, key, delta, pr);
        node->left = child;
        if (child && child->pr > node->pr) {
            node->left = child->right;
            child->right = node;
            pull(node);
            pull(child);
            return child;
        }
    } else {
        Node* child = insertOrAdd(node->right, key, delta, pr);
        node->right = child;
        if (child && child->pr > node->pr) {
            node->right = child->left;
            child->left = node;
            pull(node);
            pull(child);
            return child;
        }
    }
    pull(node);
    return node;
}

static void addDelta(long long key, int delta) {
    root = insertOrAdd(root, key, delta, static_cast<int>(rng()));
}

static void changeInterval(int a, int b, int sign) {
    addDelta(a, sign);
    addDelta(static_cast<long long>(b) + 1, -sign);
}

void Bovit(int a, int b) {
    changeInterval(a, b, +1);
}

void Torol(int a, int b) {
    changeInterval(a, b, -1);
}

int MaxiPont() {
    return root ? static_cast<int>(root->bestPoint) : 0;
}

int MaxiHany() {
    return root ? static_cast<int>(root->bestPref) : 0;
}
