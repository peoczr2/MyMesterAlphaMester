/*
Megoldás lényege:
Pozíciónként vizsgáljuk az elemeket: egy elem akkor számít bele az eredménybe, ha a következő K elem között van vele egyező érték.
Az eredmény az elemek (pozíciók) száma, nem a különböző értékeké, így ugyanaz az érték többször is beleszámíthat.
Minden i-hez végignézzük a következő K elemet (a sorozat végéig), és az első egyezésnél megszakítjuk a keresést; az időigény O(N*K).
*/
/*
Hint 1: || A kérdés az elemek száma, nem a különböző értékeké: ugyanaz az érték többször is beleszámíthat. Pozíciónként gondolkodj. ||
Hint 2: || Mivel N és K is legfeljebb 100, két egymásba ágyazott ciklus bőven belefér az időlimitbe. A belső ciklust az első egyezésnél megszakíthatod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int db = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n && j <= i + k; j++) {
            if (a[j] == a[i]) {
                db++;
                break;
            }
        }
    }
    cout << db << endl;
    return 0;
}
