/*
Megoldás lényege:
Minden héten a városok közötti minimális feszítőfa költségét kell megadni, ha a hálózat összefüggő.
Új él hozzáadása után az új minimális feszítőfa megkapható a régi minimális feszítőfa éleiből és az új élből, ezért elég az eddigi feszítőfát (legfeljebb N-1 él) tárolni, és minden héten Kruskal-algoritmust futtatni erre a kevés élre.
Ha a Kruskal-algoritmus N-1 élt választ ki, a hálózat összefüggő, és a költség az élek összege; különben az adott héten 0 a válasz.
A költség az idővel nem nő, így az első sorba az a hét kerül, amelytől kezdve a legkisebb költség már nem csökken: ez az első hét, amikor a végső minimumot elértük.
Az időigény O(K * N log N), ami N ≤ 100 és K ≤ 10 000 mellett bőven belefér.
*/
/*
Hint 1: || Az új él hozzáadása után nem kell az összes élt újra vizsgálni: az új minimális feszítőfa mindig megtalálható a régi feszítőfa éleiből és az új élből. ||
Hint 2: || Tárold az eddigi minimális feszítőfa éleit (legfeljebb N-1 darab), hetente rendezd őket súly szerint, majd DSU-val válogasd ki az éleket; ha N-1 él kerül be, a költség a súlyok összege, különben 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct El {
    int a, b, w;
};

int keres(vector<int>& szulo, int x) {
    while (szulo[x] != x) {
        szulo[x] = szulo[szulo[x]];
        x = szulo[x];
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<El> fa;                        // az eddigi minimális feszítőfa élei (legfeljebb n-1)
    vector<long long> koltseg(k + 1, 0);  // koltseg[het]: az adott heti költség (0, ha nem összefüggő)

    for (int het = 1; het <= k; ++het) {
        El uj;
        cin >> uj.a >> uj.b >> uj.w;
        fa.push_back(uj);
        sort(fa.begin(), fa.end(), [](const El& x, const El& y) { return x.w < y.w; });

        vector<int> szulo(n + 1);
        iota(szulo.begin(), szulo.end(), 0);
        vector<El> uj_fa;
        long long osszeg = 0;
        for (const El& e : fa) {
            int ra = keres(szulo, e.a), rb = keres(szulo, e.b);
            if (ra != rb) {
                szulo[ra] = rb;
                uj_fa.push_back(e);
                osszeg += e.w;
            }
        }
        fa = uj_fa;
        koltseg[het] = (int)fa.size() == n - 1 ? osszeg : 0;
    }

    int elso = 0;
    if (koltseg[k] != 0) {
        for (int het = 1; het <= k; ++het) {
            if (koltseg[het] == koltseg[k]) {
                elso = het;
                break;
            }
        }
    }

    cout << elso << '\n';
    for (int het = 1; het <= k; ++het) cout << koltseg[het] << '\n';
    return 0;
}
