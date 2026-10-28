/*
Megoldás lényege:
Egy karaván reggel indul és aznap este megérkezik, így egy útvonal minden élének indulási napja szigorúan nagyobb az előző él indulási napjánál. Mindhárom kérdést a 365 napon végighaladó, naponként egyszer minden élet megvizsgáló bejárással oldjuk meg. A legkorábbi érkezésnél azt a napot keressük, amikor B először elérhető. A legrövidebb időtartamnál minden napra eltároljuk, melyik legkésőbbi indulási nappal juthatunk el az egyes városokba, és a (nap - indulás + 1) értékek minimuma a válasz. A legkésőbbi indulást a napokon fordított irányban haladva, B-től visszafelé számoljuk. Az időigény O(365*M + N), ami M ≤ 50 000 mellett a 0,3 másodperces időlimitben is elfér.
*/
/*
Hint 1: || Egy karaván aznap indul és aznap érkezik, így egy útvonalon a napok szigorúan nőnek: a következő indulás legkorábban a megérkezés napja utáni napon lehet. ||
Hint 2: || A legrövidebb időtartamhoz napokra bontva haladj: minden városba tartsd nyilván, melyik legkésőbbi indulási nappal lehet odaérni a megadott napig. A kérdés válasza a (nap - indulási nap + 1) értékek minimuma. ||
Hint 3: || A legkésőbbi indulást fordítva számold: a napokat H-tól visszafelé járva, B-ből indulva. Egy él akkor használható egy adott napon, ha a célvárosból a következő napon még el lehet jutni B-be H-ig. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from, to, p, q;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int DAYS = 365;
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (auto& e : edges) {
        cin >> e.from >> e.to >> e.p >> e.q;
    }
    int A, B, H;
    cin >> A >> B >> H;

    // 1. Legkorábbi érkezés: reached[v] = 1, ha v-be már megérkeztünk (az érkezés napján nem indulhatunk tovább).
    int earliest = -1;
    {
        vector<char> reached(n + 1, 0);
        reached[A] = 1;  // A-ból bármelyik nap indulhatunk
        vector<int> newly;
        for (int day = 1; day <= DAYS && earliest == -1; day++) {
            newly.clear();
            for (const auto& e : edges) {
                if (day < e.p || day > e.q) continue;
                if (reached[e.from] && !reached[e.to]) newly.push_back(e.to);
            }
            for (int v : newly) reached[v] = 1;
            if (reached[B]) earliest = day;
        }
    }

    // 2. Legrövidebb időtartam: cur[v] = a legkésőbbi indulási nap, amellyel legkésőbb a mai napig v-be érhetünk (0: nem lehet).
    int shortest = -1;
    {
        vector<int> cur(n + 1, 0), nxt(n + 1, 0);
        for (int day = 1; day <= DAYS; day++) {
            nxt = cur;
            for (const auto& e : edges) {
                if (day < e.p || day > e.q) continue;
                int start = (e.from == A) ? day : cur[e.from];
                if (start > nxt[e.to]) nxt[e.to] = start;
            }
            cur.swap(nxt);
            if (cur[B] > 0) {
                int len = day - cur[B] + 1;
                if (shortest == -1 || len < shortest) shortest = len;
            }
        }
    }

    // 3. Legkésőbbi indulás: latest[v] = a legkésőbbi nap, amikor v-ből indulva még H-ig B-be érhetünk (0: nem lehet).
    int latestStart = -1;
    {
        vector<int> latest(n + 1, 0);
        latest[B] = H + 1;  // B-ben már vagyunk, a határidő H
        for (int day = min(H, DAYS); day >= 1; day--) {
            for (const auto& e : edges) {
                if (day < e.p || day > e.q) continue;
                if (latest[e.to] < day + 1) continue;
                if (latest[e.from] == 0) latest[e.from] = day;
            }
        }
        if (latest[A] > 0) latestStart = latest[A];
    }

    cout << earliest << "\n" << shortest << "\n" << latestStart << "\n";
    return 0;
}
