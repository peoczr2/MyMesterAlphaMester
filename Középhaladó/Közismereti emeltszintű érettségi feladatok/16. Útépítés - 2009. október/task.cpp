/*
Megoldás lényege: az áthaladásokat a belépési idő szerinti sorrendben dolgozzuk fel, a belépési időt másodpercre váltjuk. Előzés nincs, ezért egy jármű elhagyási ideje az saját belépési idejéből és a vele azonos irányban korábban belépett jármű elhagyási idejéből adódik: a kettő maximuma lesz az eredmény. Az 1. részfeladat a K-adik jármű irányát adja, a 2. a két utolsó 1 irányú jármű belépési idejének különbsége (ha csak egy van, 0). A 3. részfeladatban a belépési óra szerint számoljuk a járműveket irányonként. A 4. részfeladatban a saját áthaladási idő szerint stabil rendezést végzünk, így az azonos sebességű járművek a bemenet sorrendjében maradnak. Az 5. részfeladatban a 0 irányú járművek elhagyási idejét írjuk ki. Az időigény O(N log N).
*/
/*
Hint 1: || A belépési időket váltsd át másodperccé: az óra, perc és másodperc hármasából egyetlen egész szám lesz, így az időkülönbségek egyszerűen kivonhatók. ||
Hint 2: || Ugyanabban az irányban a később érkező jármű nem előzhet, ezért az elhagyási idő legalább az előtte haladó jármű elhagyási ideje: a saját és az előző elhagyási idő maximumát vedd. ||
Hint 3: || A 4. részfeladatnál a nagyobb sebességhez rövidebb áthaladási idő tartozik, ezért a járműveket az áthaladási idő szerint rendezd, és a rendezés legyen stabil, hogy az azonos sebességű járművek sorrendje megmaradjon. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Másodpercben megadott időpont kiírása óra perc másodperc alakban.
void kiir_ido(long long x) {
    cout << x / 3600 << " " << (x % 3600) / 60 << " " << x % 60 << "\n";
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> ora(n), perc(n), masodperc(n), tart(n), irany(n);
    vector<long long> belep(n), kilep(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> ora[i] >> perc[i] >> masodperc[i] >> tart[i] >> irany[i];
        belep[i] = ora[i] * 3600LL + perc[i] * 60LL + masodperc[i];
    }

    // 1. részfeladat: a K. jármű iránya
    cout << "#\n" << (k >= 1 ? irany[k - 1] : -1) << "\n";

    // 2. részfeladat: az utolsó két 1 irányú jármű belépési idejének különbsége
    vector<int> egyes;
    for (int i = 0; i < n; i++)
        if (irany[i] == 1) egyes.push_back(i);
    long long kul;
    if (egyes.size() >= 2)
        kul = belep[egyes[egyes.size() - 1]] - belep[egyes[egyes.size() - 2]];
    else if (egyes.size() == 1)
        kul = 0;
    else
        kul = -1;
    cout << "#\n" << kul << "\n";

    // 3. részfeladat: óránként és irányonként a belépések száma
    cout << "#\n";
    for (int d = 0; d < 2; d++) {
        vector<int> db(24, 0);
        for (int i = 0; i < n; i++)
            if (irany[i] == d) db[ora[i]]++;
        for (int h = 0; h < 24; h++) {
            if (h) cout << " ";
            cout << db[h];
        }
        cout << "\n";
    }

    // 4. részfeladat: a 10 leggyorsabb jármű (saját áthaladási idő szerint, stabil rendezés)
    vector<int> sorrend(n);
    iota(sorrend.begin(), sorrend.end(), 0);
    stable_sort(sorrend.begin(), sorrend.end(),
                [&](int a, int b) { return tart[a] < tart[b]; });
    cout << "#\n";
    for (int j = 0; j < min(10, n); j++) {
        int i = sorrend[j];
        cout << ora[i] << " " << perc[i] << " " << masodperc[i] << " " << irany[i] << "\n";
    }

    // 5. részfeladat: a 0 irányú járművek elhagyási ideje növekvő sorrendben
    long long utolso[2] = {-1, -1};
    for (int i = 0; i < n; i++) {
        int d = irany[i];
        kilep[i] = max(belep[i] + tart[i], utolso[d]);
        utolso[d] = kilep[i];
    }
    vector<long long> nulla;
    for (int i = 0; i < n; i++)
        if (irany[i] == 0) nulla.push_back(kilep[i]);
    sort(nulla.begin(), nulla.end());
    cout << "#\n";
    for (long long x : nulla) kiir_ido(x);

    return 0;
}
