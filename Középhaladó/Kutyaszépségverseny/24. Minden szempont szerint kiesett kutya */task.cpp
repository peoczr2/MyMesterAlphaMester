/*
Megoldás lényege:
Egy kutya minden szempont szerint kiesett, ha minden szempontban a pontszáma kisebb az adott szempont alsó határánál. Soronként ellenőrizzük ezt: ha valamelyik szempontban eléri a határt, a kutya nem esett ki mindenhol. Ha van olyan kutya, amelyik végig kiesett, a válasz VAN, különben NINCS. Az időigény O(N·M).
*/
/*
Hint 1: || A kiesés szempontonként értendő: a j. szempontban akkor esik ki a kutya, ha a j. pontszáma kisebb a j. alsó határnál. Egyetlen olyan szempont is elég a bent maradáshoz, ahol eléri a határt. ||
Hint 2: || Soronként haladj: minden kutyára egy logikai jelzőt tarts, amely kezdetben igaz, és ha valamelyik pontszám eléri az alsó határt, állítsd hamisra. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    bool van = false;
    for (int i = 0; i < n; i++) {
        bool mindenKiesett = true;
        for (int j = 0; j < m; j++) {
            int p;
            cin >> p;
            if (p >= minPont[j]) mindenKiesett = false;
        }
        if (mindenKiesett) van = true;
    }

    cout << (van ? "VAN" : "NINCS") << '\n';
    return 0;
}
