/*
    Az életkorok 1 és 150 közé esnek, ezért nem kell a teljes sorozatot rendezni: elég
    megszámolni, hány ember van az egyes korokban (gyakorisági tömb). Páratlan N esetén a
    középső ember a sorba rendezett sorozatban a (N+1)/2-edik, ezt a korokon 1-től 150-ig
    haladva, a darabszámok összegzésével találjuk meg: az első olyan kornál állunk meg, ahol az
    összeg eléri a (N+1)/2-et. Időigény O(N + 150), memória O(150).
*/
/*
Hint 1: || Nem kell az egész sorozatot rendezni: az életkorok kis egészek, ezért elég minden korból megszámolni, hány ember van. ||
Hint 2: || Páratlan N-nél a középső a (N+1)/2-edik legkisebb. Haladj a korokon 1-től 150-ig, összegezd a darabszámokat, és az első olyan korban, ahol az összeg eléri a (N+1)/2-et, ezt a kort írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> freq(151);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        ++freq[x];
    }

    int cel = (n + 1) / 2;
    for (int age = 1, sum = 0; age <= 150; ++age) {
        sum += freq[age];
        if (sum >= cel) {
            cout << age << '\n';
            return 0;
        }
    }
    return 0;
}
