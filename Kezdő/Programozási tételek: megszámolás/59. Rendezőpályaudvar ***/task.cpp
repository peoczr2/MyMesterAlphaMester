/*
Megoldás lényege:
Egy városba tartó kocsik egy vagy több szerelvénybe kerülnek, egy szerelvénybe legfeljebb K kocsi fér, és a lehető legtöbb kocsit teszik be. Ha egy városba c kocsi megy, akkor a szerelvények száma felfelé kerekített c / K, a szabad helyek száma pedig ennyi szerelvény kapacitása mínusz c. A kocsikat egy map-ben számoljuk városonként, majd minden városra kiszámoljuk a szerelvények és a szabad helyek számát. Végül a városokat szabad hely szerint csökkenő, azonos szabad hely esetén szerelvényszám szerint csökkenő sorrendbe rendezzük, és az első három várost írjuk ki. A mintán (13 kocsi, K = 2) Ajka 5 kocsival 3 szerelvényt és 1 szabad helyet ad, Sopron 2 szerelvényt és 1 szabad helyet, Szolnok 1 szerelvényt és 1 szabad helyet, ez a három sor a kimenet. Az időigény O(N log N), N legfeljebb 10 000.
*/
/*
Hint 1: || Egy szerelvényben csak ugyanoda tartó kocsik lehetnek, így minden várost külön kell kezelni. Először azt kell megtudni, hány kocsi megy az egyes városokba. ||
Hint 2: || Ha egy városba c kocsi megy, akkor a szerelvények száma c / K felfelé kerekítve, a szabad helyek száma pedig a szerelvények összkapacitása mínusz c. Egy map<string, int> alkalmas arra, hogy a városnevek alapján számolj. ||
Hint 3: || Készíts egy listát, amelyben minden városhoz szerepel a név, a szerelvények száma és a szabad helyek száma. Rendezd szabad hely szerint csökkenőre, azonos szabad hely esetén szerelvényszám szerint csökkenőre, és írd ki az első három elemet. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Varos {
    string nev;
    int szerelveny;
    int szabad;
};

int main() {
    int n, k;
    cin >> n >> k;
    map<string, int> kocsik;
    for (int i = 0; i < n; i++) {
        string varos;
        cin >> varos;
        kocsik[varos]++;
    }

    vector<Varos> lista;
    for (const auto &par : kocsik) {
        int c = par.second;
        int szerelveny = (c + k - 1) / k;
        int szabad = szerelveny * k - c;
        lista.push_back({par.first, szerelveny, szabad});
    }

    sort(lista.begin(), lista.end(), [](const Varos &a, const Varos &b) {
        if (a.szabad != b.szabad) return a.szabad > b.szabad;
        if (a.szerelveny != b.szerelveny) return a.szerelveny > b.szerelveny;
        return a.nev < b.nev;
    });

    for (int i = 0; i < (int)lista.size() && i < 3; i++) {
        cout << lista[i].nev << " " << lista[i].szerelveny << " " << lista[i].szabad << "\n";
    }
    return 0;
}
