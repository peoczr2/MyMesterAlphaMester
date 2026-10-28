/*
Megoldás lényege:
A kódolás és a dekódolás ugyanazt a sorrendet használja: előbb meghatározzuk, hogy a V-alakban felülről lefelé haladva az eredeti szöveg mely pozíciói következnek egymás után. A sorindex periodikusan változik (periódus 2·(V−1)), így minden i pozíció egy sorba kerül, és a sorokon belül a pozíciók növekvő sorrendben állnak. Ebből egy order tömb lesz: order[j] az a pozíció az eredeti szövegben, amelyből a kódolt szöveg j. karaktere származik. Kódoláskor encoded[j] = plain[order[j]], dekódoláskor pedig decoded[order[j]] = coded[j]. Így a két irány egyetlen tömbbel megoldható, az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || A dekódolás a kódolás fordítottja, ezért elég egyszer kiszámolni, hogy a kódolt szöveg egyes helyein az eredeti szöveg melyik pozíciója áll. Ezt a sorrendet mindkét irányra használhatod. ||
Hint 2: || Járd végig a sorokat felülről lefelé, és minden pozíciót tegyél abba a sorba, amelynek a sorindexe az i. pozíció maradékából adódik. A periódus 2·(V−1), és ha a maradék kisebb V-nél, az a sorindex, különben a periódusból kivonva kapod. Sorok szerint egymás után fűzd össze a pozíciókat. ||
Hint 3: || A kapott listában a j. elem azt mutatja, melyik eredeti pozícióból származik a kódolt szöveg j. karaktere. Kódoláskor tehát az eredeti szöveg ebben a sorrendben olvasandó, dekódoláskor pedig a kódolt szöveg karaktereit kell visszaírni az eredeti pozíciókba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, v;
    cin >> n >> v;
    string plain, coded;
    cin >> plain >> coded;

    int period = 2 * (v - 1);
    vector<vector<int>> rowPositions(v);
    for (int i = 0; i < n; i++) {
        int k = i % period;
        int row = (k < v) ? k : period - k;
        rowPositions[row].push_back(i);
    }

    vector<int> order;
    order.reserve(n);
    for (const vector<int>& positions : rowPositions) {
        order.insert(order.end(), positions.begin(), positions.end());
    }

    string encoded(n, ' ');
    string decoded(n, ' ');
    for (int j = 0; j < n; j++) {
        encoded[j] = plain[order[j]];
        decoded[order[j]] = coded[j];
    }

    cout << encoded << "\n" << decoded << "\n";
    return 0;
}
