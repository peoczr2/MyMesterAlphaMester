/*
A megoldás lényege, hogy minden emberhez megszámoljuk, hány gyereke van.
Ha egy kapcsolatban valaki szülőként szerepel, akkor biztosan gyerekes ember,
ezért elegendő egy logikai jelölő tömbben megjegyezni róla ezt az információt.
A végén 1-től N-ig végigszkenneljük a tömböt, és kiírjuk azokat, akik kaptak
legalább egy jelölést.
*/
/*
Hint 1: || Minden szülő-gyerek párból csak a szülő sorszáma érdekes ehhez a feladathoz. ||
Hint 2: || Egy logikai tömbben elég megjegyezni, hogy egy embernek van-e már gyereke. ||
Hint 3: || A kimenet növekvő sorrendje miatt a végső listázásnál 1-től N-ig haladj. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<char> vanGyereke(N + 1, false);
    for (int i = 0; i < K; ++i) {
        int szulo, gyerek;
        cin >> szulo >> gyerek;
        vanGyereke[szulo] = true;
    }

    vector<int> eredmeny;
    for (int i = 1; i <= N; ++i) {
        if (vanGyereke[i]) eredmeny.push_back(i);
    }

    cout << eredmeny.size() << '\n';
    for (size_t i = 0; i < eredmeny.size(); ++i) {
        if (i) cout << ' ';
        cout << eredmeny[i];
    }
    cout << '\n';

    return 0;
}
