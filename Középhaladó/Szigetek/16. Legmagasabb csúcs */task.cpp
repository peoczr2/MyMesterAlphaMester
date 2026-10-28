/*
Megoldás lényege:
Csúcs az a belső mérés, amelynek bal szomszédja pozitív és kisebb nála, jobb szomszédja pozitív és szintén kisebb nála. Ezt a feltételt minden belső mérésre egyszer ellenőrizzük, és egy bejárással nyilvántartjuk az eddigi legmagasabb csúcs magasságát és sorszámát. Csak a szigorúan magasabb csúcs írja felül az eddigit, így a balról első legmagasabb csúcs marad meg. Ha nincs csúcs, a válasz 0. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Egy csúcs három egymást követő mérés középső eleme: a középső nagyobb a bal és a jobb szomszédjánál, miközben a két szomszéd is pozitív. ||
Hint 2: || Egyetlen végigmenésben tartsd nyilván az eddigi legmagasabb csúcs magasságát és sorszámát, és csak akkor írd felül, ha az új csúcs szigorúan magasabb. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> m(n);
    for (auto &x : m) cin >> x;

    int legmagasabb = -1;  // az eddigi legmagasabb csúcs magassága
    int sorszam = 0;       // a csúcs 1-től számozott sorszáma, 0: nincs csúcs

    for (int j = 1; j + 1 < n; j++) {
        if (m[j - 1] > 0 && m[j - 1] < m[j] && m[j] > m[j + 1] && m[j + 1] > 0) {
            if (m[j] > legmagasabb) {
                legmagasabb = m[j];
                sorszam = j + 1;
            }
        }
    }

    cout << sorszam << "\n";
    return 0;
}
