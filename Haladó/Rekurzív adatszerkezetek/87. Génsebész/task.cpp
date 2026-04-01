/*
Megoldási ötlet:
A DNS-szekvencia dinamikus sztring, amelyen beszúrás, törlés, cserélés és részszámlálás történik. Erre implicit treap
felel meg, ahol a csomópontokban a részfa mérete és az A/C/G/T karakterek darabszáma is szerepel.

A részszekvencia lekérdezéséhez kettéhasítjuk a treapot, a műveletet a középső részen végezzük el, majd visszaolvasztjuk.
Az Eredmeny egy inorder bejárás.
*/
/*
Hint 1: || A pozíciók kezelése miatt implicit treap kell, nem kulcs szerinti. ||
Hint 2: || Egy részszámlálás a középső részfa karakterösszegeiből kijön. ||
Hint 3: || A törlés és a beszúrás is split + merge műveletté alakítható. ||
*/

#include "grader.h"
#include <algorithm>
#include <random>
#include <string>
#include <vector>

using namespace std;

static int index(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    return 3;
}

struct Node {
    char c;
    int pr;
    int sz;
    int cnt[4]{};
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(char c, int pr) : c(c), pr(pr), sz(1) {
        fill(begin(cnt), end(cnt), 0);
        cnt[index(c)] = 1;
    }
};

static mt19937 rng(123456789);
static Node* root = nullptr;

static int size(Node* node) { return node ? node->sz : 0; }

static void pull(Node* node) {
    if (!node) return;
    node->sz = 1 + size(node->left) + size(node->right);
    fill(begin(node->cnt), end(node->cnt), 0);
    if (node->left) for (int i = 0; i < 4; ++i) node->cnt[i] += node->left->cnt[i];
    node->cnt[index(node->c)]++;
    if (node->right) for (int i = 0; i < 4; ++i) node->cnt[i] += node->right->cnt[i];
}

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

static Node* buildChar(char c) {
    return new Node(c, static_cast<int>(rng()));
}

static void collect(Node* node, string& out) {
    if (!node) return;
    collect(node->left, out);
    out.push_back(node->c);
    collect(node->right, out);
}

void Kezd(string s) {
    root = nullptr;
    for (char c : s) root = merge(root, buildChar(c));
}

void Beszur(int i, char x) {
    Node *a, *b;
    split(root, i, a, b);
    root = merge(merge(a, buildChar(x)), b);
}

void Mutal(int i, char x) {
    Node *a, *b, *c;
    split(root, i - 1, a, b);
    split(b, 1, b, c);
    if (b) b->c = x;
    pull(b);
    root = merge(merge(a, b), c);
}

void Kivag(int i, int j) {
    Node *a, *b, *c;
    split(root, i - 1, a, b);
    split(b, j - i + 1, b, c);
    root = merge(a, c);
}

int Szamlal(int i, int j, char x) {
    Node *a, *b, *c;
    split(root, i - 1, a, b);
    split(b, j - i + 1, b, c);
    int answer = b ? b->cnt[index(x)] : 0;
    root = merge(merge(a, b), c);
    return answer;
}

string Eredmeny() {
    string result;
    result.reserve(size(root));
    collect(root, result);
    return result;
}
