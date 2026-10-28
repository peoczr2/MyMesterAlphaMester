/*
Megoldás lényege:
A munkák egy része biztosan A elé, másik része biztosan B után kerül: A összes (közvetett) elődjét A előtt,
B összes (közvetett) utódját B után kell elvégezni. Az ezekhez nem tartozó munkák mind lehetnek A és B között.
Ha a sorrend: A elődjei, majd A, aztán a maradék munkák, majd B, végül B utódai, akkor minden megelőzési
feltétel teljesül, és A és B között pontosan a maradék munkák vannak. Így a keresett szám
N - 2 - |A elődei| - |B utódai|. A csoportokon belüli sorrendet Kahn-algoritmussal (topologikus rendezéssel)
állítjuk elő, a visszafelé és előre bejárások is lineárisak, így az összidő O(N+M).
*/
/*
Hint 1: || Melyik munkákat kell feltétlenül A elé, és melyeket B után elvégezni? Ehhez az éleket A-ból visszafelé, B-ből előre bejárva kapod meg a csoportokat. ||
Hint 2: || A maradék munkák mind lehetnek A és B között. Az A-elődök, A, a maradék munkák, B, a B-utódok sorrendben már megelőzési feltételeket nem sért, ha minden csoport belül is topologikus. ||
Hint 3: || A csoportok belsejét Kahn-algoritmussal rendezheted, ha csak a csoporton belüli éleket veszed figyelembe. A kiírandó szám a középső csoport mérete. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<vector<int>> out(n + 1), in(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        out[x].push_back(y);
        in[y].push_back(x);
    }

    // cat: 1 = A elődei, 2 = A, 3 = a köztes munkák, 4 = B, 5 = B utódai
    vector<int> cat(n + 1, 3);

    // A elődei: visszafelé bejárás A-ból
    vector<int> st = {a};
    vector<bool> seen(n + 1, false);
    seen[a] = true;
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        for (int v : in[u]) {
            if (!seen[v]) {
                seen[v] = true;
                cat[v] = 1;
                st.push_back(v);
            }
        }
    }
    cat[a] = 2;

    // B utódai: előre bejárás B-ből
    fill(seen.begin(), seen.end(), false);
    seen[b] = true;
    st = {b};
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        for (int v : out[u]) {
            if (!seen[v]) {
                seen[v] = true;
                cat[v] = 5;
                st.push_back(v);
            }
        }
    }
    cat[b] = 4;

    // Egy csoport belső topologikus rendezése (Kahn, a legnagyobb sorszámút előre véve)
    auto order_group = [&](int c) {
        vector<int> res;
        vector<int> indeg(n + 1, 0);
        for (int u = 1; u <= n; u++) {
            if (cat[u] != c) continue;
            for (int v : out[u]) {
                if (cat[v] == c) indeg[v]++;
            }
        }
        priority_queue<int> pq;
        for (int u = 1; u <= n; u++) {
            if (cat[u] == c && indeg[u] == 0) pq.push(u);
        }
        while (!pq.empty()) {
            int u = pq.top();
            pq.pop();
            res.push_back(u);
            for (int v : out[u]) {
                if (cat[v] == c && --indeg[v] == 0) pq.push(v);
            }
        }
        return res;
    };

    vector<int> order;
    for (int x : order_group(1)) order.push_back(x);
    order.push_back(a);
    for (int x : order_group(3)) order.push_back(x);
    order.push_back(b);
    for (int x : order_group(5)) order.push_back(x);

    int middle = 0;
    for (int u = 1; u <= n; u++) {
        if (cat[u] == 3) middle++;
    }

    cout << middle << "\n";
    for (size_t i = 0; i < order.size(); i++) {
        if (i) cout << " ";
        cout << order[i];
    }
    cout << "\n";
    return 0;
}
