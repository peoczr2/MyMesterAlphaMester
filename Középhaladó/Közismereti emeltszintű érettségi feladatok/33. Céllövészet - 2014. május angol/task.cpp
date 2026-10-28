/*
Megoldás lényege:
A versenyzők lövéseit karaktersorozatként olvassuk be ('+' találat, '-' hiba), mindenkinek a sorában a saját
rajtszáma. A pontszámot a lövések sorrendjében számoljuk: egy találat értéke 20 mínusz az addig leadott hibák
száma, de legalább 0, így minden hiba a későbbi találatok pontját csökkenti. Az 1. részfeladatban a "++"
részsorozat keresése adja a versenyzőket, a 2. részfeladatban a legtöbb lövést leadó (azonos esetben a legkisebb
rajtszámú) versenyző, a 3. részfeladatban a V. versenyző lövéseinek egyszerű végigjárása. A 4. részfeladatban a
pontszám szerinti csökkenő rendezés (holtversenynél rajtszám szerint) után a helyezés: 1 + a nála több pontot
szerzett versenyzők száma. Az időigény a bemenet méretében lineáris.
*/
/*
Hint 1: || Minden versenyző lövéseit külön sorban kapod, a rajtszám a sor sorszáma. A pontszámot úgy kapod meg, hogy a lövéseken balról jobbra haladva számolod az addig előfordult hibákat. ||
Hint 2: || Egy találat pontja 20 mínusz az addigi hibák száma, de sosem lehet negatív. A helyezésnél nem kell a holtversenyt külön kezelni: a helyezés az előtted álló, nagyobb pontszámú versenyzők számánál eggyel nagyobb szám. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egy versenyző pontszáma: egy találat értéke 20 - (az addig leadott hibák száma), de legalább 0.
int pontszam(const string &lovesek) {
    int hibak = 0, osszes = 0;
    for (char c : lovesek) {
        if (c == '-') hibak++;
        else osszes += max(0, 20 - hibak);
    }
    return osszes;
}

int main() {
    int n, v;
    cin >> n >> v;
    string sor;
    getline(cin, sor);  // az első sor maradéka
    vector<string> lov(n + 1);  // lov[i]: az i. rajtszámú versenyző lövései
    for (int i = 1; i <= n; i++) {
        getline(cin, sor);
        for (char c : sor)
            if (c == '+' || c == '-') lov[i] += c;
    }

    // 1. részfeladat: akiknek két egymás utáni lövése is talált
    cout << "#\n";
    vector<int> kettos;
    for (int i = 1; i <= n; i++)
        if (lov[i].find("++") != string::npos) kettos.push_back(i);
    if (kettos.empty()) {
        cout << -1 << "\n";
    } else {
        for (size_t k = 0; k < kettos.size(); k++) cout << (k ? " " : "") << kettos[k];
        cout << "\n";
    }

    // 2. részfeladat: a legtöbb lövést leadó versenyző (több azonos esetén a legkisebb rajtszám)
    int legtobb = 1;
    for (int i = 2; i <= n; i++)
        if (lov[i].size() > lov[legtobb].size()) legtobb = i;
    cout << "#\n" << legtobb << "\n";

    // 3. részfeladat: a V. versenyző talált lövései, találatai, leghosszabb hibátlan sorozata, pontszáma
    cout << "#\n";
    const string &sv = lov[v];
    vector<int> talalat;
    int leghosszabb = 0, aktualis = 0;
    for (size_t k = 0; k < sv.size(); k++) {
        if (sv[k] == '+') {
            talalat.push_back(k + 1);
            aktualis++;
            leghosszabb = max(leghosszabb, aktualis);
        } else {
            aktualis = 0;
        }
    }
    if (talalat.empty()) {
        cout << -1 << "\n";
    } else {
        for (size_t k = 0; k < talalat.size(); k++) cout << (k ? " " : "") << talalat[k];
        cout << "\n";
    }
    cout << talalat.size() << "\n" << leghosszabb << "\n" << pontszam(sv) << "\n";

    // 4. részfeladat: a verseny végeredménye pontszám szerint csökkenő sorrendben
    vector<int> pont(n + 1, 0);
    for (int i = 1; i <= n; i++) pont[i] = pontszam(lov[i]);
    vector<int> sorrend;
    for (int i = 1; i <= n; i++) sorrend.push_back(i);
    stable_sort(sorrend.begin(), sorrend.end(), [&](int a, int b) { return pont[a] > pont[b]; });
    cout << "#\n";
    for (int i : sorrend) {
        int hely = 1 + (int)count_if(pont.begin() + 1, pont.end(), [&](int p) { return p > pont[i]; });
        cout << hely << " " << i << " " << pont[i] << "\n";
    }
    return 0;
}
