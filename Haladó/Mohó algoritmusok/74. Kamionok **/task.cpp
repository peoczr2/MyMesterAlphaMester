/*
Megoldás lényege:
Egy kamion 2S napos ciklusban legfeljebb egy szállítmányt visz, így D határidőig legfeljebb floor((D+S)/(2S)) igény teljesíthető vele.
A határidők szerint rendezett igények közül az i-edikre legalább ceil(i / cap(H_i)) kamion kell; ezek maximuma adja a minimális kamionszámot.
Ezzel a kamionszámmal a sorban haladva mindig azt a kamiont indítjuk, amelyik a leghamarabb érkezhet Bergengóciába (min-heap).
A legkorábbi szabad időpontokat használjuk fel, ezért az utolsó visszaérkezés is a lehető legkorábbi.
Időigény: O(N log N).
*/
/*
Hint 1: || Számold ki, hogy egy kamion egy adott határidőig hány célba érkezést tud adni. ||
Hint 2: || A minimális darabszámot prefixenként vett ceil(i/cap) maximum adja. ||
Hint 3: || Fix kamionszámnál min-heapen tartsd a kamionok következő érkezési napját. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, S;
    cin >> N >> S;
    vector<int> H(N + 1);
    for (int i = 1; i <= N; ++i) cin >> H[i];

    auto capOne = [&](long long D) -> long long {
        if (D < S) return 0;
        return (D + S) / (2LL * S);
    };

    long long trucks = 0;
    for (int i = 1; i <= N; ++i) {
        long long c = capOne(H[i]);
        if (c == 0) {
            // Elvileg nincs ilyen teszt az adott feladatkörben.
            cout << -1 << '\n' << -1 << '\n';
            return 0;
        }
        trucks = max(trucks, (i + c - 1) / c);
    }

    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (int i = 0; i < trucks; ++i) pq.push(S); // első célba érkezés napja

    long long lastReturn = 0;
    for (int i = 1; i <= N; ++i) {
        long long arr = pq.top();
        pq.pop();
        if (arr > H[i]) {
            cout << -1 << '\n' << -1 << '\n';
            return 0;
        }
        lastReturn = max(lastReturn, arr + S); // visszaérkezés napja
        pq.push(arr + 2LL * S);
    }

    cout << trucks << '\n' << lastReturn << '\n';
    return 0;
}
