/*
Megoldás lényege:
Az i. sorban az i. horgász halainak száma található halfajtánként, tehát a horgász összes halát az adott sor elemeinek összege adja. Soronként egy belső ciklus összegzi a K számot, a külső ciklus a horgászokon megy végig, és az eredményt szóközzel elválasztva egy sorba írjuk ki.
Minden elemet egyszer olvasunk be és adunk hozzá az összeghez, így az időigény O(N·K).
*/
/*
Hint 1: || Minden horgászhoz külön összeget kell képezni: a horgász sorában lévő K számot kell összegezni. Melyik ciklus fusson a horgászokon, és melyik a halfajtákon? ||
Hint 2: || A külső ciklus a horgászokon megy, a belső K számot olvas be és adja egy változóba. A belső ciklus lezárása után írd ki az összeget, az elemeket szóköz válassza el. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int osszes = 0;
        for (int j = 0; j < k; j++) {
            int halak;
            cin >> halak;
            osszes += halak;
        }
        if (i > 0) {
            cout << ' ';
        }
        cout << osszes;
    }
    cout << '\n';
    return 0;
}
