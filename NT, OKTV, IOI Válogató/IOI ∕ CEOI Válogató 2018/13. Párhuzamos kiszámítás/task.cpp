/*
Megoldás lényege:
Egy műveleti csúcs kiértékelése 1 időegység, a levelek (konstansok) nem igényelnek időt.
A minimális idő a gyökértől a legmélyebb műveleti láncig tartó műveletek száma, ezt egy
bejárással kapjuk meg. A legkisebb processzorszám nem egyszerűen a műveletszám osztva az
idővel, mert a fa szerkezete korlátozza, mely műveletek lehetnek egyszerre készen. Egy
adott P processzorra a műveleteket lépésenként ütemezzük: minden lépésben a készen álló
műveletek közül legfeljebb P-t hajtunk végre, a gyökértől legmélyebbeket előnyben részesítve.
Ez fára optimális (Hu-algoritmus), ezért a legkisebb olyan P bináris kereséssel megtalálható,
amellyel az ütemezés a minimális idő alatt befejeződik. Az idő O(N log^2 N).
*/
/*
Hint 1: || A legrövidebb idő a legmélyebb műveleti lánc hossza, a levelek nem számítanak. A processzorok száma nem egyszerűen a műveletszám osztva az idővel, mert a fa szerkezete határozza meg, mely műveletek lehetnek egyszerre készen. ||
Hint 2: || Adott P processzorral lépésenként haladunk: a készen álló műveletek (amelyek operandusai már kiszámítottak) közül legfeljebb P-t hajtunk végre. Ha több áll készen, a gyökértől legmesszebb lévőt (legmélyebb csúcsot) válasszuk először, mert annak a láncnak a többi része még hátra van. ||
Hint 3: || Ha egy P-vel az ütemezés a minimális idő alatt véget ér, akkor minden nagyobb P is megfelel, így a legkisebb ilyen P bináris kereséssel megkereshető. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Node {
    bool internal = false;
    int left = 0, right = 0;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<Node> nodes(n + 1);
    string line;
    getline(cin, line);
    for (int i = 1; i <= n; ++i) {
        getline(cin, line);
        while (!line.empty() && isspace((unsigned char)line.back())) line.pop_back();
        if (line.empty()) {
            --i;
            continue;
        }
        stringstream ss(line);
        string first;
        ss >> first;
        if (!first.empty() && (first[0] == '+' || first[0] == '-' || first[0] == '*' || first[0] == '/')) {
            nodes[i].internal = true;
            ss >> nodes[i].left >> nodes[i].right;
        }
    }

    vector<int> height(n + 1, 0);
    vector<int> ops(n + 1, 0);
    vector<pair<int, bool>> st;
    st.push_back({1, false});

    while (!st.empty()) {
        auto [v, done] = st.back();
        st.pop_back();
        if (!done) {
            st.push_back({v, true});
            if (nodes[v].internal) {
                st.push_back({nodes[v].right, false});
                st.push_back({nodes[v].left, false});
            }
        } else {
            if (!nodes[v].internal) {
                height[v] = 0;
                ops[v] = 0;
            } else {
                int l = nodes[v].left;
                int r = nodes[v].right;
                height[v] = max(height[l], height[r]) + 1;
                ops[v] = ops[l] + ops[r] + 1;
            }
        }
    }

    if (!nodes[1].internal) {
        cout << 0 << '\n' << 0 << '\n';
        return 0;
    }

    // Szülők és mélységek a gyökértől számítva (a gyökér mélysége 0).
    vector<int> par(n + 1, 0), dep(n + 1, 0);
    vector<int> order = {1};
    for (size_t idx = 0; idx < order.size(); ++idx) {
        int v = order[idx];
        if (!nodes[v].internal) continue;
        for (int c : {nodes[v].left, nodes[v].right}) {
            par[c] = v;
            dep[c] = dep[v] + 1;
            order.push_back(c);
        }
    }

    int time = height[1];
    int totalOps = ops[1];

    // Kezdeti állapot: hány belső gyereke van még hátra minden műveletnek, és melyek készen állnak.
    vector<int> pendingInit(n + 1, 0);
    vector<long long> readyInit;  // kulcs: mélység * (n + 1) + csúcs
    for (int v = 1; v <= n; ++v) {
        if (!nodes[v].internal) continue;
        for (int c : {nodes[v].left, nodes[v].right})
            if (nodes[c].internal) ++pendingInit[v];
        if (pendingInit[v] == 0) readyInit.push_back((long long)dep[v] * (n + 1) + v);
    }

    // Igaz, ha P processzorral a műveletek a minimális idő alatt kiszámíthatók.
    auto feasible = [&](int P) {
        vector<int> pending = pendingInit;
        priority_queue<long long> ready(less<long long>(), readyInit);  // legmélyebb csúcs elöl
        vector<long long> batch;
        int done = 0;
        for (int step = 0; done < totalOps; ++step) {
            if (step == time || ready.empty()) return false;
            batch.clear();
            while ((int)batch.size() < P && !ready.empty()) {
                batch.push_back(ready.top());
                ready.pop();
            }
            for (long long key : batch) {
                int v = (int)(key % (n + 1));
                ++done;
                int p = par[v];
                if (p != 0 && --pending[p] == 0) ready.push((long long)dep[p] * (n + 1) + p);
            }
        }
        return true;
    };

    int lo = 1, hi = totalOps;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) hi = mid;
        else lo = mid + 1;
    }

    cout << time << '\n' << lo << '\n';
    return 0;
}
