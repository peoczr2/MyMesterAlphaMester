/*
Megoldás lényege:
A „nem szeretik egymást” párok mindig különböző táborba kerülnek, ezért a gráf páros, és minden összefüggő komponensben a tanulók két színosztályba esnek. BFS-sel komponensenként megszámoljuk a két színosztály létszámát (c0, c1). Egy komponens két színosztálya szabadon fordítható, így a komponens eltérése |c0 - c1|, és csak az előjelét kell megválasztani. Ez részösszeg-feladat: a komponensek eltéréseiből úgy kell egy részhalmazt választani, hogy összege a lehető legközelebb legyen az összes eltérés felééhez. A részösszegeket logikai DP-vel számoljuk, a visszakövetéssel megkapjuk, mely komponenseknél kerüljön a nagyobb színosztály az első táborba. Mivel N ≤ 2000, az O(N²) DP időben és memóriában bőven belefér.
*/
/*
Hint 1: || Egy összefüggő részen belül a táborok váltakozva következnek: ha egy diák az egyik táborban van, a vele összekötött diákok a másikban. Így minden komponensnek csak két beosztása lehet, és elég a két színosztály méretét ismerni. ||
Hint 2: || Számold meg BFS-sel komponensenként a két színosztály létszámát. A komponens eltérése a_i = |c0 − c1|, és eldöntheted, hogy a nagyobb színosztály kerüljön-e az első táborba. Az eltérés így a_i-k előjeles összege. ||
Hint 3: || Ez részösszeg-feladat: keress olyan részhalmazt az a_i értékek között, amelynek összege a lehető legközelebb van az összes a_i összegének feléhez. Logikai DP-vel (dp[i][s]) számolható, a visszakövetéssel pedig megkapod, mely komponenseknél kell a nagyobb színosztályt az első táborba tenni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    // BFS: minden tanulóhoz komponens és színosztály
    vector<int> comp(n + 1, -1), color(n + 1, 0);
    vector<int> a;    // komponensenként |c0 - c1|
    vector<int> big;  // komponensenként a nagyobb színosztály
    int k = 0;
    for (int s = 1; s <= n; s++) {
        if (comp[s] != -1) continue;
        int cnt[2] = {0, 0};
        queue<int> q;
        comp[s] = k;
        color[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cnt[color[u]]++;
            for (int v : adj[u]) {
                if (comp[v] == -1) {
                    comp[v] = k;
                    color[v] = 1 - color[u];
                    q.push(v);
                }
            }
        }
        a.push_back(abs(cnt[0] - cnt[1]));
        big.push_back(cnt[0] >= cnt[1] ? 0 : 1);
        k++;
    }

    // Részösszeg-DP: reach[i][s] = az első i komponens egy részhalmazának összege lehet-e s
    int total = 0;
    for (int x : a) total += x;
    vector<vector<char>> reach(k + 1, vector<char>(total + 1, 0));
    reach[0][0] = 1;
    for (int i = 0; i < k; i++) {
        for (int s = 0; s <= total; s++) {
            if (!reach[i][s]) continue;
            reach[i + 1][s] = 1;
            if (s + a[i] <= total) reach[i + 1][s + a[i]] = 1;
        }
    }

    // Az a legjobb, ahol |2s - total| minimális (az üres részhalmaz mindig elérhető)
    int best = 0;
    for (int s = 0; s <= total; s++) {
        if (reach[k][s] && abs(2 * s - total) < abs(2 * best - total)) best = s;
    }

    // Visszakövetés: mely komponensek kerüljenek az első táborba a nagyobb színosztállyal
    vector<int> taken(k, 0);
    int s = best;
    for (int i = k; i >= 1; i--) {
        if (reach[i - 1][s]) continue;
        taken[i - 1] = 1;
        s -= a[i - 1];
    }

    vector<int> team(n + 1);
    for (int v = 1; v <= n; v++) {
        int c = comp[v];
        bool inFirst = taken[c] ? (color[v] == big[c]) : (color[v] != big[c]);
        team[v] = inFirst ? 0 : 1;
    }

    vector<int> first, second;
    for (int v = 1; v <= n; v++) {
        if (team[v] == 0) first.push_back(v);
        else second.push_back(v);
    }

    auto print = [](const vector<int>& vec) {
        for (size_t i = 0; i < vec.size(); i++) {
            if (i) cout << ' ';
            cout << vec[i];
        }
        cout << '\n';
    };

    cout << first.size() << ' ' << second.size() << '\n';
    print(first);
    print(second);
    return 0;
}
