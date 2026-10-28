/*
Megoldás lényege:
Mindkét sorozat növekvő, ezért az embereket lakhelyük szerint sorban dolgozzuk fel. Mindegyik embernek a [lakhely − K, lakhely + K] intervallumba eső, még szabad árushelyek közül a legkisebbet foglaljuk le, ha van ilyen. Mivel minden intervallum azonos hosszú, a túl balra eső árushelyeket a későbbi emberek sem használhatják, így egyetlen mutató elegendő, és az egész O(N + M) időben fut. A mohó választás helyes, mert a legbaloldalibb elérhető hely lefoglalásával a jobb oldali helyek a későbbi emberek számára szabadok maradnak.
*/
/*
Hint 1: || Az emberek és az árushelyek is növekvő sorrendben vannak, ezért nem kell minden párt kipróbálni: elég a két sorozatot egyszerre, balról jobbra végigvinni. ||
Hint 2: || Egy ember lakhelye L esetén az elérhető árushelyek a [L − K, L + K] intervallumba esnek. Ha az aktuális legkisebb szabad árushely már L − K-nál kisebb, azt később senki sem használhatja, így a mutatót előre lehet léptetni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> lakhely(n);
    for (auto &x : lakhely) cin >> x;

    int m;
    cin >> m;
    vector<long long> hely(m);
    for (auto &x : hely) cin >> x;

    long long k;
    cin >> k;

    sort(lakhely.begin(), lakhely.end());
    sort(hely.begin(), hely.end());

    int db = 0;
    int j = 0;
    for (int i = 0; i < n; i++) {
        // a lakhelytől K-nál messzebb balra lévő árushelyek a későbbi embereknek sem jók
        while (j < m && hely[j] < lakhely[i] - k) j++;
        if (j < m && hely[j] <= lakhely[i] + k) {
            db++;
            j++;
        }
    }
    cout << db << "\n";
    return 0;
}
