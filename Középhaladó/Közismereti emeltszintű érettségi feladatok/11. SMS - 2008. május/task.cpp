/*
Megoldás lényege:
Az üzeneteket érkezési sorrendben beolvassuk, és minden üzenethez eltároljuk az időpontját (percben), a telefonszámát, a szövegét és a hosszát.
A memóriában levő üzenetek a bemenet első M érkező üzenete, ezért az utolsó érkezéskor a legfrissebb tárolt üzenet a min(K, M)-edik.
A leghosszabb és a legrövidebb üzenetet, valamint a hosszstatisztikát egyetlen bejárással kapjuk meg, az azonos hosszúságúak közül az első marad.
A törlési szimulációban minden óra kezdetekor a tárolt üzenetek száma nullázódik, és ha a telefon éppen tele van, az üzenet a szolgáltatónál marad.
A barátnő üzeneteinek időkülönbségét a saját üzenetei között, a telefonszámonkénti csoportosítást pedig az első előfordulás sorrendjében számoljuk.
Az időigény O(K), K ≤ 100 mellett nagyon kicsi.
*/
/*
Hint 1: || Az üzeneteket érkezési sorrendben kell feldolgozni, és a szövegsor beolvasásánál a sor végi kocsi-vissza karaktert el kell távolítani. ||
Hint 2: || Az első M üzenet van a telefonon, így a legfrissebb tárolt üzenet a min(K, M)-edik. A törlési szimulációban az óra kezdeténél nullázd a tárolt darabszámot, és csak akkor növeld, ha van hely. ||
Hint 3: || A csoportosításhoz egy térkép adja meg, melyik telefonszámhoz melyik üzenetek tartoznak. Az első hívás sorrendjét egy külön vektor őrzi, ez határozza meg a kiírás sorrendjét. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Uzenet {
    int ora, perc;
    string tel, szoveg;
    int hossz;
};

// Egy sort olvas, és eltávolítja a végéről a kocsi-vissza karaktert (CRLF fájlok miatt).
string sorOlvas() {
    string s;
    getline(cin, s);
    if (!s.empty() && s.back() == '\r') s.pop_back();
    return s;
}

int main() {
    int k, m;
    string bar;
    {
        istringstream is(sorOlvas());
        is >> k >> m >> bar;
    }
    vector<Uzenet> u(k);
    for (auto& x : u) {
        istringstream is(sorOlvas());
        is >> x.ora >> x.perc >> x.tel;
        x.szoveg = sorOlvas();
        x.hossz = (int)x.szoveg.size();
    }

    // 1. részfeladat: az utolsó érkezéskor a memóriában levő legfrissebb üzenet
    cout << "#\n";
    cout << u[min(k, m) - 1].szoveg << "\n";

    // 2. és 3. részfeladat: a leghosszabb és a legrövidebb üzenet (egyezésnél az első)
    int hosszu = 0, rovid = 0;
    for (int i = 1; i < k; i++) {
        if (u[i].hossz > u[hosszu].hossz) hosszu = i;
        if (u[i].hossz < u[rovid].hossz) rovid = i;
    }
    cout << "#\n";
    cout << u[hosszu].ora << " " << u[hosszu].perc << " " << u[hosszu].tel << " " << u[hosszu].szoveg << "\n";
    cout << "#\n";
    cout << u[rovid].ora << " " << u[rovid].perc << " " << u[rovid].tel << " " << u[rovid].szoveg << "\n";

    // 4. részfeladat: hosszstatisztika (1-20, 21-40, 41-60, 61-80, 81-100)
    int db[5] = {0, 0, 0, 0, 0};
    for (auto& x : u) {
        int idx = (x.hossz - 1) / 20;
        if (idx < 0) idx = 0;
        if (idx > 4) idx = 4;
        db[idx]++;
    }
    cout << "#\n";
    cout << db[0] << " " << db[1] << " " << db[2] << " " << db[3] << " " << db[4] << "\n";

    // 5. részfeladat: a szolgáltatónál maradó üzenetek száma, ha minden óra kezdetekor törlik a tárolt üzeneteket
    int tarolt = 0, szolgaltatonal = 0;
    int elozoIdo = -1;
    for (auto& x : u) {
        int ido = x.ora * 60 + x.perc;
        // Volt-e óra kezdete (xx:00) az előző és ez az érkezés között (az érkezéssel egy időben is).
        if (ido / 60 > elozoIdo / 60) tarolt = 0;
        if (tarolt < m) tarolt++;
        else szolgaltatonal++;
        elozoIdo = ido;
    }
    cout << "#\n";
    cout << szolgaltatonal << "\n";

    // 6. részfeladat: a barátnő két egymás utáni üzenete közötti legnagyobb időtartam (perc)
    vector<int> barat;
    for (auto& x : u) {
        if (x.tel == bar) barat.push_back(x.ora * 60 + x.perc);
    }
    cout << "#\n";
    if (barat.size() <= 1) {
        cout << "nem\n";
    } else {
        int legh = 0;
        for (size_t i = 1; i < barat.size(); i++) {
            legh = max(legh, barat[i] - barat[i - 1]);
        }
        cout << legh << "\n";
    }

    // 7. részfeladat: a telefonszámok csoportosítva, az első hívás szerinti sorrendben
    vector<string> telefonok;
    map<string, vector<int>> csoport;
    for (int i = 0; i < k; i++) {
        if (!csoport.count(u[i].tel)) telefonok.push_back(u[i].tel);
        csoport[u[i].tel].push_back(i);
    }
    cout << "#\n";
    cout << telefonok.size() << "\n";
    for (auto& t : telefonok) {
        vector<int>& idx = csoport[t];
        cout << t << " " << idx.size() << "\n";
        for (int i : idx) {
            cout << u[i].ora << " " << u[i].perc << " " << u[i].szoveg << "\n";
        }
    }
    return 0;
}
