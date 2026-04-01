#include <bits/stdc++.h>
using namespace std;

/*
    Minden rendszámhoz eltároljuk az utolsó megfigyelt helyet és időt. Ha ugyanaz
    az autó a következő megfigyeléskor a szomszédos helyen jelenik meg, akkor az
    adott szakaszra egy új jelöltet kapunk. A minimális időt és a korábbi autót
    külön-külön vezetjük.
*/

struct Info {
    int hely = -1;
    int ido = -1;
    int elsosor = -1;
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
                    if (diff < bestTF[seg] || (diff == bestTF[seg] && x.ido < bestOf[seg])) {
                        bestTF[seg] = diff;
                        bestOf[seg] = x.ido;
                        bestF[seg] = r;
                    }
                } else {
                    if (diff < bestTB[seg] || (diff == bestTB[seg] && x.ido < bestOb[seg])) {
                        bestTB[seg] = diff;
                        bestOb[seg] = x.ido;
                        bestB[seg] = r;
                    }
                }
            }
        }
        x.hely = h;
        x.ido = time;
        x.elsosor = idx;
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