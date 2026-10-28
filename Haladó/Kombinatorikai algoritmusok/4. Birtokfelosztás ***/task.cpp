/*
Megoldás lényege:
A felosztások száma: N birtok K pozitív egész részre bontása, ahol a részek sorrendje számít. Egy felosztást az N−1 lehetséges határhelyből kiválasztott K−1 vágás ad, így a szám M = C(N−1, K−1). Az első rész f értékéhez tartozó felosztások száma a maradék N−f birtok K−1 részre bontása, azaz C(N−f−1, K−2).
A lexikografikusan csökkenő sorrendben az I-edik felosztást unrankeléssel keressük: az első részt a legnagyobb lehetséges értéktől lefelé vizsgáljuk, és az I-ből annyit vonunk le, amennyi a nagyobb első résszel kezdődő felosztások száma, míg meg nem találjuk a megfelelő f-et. Ezután a maradék N−f birtokra ugyanezt ismételjük. A binomiális együtthatókat Pascal-háromszöggel számoljuk, az időigény O(N·K).
*/
/*
Hint 1: || Minden felosztást N−1 lehetséges vágási hely közül kiválasztott K−1 vágás ad. Ebből már következik a felosztások száma, anélkül hogy egyesével felsorolnád őket. ||
Hint 2: || Ha az első rész f, akkor a maradék N−f birtok K−1 részre bontása ugyanolyan probléma kisebb paraméterekkel. Az f-fel kezdődő felosztások száma így binomiális együtthatóval kiszámolható. ||
Hint 3: || Az I-edik kereséséhez az első részt a legnagyobb lehetséges értéktől lefelé vizsgáld: ha az I nagyobb, mint az adott f-fel kezdődő felosztások száma, vond le belőle, és lépj a következő f-re; különben ezt az f-et válaszd, és a maradékra ugyanezt ismételd. ||
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
static ull C[35][35];

ull countComp(int sum, int parts) {
    if (parts == 1) return 1;
    return C[sum - 1][parts - 1];
}

vector<int> unrankComp(int sum, int parts, ull rank) {
    if (parts == 1) return {sum};
    for (int first = sum - parts + 1; first >= 1; --first) {
        ull cnt = countComp(sum - first, parts - 1);
        if (rank > cnt) rank -= cnt;
        else {
            vector<int> tail = unrankComp(sum - first, parts - 1, rank);
            tail.insert(tail.begin(), first);
            return tail;
        }
    }
    return {};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int n = 0; n <= 30; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k) C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
    }

    int N, K;
    ull I;
    cin >> N >> K >> I;
    ull total = countComp(N, K);
    vector<int> ans = unrankComp(N, K, I);

    cout << total << '\n';
    for (int i = 0; i < K; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
