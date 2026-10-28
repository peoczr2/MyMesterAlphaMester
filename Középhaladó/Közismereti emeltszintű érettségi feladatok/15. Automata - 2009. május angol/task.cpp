/*
Megoldás lényege: a rekeszek kezdeti adatait eltároljuk, majd a vásárlásokat sorban dolgozzuk fel. Az automata összértéke a darabszám és az egységár szorzatainak összege. A 3. részfeladatban az a rekesz felel meg, ahol legalább 7 darab van, és 7 darab ára nem haladja meg a P összeget. A 4. részfeladatban a fizetendő összeget (egységár * C) a mohó algoritmussal bontjuk címletekre: a legnagyobb címletből annyit veszünk, amennyit a hátralévő összeg enged, így a címletek száma minimális. Az 5. részfeladatban az utolsó rekesz vásárlásait a kezdeti állapotból szimuláljuk: a sikeres vásárlás csökkenti a darabszámot, a befizetett összeget a bedobott érmék értékéből számoljuk. Az időigény O(N + 7V).
*/
/*
Hint 1: || A 3. és a 4. részfeladat is a rekeszek kezdeti adataiból dolgozik: a fizetendő összeg mindig az egységár és a darabszám szorzata. ||
Hint 2: || A 4. részfeladathoz a címleteket nagyobbtól kisebbig nézd végig, és mindegyikből annyit vegyél, amennyit a még hátralévő összeg megenged; az eredményt címlet szerint növekvő sorrendben írd ki. ||
Hint 3: || Az 5. részfeladatban a vásárlásokat a bemenet sorrendjében dolgozd fel, és egy sikeres vásárlás után csökkentsd a rekesz darabszámát, mert később már kevesebb csokoládé áll rendelkezésre. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int CIMLET[7] = {1, 2, 5, 10, 20, 50, 100};

int main() {
    int n;
    cin >> n;
    vector<int> db(n + 1, 0), ar(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int s, d, a;
        cin >> s >> d >> a;
        db[s] = d;
        ar[s] = a;
    }

    int v, p, r, c;
    cin >> v >> p >> r >> c;
    vector<int> vr(v), vq(v), befizetett(v, 0);
    for (int i = 0; i < v; i++) {
        cin >> vr[i] >> vq[i];
        for (int j = 0; j < 7; j++) {
            int sz;
            cin >> sz;
            befizetett[i] += sz * CIMLET[j];
        }
    }

    // 1. részfeladat: a kezdeti összérték
    long long osszertek = 0;
    for (int s = 1; s <= n; s++) osszertek += (long long)db[s] * ar[s];
    cout << "#\n" << osszertek << "\n";

    // 2. részfeladat: a vásárlásokban érintett rekeszek (növekvő sorrendben)
    set<int> erintett(vr.begin(), vr.end());
    cout << "#\n";
    if (erintett.empty()) {
        cout << -1 << "\n";
    } else {
        bool elso = true;
        for (int s : erintett) {
            if (!elso) cout << " ";
            cout << s;
            elso = false;
        }
        cout << "\n";
    }

    // 3. részfeladat: rekeszek, ahonnan 7 darab a P összegből megvásárolható
    cout << "#\n";
    vector<int> hetes;
    for (int s = 1; s <= n; s++)
        if (db[s] >= 7 && (long long)ar[s] * 7 <= p) hetes.push_back(s);
    if (hetes.empty()) {
        cout << -1 << "\n";
    } else {
        for (size_t i = 0; i < hetes.size(); i++) {
            if (i) cout << " ";
            cout << hetes[i];
        }
        cout << "\n";
    }

    // 4. részfeladat: a pontos fizetéshez felhasznált címletek
    cout << "#\n";
    int maradt = ar[r] * c;
    int darab[7] = {0, 0, 0, 0, 0, 0, 0};
    for (int j = 6; j >= 0; j--) {
        darab[j] = maradt / CIMLET[j];
        maradt -= darab[j] * CIMLET[j];
    }
    for (int j = 0; j < 7; j++)
        if (darab[j] > 0) cout << CIMLET[j] << " " << darab[j] << "\n";

    // 5. részfeladat: az utolsó rekesz vásárlásainak eredménye
    cout << "#\n";
    int utolso = n;
    vector<int> sim = db;
    bool volt_vasarlas = false;
    for (int i = 0; i < v; i++) {
        if (vr[i] != utolso) continue;
        volt_vasarlas = true;
        int fizetendo = ar[utolso] * vq[i];
        if (sim[utolso] < vq[i]) {
            cout << i + 1 << " keves a csoki\n";
        } else if (befizetett[i] < fizetendo) {
            cout << i + 1 << " nem volt eleg a penz\n";
        } else {
            sim[utolso] -= vq[i];
            cout << i + 1 << " " << vq[i] << "\n";
        }
    }
    if (!volt_vasarlas) cout << -1 << "\n";

    return 0;
}
