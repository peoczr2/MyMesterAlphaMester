/*
Megoldás lényege: a benzint 100-szoros egységben számoljuk, így egy kilométer fogyasztása L egység, a távolságok
pedig egész számok maradnak. Haladunk előre, és minden elért kutat egy prioritási sorba teszünk a tankolt mennyiséggel.
Ha a következő kútig vagy a célig nem elég a benzin, a sorból a legnagyobb tankolást vesszük ki, és ezt használjuk
fel (a tartály mérete nem korlát, így a már elhaladt kutak is használhatók). Ez a mohó stratégia optimális: mindig
a legnagyobb tankolással kevesebb állomás kell.
Időigény: O(N log N), a rendezés és a prioritási sor dominál.
*/
/*
Hint 1: || Az elérhető kutak tankolásait egy prioritási sorban tárold. ||
Hint 2: || Amikor kevés a benzin, mindig a legnagyobb eddig látott tankolást használd fel. ||
Hint 3: || Ha a célig a jelenlegi benzinnel nem jutsz el, a legnagyobb tankolást vedd hozzá, és így ismételd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long K, N, B, L;
    cin >> K >> N >> B >> L;
    vector<pair<long long, long long>> st(N);
    for (int i = 0; i < N; ++i) cin >> st[i].first >> st[i].second;
    sort(st.begin(), st.end());

    priority_queue<long long> pq;
    long long fuel = B * 100;
    long long used = 0;
    long long pos = 0;
    int ptr = 0;

    auto need = [&](long long d) { return d * L; };

    while (pos < K) {
        long long reach = pos + fuel / L;
        while (ptr < N && st[ptr].first <= reach) {
            pq.push(st[ptr].second * 100);
            ++ptr;
        }
        long long nextPos = K;
        if (ptr < N) nextPos = min(nextPos, st[ptr].first);
        if (fuel >= need(nextPos - pos)) {
            fuel -= need(nextPos - pos);
            pos = nextPos;
            continue;
        }
        if (pq.empty()) break;
        fuel += pq.top();
        pq.pop();
        ++used;
    }

    cout << used << '\n';
    return 0;
}