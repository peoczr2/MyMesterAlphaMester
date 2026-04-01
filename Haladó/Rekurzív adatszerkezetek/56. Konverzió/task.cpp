/*
Megoldási ötlet:
A posztfix kifejezést balról jobbra olvasva minden operandushoz eltároljuk annak infix alakját, a gyökerének
operátorát és a gyökeres kifejezés prioritását. Amikor egy műveleti jelet látunk, a két legutóbbi részfát
összefűzzük.

A zárójelezés szabálya egyszerű:
- bal oldalon csak akkor kell zárójel, ha az adott részfa prioritása kisebb az új operátorénál;
- jobb oldalon akkor kell zárójel, ha a prioritása kisebb, vagy ugyanakkora, de az új operátor nem asszociatív a
  jobb gyerekkel együtt.
Ez elegendő a lehető legkevesebb zárójelhez, miközben az argumentumok sorrendje változatlan marad.
*/
/*
Hint 1: || A posztfix alakból egy egyszerű veremmel építhető fel az infix kifejezés fája. ||
Hint 2: || A bal oldali részfa ugyanazon prioritás mellett általában zárójel nélkül maradhat. ||
Hint 3: || A jobb oldalon ugyanazon prioritásnál csak a + és * operátorok engedik el a zárójelet. ||
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Expr {
    string text;
    char op;
    int prec;
};

struct Node {
    char op;
    string value;
    int left = -1;
    int right = -1;
};

bool isAdd(char op) {
    return op == '+' || op == '-';
}

bool isMul(char op) {
    return op == '*' || op == '/';
}

string renderAdd(const vector<Node>& nodes, int idx);
string renderMul(const vector<Node>& nodes, int idx);

string renderChild(const vector<Node>& nodes, int idx, char parentOp, bool isRightChild) {
    const Node& node = nodes[idx];
    if (!isAdd(node.op) && !isMul(node.op)) {
        return node.value;
    }

    int parentPrec = (parentOp == '+' || parentOp == '-') ? 1 : 2;
    int childPrec = isAdd(node.op) ? 1 : 2;
    bool need = childPrec < parentPrec;

    if (!need && childPrec == parentPrec) {
        if (parentOp == '+') {
            need = false;
        } else if (parentOp == '-') {
            need = isRightChild;
        } else if (parentOp == '*') {
            need = false;
        } else if (parentOp == '/') {
            need = isRightChild;
        }
    }

    string text = isAdd(node.op) ? renderAdd(nodes, idx) : renderMul(nodes, idx);
    if (need) {
        return '(' + text + ')';
    }
    return text;
}

string renderAdd(const vector<Node>& nodes, int idx) {
    const Node& node = nodes[idx];
    if (!isAdd(node.op) && !isMul(node.op)) {
        return node.value;
    }
    if (!isAdd(node.op)) {
        return renderMul(nodes, idx);
    }

    return renderChild(nodes, node.left, node.op, false) + node.op + renderChild(nodes, node.right, node.op, true);
}

string renderMul(const vector<Node>& nodes, int idx) {
    const Node& node = nodes[idx];
    if (!isAdd(node.op) && !isMul(node.op)) {
        return node.value;
    }
    if (!isMul(node.op)) {
        return renderAdd(nodes, idx);
    }
    return renderChild(nodes, node.left, node.op, false) + node.op + renderChild(nodes, node.right, node.op, true);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string postfix;
    cin >> postfix;

    vector<Node> nodes;
    vector<int> st;
    for (char ch : postfix) {
        if (ch >= 'a' && ch <= 'z') {
            nodes.push_back({0, string(1, ch), -1, -1});
            st.push_back((int)nodes.size() - 1);
        } else {
            int right = st.back(); st.pop_back();
            int left = st.back(); st.pop_back();
            nodes.push_back({ch, {}, left, right});
            st.push_back((int)nodes.size() - 1);
        }
    }

    int root = st.back();
    if (nodes[root].op == '+' || nodes[root].op == '-') {
        cout << renderAdd(nodes, root) << '\n';
    } else if (nodes[root].op == '*' || nodes[root].op == '/') {
        cout << renderMul(nodes, root) << '\n';
    } else {
        cout << nodes[root].value << '\n';
    }
    return 0;
}