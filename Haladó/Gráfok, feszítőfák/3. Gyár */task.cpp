/*
Megoldás lényege:
Minden várost valamelyik gyárral kell megerősített úton összekötni úgy, hogy az utak összhossza minimális legyen.
A gyártelepüléseket egy közös csúcsba vonjuk össze (közöttük nincs költség), így a feladat egy minimális feszítőfa keresése.
Az utakat hossz szerint csökkenő sorrendbe rendezzük, és a végéről (a legrövidebbtől) haladva Kruskal-algoritmussal, unió-keresés adatszerkezettel fogadjuk el azokat az utakat, amelyek két különböző komponenst kötnek össze.
Az elfogadott utak összhossza a válasz, az elfogadott utak végpontjai pedig a megerősítendő szakaszok.
Az időigény O(M log M), ami M ≤ 500 000 esetén az időkorláton belül van.
*/
/*
Hint 1: || Ha minden gyártelepülést egyetlen csúcsnak tekintesz, a feladat egy minimális feszítőfa keresése lesz: a gyárak közötti utakra nincs szükség. ||
Hint 2: || Rendezd az utakat hossz szerint, és Kruskal-algoritmussal (unió-keresés) válogasd ki azokat az utakat, amelyek nem zárnak kört; a gyárakat előre uniózd össze, hogy ne kerüljenek az összegbe. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Ut {
    int a, b, h;
};

vector<int> szulo;

int keres(int x) {
    while (szulo[x] != x) {
        szulo[x] = szulo[szulo[x]];
        x = szulo[x];
    }
    return x;
}

bool egyesit(int a, int b) {
    int ra = keres(a), rb = keres(b);
    if (ra == rb) return false;
    szulo[ra] = rb;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, m;
    cin >> n >> k >> m;

    vector<Ut> utak(m);
    for (Ut& u : utak) cin >> u.a >> u.b >> u.h;

    szulo.resize(n + 1);
    iota(szulo.begin(), szulo.end(), 0);

    // A gyártelepüléseket összevonjuk: közöttük nincs szükség útra, ezért nem kerülnek az összegbe
    int elso_gyar;
    cin >> elso_gyar;
    for (int i = 1; i < k; ++i) {
        int s;
        cin >> s;
        egyesit(elso_gyar, s);
    }

    // Hossz szerint csökkenő sorrend: a vektor végéről a legrövidebb út jön
    stable_sort(utak.begin(), utak.end(), [](const Ut& x, const Ut& y) { return x.h > y.h; });

    long long osszeg = 0;
    vector<pair<int, int>> megerositett;
    while (!utak.empty()) {
        Ut u = utak.back();
        utak.pop_back();
        if (egyesit(u.a, u.b)) {
            osszeg += u.h;
            megerositett.push_back({u.a, u.b});
        }
    }

    cout << osszeg << '\n';
    for (const auto& p : megerositett) cout << p.first << ' ' << p.second << '\n';
    return 0;
}
