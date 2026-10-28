/*
Megoldás lényege:
A busz útját megállónként haladva követjük, és az aktuális időt egyetlen változóban, percben tároljuk. Minden lépésnél az előző köztes megállóban töltött várakozást (ha volt ilyen) és a két megálló közötti menetidőt adjuk az időhöz, majd az új érkezési időt kiírjuk. A várakozási számok eggyel el vannak tolva: a bemenet i. várakozási száma az (i+1). megálló várakozása, ezért az indexelésnél erre figyelni kell. Az idő percben való számolása miatt az órára váltás (például 59 perc után) automatikusan helyes, a kiíráskor csak visszaalakítjuk óra és perc párra. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Az idő csak előre halad: a megállók között sorban haladj, és minden lépésnél az aktuális időhöz add hozzá az előző megálló várakozását (ha van) és a menetidőt. ||
Hint 2: || Figyelj az indexelésre: a várakozási tömb elemei eggyel el vannak tolva a megállókhoz képest, az időt pedig célszerű percben számolni, és csak a kiíráskor visszaváltani óra és perc párra. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> travel(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> travel[i];
    }

    vector<int> waitTime(n - 2);
    for (int i = 0; i < n - 2; i++) {
        cin >> waitTime[i];
    }

    int h, m;
    cin >> h >> m;
    int t = h * 60 + m;

    cout << 1 << ". " << t / 60 << " " << t % 60 << "\n";
    for (int k = 0; k + 1 < n; k++) {
        if (k >= 1) {
            t += waitTime[k - 1];
        }
        t += travel[k];
        cout << k + 2 << ". " << t / 60 << " " << t % 60 << "\n";
    }
    return 0;
}
