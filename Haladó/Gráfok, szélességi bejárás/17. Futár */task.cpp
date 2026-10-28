/*
Megoldás lényege:
Egyetlen szélességi bejárással (többforrású BFS) határozzuk meg minden városra, hogy legkevesebb hány úton át érhető el valamelyik kezdővárosból. A kezdővárosokat egyszerre tesszük a sorba, a távolságuk 0. Egy nap alatt legfeljebb K út tehető meg, ezért azok a városok maradnak 1 nap alatt elérhetetlenek, amelyek távolsága nagyobb K-nál. A mindenhova eljutáshoz szükséges napok száma a legnagyobb távolság K-val való hányadosa, felfelé kerekítve. Az élek CSR-tömbben vannak tárolva, így az időigény O(N + M), a memóriaigény is ezzel arányos.
*/
/*
Hint 1: || Nem kell minden kezdővárosból külön bejárást indítani: mindet egyszerre tedd a sorba, a távolságukat vedd 0-nak. ||
Hint 2: || A legnagyobb távolságot (maxd) kell K-val osztani úgy, hogy a maradék is számítson: a napok száma (maxd + K - 1) / K. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, m;
    cin >> n >> k >> m;

    // Az éleket először két tömbbe olvassuk, majd szomszédsági listát (CSR) építünk belőlük.
    vector<int> eu(m), ev(m);
    vector<int> off(n + 2, 0);
    for (int i = 0; i < m; ++i) {
        cin >> eu[i] >> ev[i];
        ++off[eu[i] + 1];
        ++off[ev[i] + 1];
    }
    for (int v = 1; v <= n + 1; ++v) off[v] += off[v - 1];

    vector<int> pos(off.begin(), off.end());
    vector<int> adj(2 * (size_t)m);
    for (int i = 0; i < m; ++i) {
        adj[pos[eu[i]]++] = ev[i];
        adj[pos[ev[i]]++] = eu[i];
    }
    vector<int>().swap(eu);
    vector<int>().swap(ev);
    vector<int>().swap(pos);

    // Többforrású szélességi bejárás: minden kezdőváros távolsága 0.
    vector<int> dist(n + 1, -1);
    vector<int> q;
    q.reserve(n);
    int x;
    while (cin >> x) {
        if (x >= 1 && x <= n && dist[x] == -1) {
            dist[x] = 0;
            q.push_back(x);
        }
    }
    for (size_t h = 0; h < q.size(); ++h) {
        int u = q[h];
        for (int e = off[u]; e < off[u + 1]; ++e) {
            int v = adj[e];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push_back(v);
            }
        }
    }

    // Azok a városok, ahova 1 nap alatt nem lehet eljutni, és a legnagyobb távolság.
    string line;
    int maxd = 0;
    for (int v = 1; v <= n; ++v) {
        if (dist[v] == -1 || dist[v] > k) {
            if (!line.empty()) line += ' ';
            line += to_string(v);
        }
        if (dist[v] > maxd) maxd = dist[v];
    }

    int days = (maxd + k - 1) / k;
    cout << line << '\n' << days << '\n';
    return 0;
}
