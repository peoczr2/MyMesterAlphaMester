#include <bits/stdc++.h>
using namespace std;

/*
  Egy műveleti csúcs kiértékelése 1 időegység, a levelek (konstansok) nem igényelnek időt.
  A minimális futási idő a legmélyebb műveleti lánc hossza.
  A legrövidebb időhöz szükséges processzorszámot a teljes műveletszám és a kritikus út
  hossza adja: ennyi műveletet kell elvégezni ennyi időegység alatt, ezért legalább
  ceil(muveletszam / ido) processzor kell, és fára ez elegendő is.

  A fára iteratív posztorder bejárással számoljuk ki minden csúcsra a műveletek számát
  és a kritikus út hosszát, hogy a 100000-es mélységet is biztonságosan kezeljük.
*/

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

    int time = height[1];
    int processors = (ops[1] + time - 1) / time;
    cout << time << '\n' << processors << '\n';
    return 0;
}