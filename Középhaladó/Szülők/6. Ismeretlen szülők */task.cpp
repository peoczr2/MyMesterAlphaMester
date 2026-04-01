/*
A megoldás lényege, hogy minden emberről eltároljuk: ismert-e legalább egy szülője.
Minden beolvasott szülő-gyerek kapcsolatnál a gyereket megjelöljük, majd a végén
azokat az embereket írjuk ki növekvő sorrendben, akiknél ez a jelölés hiányzik.
*/
/*
Hint 1: || Nem kell a szülők számát, csak azt megjegyezni, hogy egy emberhez érkezett-e már kapcsolat. ||
Hint 2: || Elég egy logikai vagy 0/1 tömb N+1 elemmel, mert az azonos gyerekhez több kapcsolat is tartozhat. ||
Hint 3: || A kimenet természetes sorrendje az 1-től N-ig végigszkennelésből adódik. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<int> szulo_ismeretlen(N + 1, 1);
    for (int i = 0; i < K; ++i) {
        int sz, gy;
        cin >> sz >> gy;
        (void)sz;
        szulo_ismeretlen[gy] = 0;
    }

    vector<int> valasz;
    for (int i = 1; i <= N; ++i) {
        if (szulo_ismeretlen[i]) valasz.push_back(i);
    }

    cout << valasz.size() << '\n';
    for (int x : valasz) cout << x << ' ';
    if (!valasz.empty()) cout << '\n';
    return 0;
}
