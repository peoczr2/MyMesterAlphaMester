/*
Megoldás lényege:
Zsákfalu a fokszám-1 település. Innen indulva fokszám-2 településbe érkezve nincs választás, ezért tovább lépünk, és számoljuk a szakaszokat; az első olyan településnél (elágazás vagy zsákfalu) megállunk, ahol már nem fokszám-2 a fokszám. Minden fokszám-2 szakaszt legfeljebb kétszer járunk be, így az összidő O(N + M). A szomszédsági listát egyetlen tömbben tároljuk, mert a memóriakorlát 4 MB.
*/
/*
Hint 1: || Számold ki minden település fokszámát. A zsákfalu a fokszám-1 település; a fokszám-2 településeken nincs választás, így az út csak olyan településnél áll meg, amelynek fokszáma nem 2. ||
Hint 2: || Zsákfalunként egy lineáris bejárást végezz: mindig a még nem érintett szomszédba lépj (az előző települést ne add vissza), és számold a lépéseket, amíg nem fokszám-2 településre érsz. ||
Hint 3: || A 4 MB-os memóriakorlát miatt ne vector<vector<int>> szomszédsági listát használj, hanem az éleket egy tömbben tárold: a fokszámokból számolt kezdőindexekkel minden település szomszédai egymás után álljanak. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> ea(m), eb(m);
    vector<int> start(n + 2, 0);
    for (int i = 0; i < m; ++i) {
        cin >> ea[i] >> eb[i];
        ++start[ea[i]];
        ++start[eb[i]];
    }
    for (int v = 1; v <= n + 1; ++v) start[v] += start[v - 1];

    vector<int> adj(2 * m);
    for (int i = 0; i < m; ++i) {
        adj[--start[ea[i]]] = eb[i];
        adj[--start[eb[i]]] = ea[i];
    }
    // Ezután start[v] a v szomszédainak kezdőindexe, start[v + 1] a végindexe.
    auto deg = [&](int v) { return start[v + 1] - start[v]; };

    int best = 0;
    vector<int> ans;
    for (int s = 1; s <= n; ++s) {
        if (deg(s) != 1) continue;
        int prev = 0, v = s, len = 0;
        while (true) {
            int next = 0;
            for (int k = start[v]; k < start[v + 1]; ++k) {
                if (adj[k] != prev) { next = adj[k]; break; }
            }
            if (next == 0) break;
            ++len;
            if (deg(next) != 2) break;
            prev = v;
            v = next;
        }
        if (len > best) {
            best = len;
            ans.clear();
            ans.push_back(s);
        } else if (len == best) {
            ans.push_back(s);
        }
    }

    if (ans.empty()) {
        cout << -1 << '\n';
        return 0;
    }
    cout << best << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
