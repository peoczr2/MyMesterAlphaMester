/*
Megoldás lényege:
Ha a fiú egy úton egymás mellett álló a_j nyárfát választ, a köztük levő a_j - 1 szilva az övé lesz.
Ha több különálló szakaszt választ, minden szakasz egyel kevesebb szilvát ad, így a szilvák száma N - (a szakaszok száma).
Ezért a lehető legkevesebb szakaszt kell használni: az utakat a nyárfáik száma szerint csökkenő sorrendbe rendezzük, és sorban vesszük a legnagyobbakat, amíg együtt el nem érik az N nyárfát.
Ha így k szakaszt használunk, a válasz N - k. A rendezés miatt az időigény O(K log K).
*/
/*
Hint 1: || Egy összefüggő szakasz a_j nyárfával a_j - 1 szilvát ad. Ha a fiú több különálló szakaszt választ, minden szakasz egyel kevesebb szilvát ad: mennyi a szilvák száma, ha k szakasz van? ||
Hint 2: || Minimalizáld a szakaszok számát: rendezd az utakat nyárfaszám szerint csökkenően, és add össze a legnagyobbakat, amíg az összeg el nem éri N-t. Ha ehhez k út kell, a válasz N - k. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    int k;
    cin >> n >> k;
    vector<long long> ny(k);
    for (long long &x : ny) cin >> x;

    sort(ny.begin(), ny.end(), greater<long long>());

    long long got = 0, used = 0;    // a kiválasztott nyárfák száma, a használt utak száma
    for (int i = 0; i < k && got < n; i++) {
        got += ny[i];
        used++;
    }
    long long chosen = min(n, got); // ha összesen kevesebb nyárfa van, mindet kiválasztjuk
    cout << chosen - used << '\n';
    return 0;
}
