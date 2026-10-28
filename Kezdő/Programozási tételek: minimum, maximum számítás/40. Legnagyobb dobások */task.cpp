/*
Megoldás lényege:
Minden versenyző dobásai közül a maximumot külön keressük meg, mert versenyzőnként külön eredmény kell. A sikertelen dobás -1 értéke soha nem lehet nagyobb a 0 kezdőértéknél, így a sikertelen dobások automatikusan kimaradnak; ha minden dobás sikertelen, a kezdőérték 0 marad, ami a feladat szerinti eredmény. Az N eredményt egy sorba, szóközzel elválasztva írjuk ki. Az időigény O(6N) = O(N), a tárigény O(1).
*/
/*
Hint 1: || Versenyzőnként külön maximumkeresés kell: egy versenyző 6 dobását olvasd be egymás után, és közben tartsd nyilván az eddigi legnagyobbat egyetlen változóban. ||
Hint 2: || A sikertelen dobás értéke -1, ezért a maximum kezdőértéke 0 legyen: így a -1 értékek soha nem kerülnek a maximumba, és ha minden dobás sikertelen, az eredmény 0 marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int best = 0;
        for (int j = 0; j < 6; j++) {
            int d;
            cin >> d;
            if (d > best) best = d;
        }
        if (i > 0) cout << ' ';
        cout << best;
    }
    cout << "\n";
    return 0;
}
