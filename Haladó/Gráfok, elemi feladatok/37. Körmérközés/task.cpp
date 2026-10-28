/*
Megoldás lényege:
Egy olyan sorrendet keresünk, amelyben mindenki legyőzte a közvetlenül előtte állót. Ilyen sorrend mindig létezik (Rédei-tétel), és beszúrásos módszerrel megkapjuk.
A versenyzőket egyenként vesszük. Az új versenyzőt a sor végére tesszük, majd amíg az előtte álló legyőzte, felcseréljük vele, így az új versenyző egyre előrébb kerül.
Minden csere után a szomszédos párok érvényesek maradnak, így a végeredmény is megfelelő. Az időigény O(N^2), ami N <= 100 mellett bőven elég.
*/
/*
Hint 1: || Nem kell a legjobb sorrendet megtalálni: elég olyan sorrend, amelyben minden szomszédos párban a későbbi versenyző legyőzte a korábbit. Ilyen sorrend mindig létezik, és fokozatosan is építhető. ||
Hint 2: || Tartsd érvényesnek az eddigi sorrendet, és az új versenyzőt tedd a végére. Ha az előtte álló legyőzte, cseréld meg a két helyet, és ismételd, amíg az új versenyző nem győzte le az előtte állót. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<char>> beat(n + 1, vector<char>(n + 1, 0));
    int games = n * (n - 1) / 2;
    for (int i = 0; i < games; ++i) {
        int a, b;
        cin >> a >> b;
        beat[a][b] = 1;
    }

    vector<int> order;
    for (int v = 1; v <= n; ++v) {
        order.push_back(v);
        // v egyre előrébb csúszik, amíg az előtte álló le nem győzte
        for (int i = (int)order.size() - 1; i > 0 && beat[order[i - 1]][v]; --i) {
            swap(order[i - 1], order[i]);
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << order[i] << (i + 1 < n ? ' ' : '\n');
    }
    return 0;
}
