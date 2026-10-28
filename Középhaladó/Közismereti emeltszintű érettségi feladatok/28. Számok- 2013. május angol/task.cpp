/*
A kérdések sora szóközöket is tartalmazhat, ezért a kérdést külön sorként olvassuk be, a válasz sorából pedig a válasz értékét, a pontszámot és a témakör nevét egymás után kiolvassuk.
Az N kérdést egy tömbben tároljuk, majd a négy részfeladatot egy-egy egyszerű bejárással oldjuk meg: az A témakör darabszámát számlálással kapjuk.
A B témakör pontérték szerinti eloszlását egy M+1 elemű számláló tömbbel, a válaszok legkisebb és legnagyobb értékét szélsőérték-kereséssel határozzuk meg.
A témakörök számát és nevét egy halmazba (set) gyűjtve kapjuk, ami N ≤ 10000 mellett bőven az időlimiten belül marad.
*/
/*
Hint 1: || Mind a négy részfeladat egy bejárással megoldható: a kérdéseket érdemes tömbbe tárolni, és közben számolni, minimumot keresni, illetve gyűjteni. ||
Hint 2: || A kérdés sora szóközöket tartalmazhat, ezért getline-nal olvasd be, a válasz sorát pedig egy stringstream-mel bontsd három részre. A témakörök nevei set-be kerülhetnek. ||
*/

#include <bits/stdc++.h>
using namespace std;

// Levágja a sor elejéről és végéről a szóközöket és a kocsivissza (\r) karaktereket.
string levag(string s) {
    while (!s.empty() && isspace((unsigned char)s.back())) s.pop_back();
    size_t kezd = 0;
    while (kezd < s.size() && isspace((unsigned char)s[kezd])) kezd++;
    return s.substr(kezd);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    string sor;
    getline(cin, sor);  // az első sor maradéka (a sortörés)

    vector<long long> valasz(n);
    vector<int> pont(n);
    vector<string> temakor(n);
    for (int i = 0; i < n; i++) {
        getline(cin, sor);  // a kérdés szövege
        getline(cin, sor);  // válasz, pontszám, témakör
        stringstream ss(sor);
        ss >> valasz[i] >> pont[i] >> temakor[i];
    }

    string a, b;
    getline(cin, a);
    getline(cin, b);
    a = levag(a);
    b = levag(b);

    // 1. részfeladat: az A témakör feladatainak száma
    int darab_a = 0;
    for (int i = 0; i < n; i++)
        if (temakor[i] == a) darab_a++;

    // 2. részfeladat: a B témakör feladatai pontérték szerint
    vector<int> pont_db(m + 1, 0);
    for (int i = 0; i < n; i++)
        if (temakor[i] == b && pont[i] >= 1 && pont[i] <= m) pont_db[pont[i]]++;

    // 3. részfeladat: a válaszok legkisebb és legnagyobb értéke
    long long legkisebb = valasz[0], legnagyobb = valasz[0];
    for (long long v : valasz) {
        legkisebb = min(legkisebb, v);
        legnagyobb = max(legnagyobb, v);
    }

    // 4. részfeladat: a témakörök száma és nevei
    set<string> temakorok(temakor.begin(), temakor.end());

    cout << "#\n" << darab_a << "\n";

    cout << "#\n";
    for (int p = 1; p <= m; p++) cout << pont_db[p] << (p < m ? " " : "\n");

    cout << "#\n" << legkisebb << " " << legnagyobb << "\n";

    cout << "#\n" << temakorok.size() << "\n";
    bool elso = true;
    for (const string &t : temakorok) {
        if (!elso) cout << " ";
        cout << t;
        elso = false;
    }
    cout << "\n";

    return 0;
}
