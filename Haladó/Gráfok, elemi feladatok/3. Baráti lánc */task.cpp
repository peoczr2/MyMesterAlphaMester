/*
Megoldás lényege:
Egy Hamilton-kört keresünk, amely 1-essel kezdődik: a könyv útja egy olyan körbejárás, ahol mindenki barátjának adja tovább.
Egy 1-essel kezdődő utat építünk: mindig a végéhez csatlakoztatunk még nem használt barátot. Ha elakadunk, Pósa-féle forgatással
az út egy végponti barátját választjuk, a mögötte lévő szakaszt megfordítjuk, így új végpont lesz, amelyhez talán van szabad barát.
Ha az út mind az N tanulót tartalmazza, és a végpont barátja 1, a lánc kész. Mivel a fokszámok nagyok (K > 2N/3), a forgatások gyorsan célhoz vezetnek.
*/
/*
Hint 1: || Építs 1-ből kiindulva egy utat, amelyben minden újabb tanuló barátja az addigi utolsó tanulónak; ha minden tanuló benne van, és az utolsó barátja 1, kész a lánc. ||
Hint 2: || Ha az út végéről nincs több, még nem használt barát, egy útbeli barátjától kezdve fordítsd meg a mögötte lévő szakaszt: így az út vége új tanulóra kerül. ||
Hint 3: || Mivel minden tanulónak legalább K > 2N/3 barátja van, az ilyen forgatások gyorsan eredményt adnak; a rögzített magú véletlen választás elkerüli a körbejárást. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string buf;
    {
        char tmp[1 << 16];
        size_t r;
        while ((r = fread(tmp, 1, sizeof tmp, stdin)) > 0) buf.append(tmp, r);
    }
    size_t ip = 0;
    auto readNumber = [&](int &v) -> bool {
        while (ip < buf.size() && !isdigit((unsigned char)buf[ip])) ip++;
        if (ip >= buf.size()) return false;
        v = 0;
        while (ip < buf.size() && isdigit((unsigned char)buf[ip])) {
            v = v * 10 + (buf[ip] - '0');
            ip++;
        }
        return true;
    };

    int n = 0, k = 0;
    readNumber(n);
    readNumber(k);
    while (ip < buf.size() && buf[ip] != '\n') ip++;

    // soronként egy tanuló barátai: a sorok hossza nem ismert előre
    vector<vector<int>> nb(n + 1);
    vector<vector<char>> adj(n + 1, vector<char>(n + 1, 0));
    for (int i = 1; i <= n; i++) nb[i].reserve(k + 8);
    for (int i = 1; i <= n; i++) {
        while (ip < buf.size() && !isdigit((unsigned char)buf[ip])) ip++;
        while (ip < buf.size() && buf[ip] != '\n') {
            if (isdigit((unsigned char)buf[ip])) {
                int v = 0;
                readNumber(v);
                if (v != i && v >= 1 && v <= n) {
                    nb[i].push_back(v);
                    adj[i][v] = 1;
                }
            } else {
                ip++;
            }
        }
    }

    mt19937 rng(20261025u);
    vector<int> p;
    vector<int> at(n + 1, -1); // a tanuló helye az útban, -1 ha nincs benne
    const int LIMIT = 40 * n + 1000;

    while (true) {
        p.assign(1, 1);
        fill(at.begin(), at.end(), -1);
        at[1] = 0;
        int rot = 0;
        bool found = false;
        while (rot < LIMIT) {
            int L = p.size();
            int end = p[L - 1];
            if (L == n && adj[end][1]) {
                found = true;
                break;
            }

            // bővítés: még nem használt barát a végponthoz
            vector<int> freeNb;
            for (int u : nb[end]) {
                if (at[u] < 0) freeNb.push_back(u);
            }
            if (!freeNb.empty()) {
                int u = freeNb[rng() % freeNb.size()];
                at[u] = L;
                p.push_back(u);
                continue;
            }

            // Pósa-forgatás: a végpont egy útbeli barátjától kezdve megfordítjuk a szakaszt
            vector<int> cand;
            for (int u : nb[end]) {
                if (at[u] >= 0 && at[u] < L - 2) cand.push_back(at[u]);
            }
            if (cand.empty()) break;
            int i = cand[rng() % cand.size()];
            reverse(p.begin() + i + 1, p.end());
            for (int j = i + 1; j < L; j++) at[p[j]] = j;
            rot++;
        }
        if (found) break;
    }

    string out;
    out.reserve(n * 5);
    for (int i = 0; i < (int)p.size(); i++) {
        if (i) out += ' ';
        out += to_string(p[i]);
    }
    out += '\n';
    cout << out;
    return 0;
}
