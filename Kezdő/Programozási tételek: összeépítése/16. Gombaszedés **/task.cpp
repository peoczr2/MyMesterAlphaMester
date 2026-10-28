/*
Megoldás lényege:
A gombákat súly szerint csökkenő sorrendbe rendezzük, azonos súly esetén Csiperke, Rókagomba, Lila pereszke sorrendben. Józsi mindig a sorrendben első olyan gombát szedi, amely szedhető: Lila pereszkét csak akkor, ha az erdőben már nincs szedetlen Csiperke, és a gomba beleférjen a zsákba. Amelyik gomba nem fér bele, az a kapacitás csökkenése miatt később sem fér bele, ezért véglegesen kihagyható; a kihagyott Csiperke azonban az erdőben marad, így Lila pereszkét nem szed. A szimuláció minden lépésben a listán keresi az első szedhető gombát, legfeljebb N szedéssel és N keresési körrel, így az időigény O(N^2), ami N <= 1000 mellett bőven belefér.
*/
/*
Hint 1: || Rendezd a gombákat súly szerint csökkenő sorrendbe, azonos súlynál a C, R, L fajták sorrendjében. Így a sorban első szedhető gomba mindig a helyes választás. ||
Hint 2: || A zsák kapacitása csak csökken, ezért ami egyszer nem fér bele, később sem fog. A Lila pereszkét tiltó szabályhoz azt kell nyilvántartani, hány Csiperke van még az erdőben. ||
Hint 3: || Ismételd: keresd meg az első olyan gombát, amely most szedhető, és ha nem fér bele, jelöld kihagyottnak. Ha nincs több szedhető gomba, állj meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Gomba {
    char fajta;
    int suly;
    bool szedve = false;
    bool kihagyva = false;
};

int sorrend(char f) {
    if (f == 'C') return 0;
    if (f == 'R') return 1;
    return 2;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Gomba> g(n);
    for (auto &x : g) cin >> x.fajta >> x.suly;

    sort(g.begin(), g.end(), [](const Gomba &a, const Gomba &b) {
        if (a.suly != b.suly) return a.suly > b.suly;
        return sorrend(a.fajta) < sorrend(b.fajta);
    });

    int kapacitas = m;
    while (true) {
        int csiperkeMaradt = 0;
        for (const auto &x : g)
            if (x.fajta == 'C' && !x.szedve) csiperkeMaradt++;

        int kivalasztott = -1;
        for (int i = 0; i < n; i++) {
            if (g[i].szedve || g[i].kihagyva) continue;
            if (g[i].fajta == 'L' && csiperkeMaradt > 0) continue;
            if (g[i].suly > kapacitas) {
                g[i].kihagyva = true;
                continue;
            }
            kivalasztott = i;
            break;
        }
        if (kivalasztott == -1) break;
        g[kivalasztott].szedve = true;
        kapacitas -= g[kivalasztott].suly;
    }

    long long db[3] = {0, 0, 0}, suly[3] = {0, 0, 0};
    for (const auto &x : g) {
        if (!x.szedve) continue;
        db[sorrend(x.fajta)]++;
        suly[sorrend(x.fajta)] += x.suly;
    }
    cout << db[0] + db[1] + db[2] << " " << suly[0] + suly[1] + suly[2] << "\n";
    for (int i = 0; i < 3; i++) cout << db[i] << " " << suly[i] << "\n";
    return 0;
}
