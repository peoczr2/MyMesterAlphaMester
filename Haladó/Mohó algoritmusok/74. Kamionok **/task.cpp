/*
Feladat: Minden igényt határidőre Bergengóciába kell vinni. Egy kamion indulásai között 2*S nap telik el, az indulás utáni S. napon ér célba. Minimalizálni kell a kamionok számát, majd ehhez az utolsó visszaérkezés idejét.
Ötlet: Egy D napos határidőig egy kamion legfeljebb floor((D+S)/(2S)) szállítást tud célba juttatni. Ez prefix-kapacitáskorlátot ad, így a minimális kamionszám a max_i ceil(i / cap(Hi)). Ezután ezen kamionszámmal határidő szerint kiosztunk: mindig annak a kamionnak adjuk a következő igényt, amelyik a leghamarabb tud legközelebb célba érni. Így a második sorban kért visszaérkezési idő minimális.
Hint 1: || Számold ki, egy kamion hány célba érkezést tud adni egy adott határidőig. ||
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
