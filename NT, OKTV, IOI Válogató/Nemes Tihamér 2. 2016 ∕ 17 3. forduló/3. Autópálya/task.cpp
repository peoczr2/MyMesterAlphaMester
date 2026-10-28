/*
Megoldás lényege:
Minden rendszámhoz tároljuk az utolsó megfigyelés helyét és idejét, valamint az első megfigyelés idejét. Ha ugyanaz az autó a következő megfigyeléskor a szomszédos helyen jelenik meg, a két időpont különbsége az adott szakasz menetideje, az irány pedig attól függ, hogy a helyek sorszáma nő vagy csökken. Szakaszonként és irányonként a legkisebb menetidőt és a hozzá tartozó rendszámot tartjuk nyilván; döntetlennél az a rendszám nyer, amelynek autója korábban kezdte az útját, vagyis kisebb az első megfigyelés ideje. Egy megfigyelés feldolgozása állandó idejű, így az egész megoldás O(M) (hash-táblával átlagosan).
*/
/*
Hint 1: || Egy autó útját az időrendben egymás utáni megfigyelések írják le: két egymás utáni, szomszédos helyen készült megfigyelés egy szakasz bejárását adja. ||
Hint 2: || Szakaszonként és irányonként külön tárold az eddigi legkisebb menetidőt és a hozzá tartozó rendszámot. Az előre (kisebb sorszámú helyről nagyobbra) és a visszafelé bejárásokhoz is legyen külön tömb. ||
Hint 3: || Döntetlen esetén az a rendszám kell, amelyiknek autója korábban indult, vagyis amelynek első megfigyelési ideje kisebb. Ezt az időt autónként az első megfigyeléskor jegyezd fel. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Info {
    int hely = -1;
    int ido = -1;
    int kezdes = -1;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    const int MAXP = 100000;
    vector<int> bestF(n, 0), bestB(n, 0);
    vector<int> bestTF(n, INT_MAX), bestTB(n, INT_MAX);
    vector<int> bestOf(n, INT_MAX), bestOb(n, INT_MAX);

    unordered_map<int, Info> last;
    last.reserve(2000);

    for (int idx = 0; idx < m; ++idx) {
        int r, h, o, p;
        cin >> r >> h >> o >> p;
        int time = o * 60 + p;
        auto &x = last[r];
        if (x.hely != -1) {
            int diff = time - x.ido;
            if (abs(h - x.hely) == 1) {
                int seg = min(h, x.hely) - 1;
                if (h > x.hely) {
                    if (diff < bestTF[seg] || (diff == bestTF[seg] && x.kezdes < bestOf[seg])) {
                        bestTF[seg] = diff;
                        bestOf[seg] = x.kezdes;
                        bestF[seg] = r;
                    }
                } else {
                    if (diff < bestTB[seg] || (diff == bestTB[seg] && x.kezdes < bestOb[seg])) {
                        bestTB[seg] = diff;
                        bestOb[seg] = x.kezdes;
                        bestB[seg] = r;
                    }
                }
            }
        }
        if (x.hely == -1) x.kezdes = time;
        x.hely = h;
        x.ido = time;
    }

    for (int i = 0; i < n - 1; ++i) {
        if (i) cout << ' ';
        cout << bestF[i];
    }
    cout << '\n';
    for (int i = 0; i < n - 1; ++i) {
        if (i) cout << ' ';
        cout << bestB[i];
    }
    cout << '\n';
    return 0;
}