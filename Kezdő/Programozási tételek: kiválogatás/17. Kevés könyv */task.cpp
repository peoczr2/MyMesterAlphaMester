/*
Megoldás lényege:
Minden könyvnél a könyvtárban lévő példányszám a teljes példányszám mínusz a kikölcsönzött példányszám.
Ha ez legfeljebb 2, a könyv sorszámát (1-től, a beolvasási sorrendben) eltesszük egy vektorba.
A könyveket soronként olvassuk be, mert a szerző és a cím tartalmazhat szóközt, a mezőket pontosvesszőnél bontjuk szét.
A sorszámokat növekvő sorrendben kapjuk, így a vektor már rendezett, és csak a darabszámot és a sorszámokat kell kiírni.
Az időigény a könyvek számával arányos, ami a legfeljebb 100 könyv miatt bőven belefér.
*/
/*
Hint 1: || Egy könyvből elérhető példányszám: a teljes példányszám mínusz a kikölcsönzött példányszám. A feladat szerint azokat kell kiválogatni, ahol ez legfeljebb 2. ||
Hint 2: || A könyvek adatait soronként olvasd be (getline), mert a cím és a szerző tartalmazhat szóközt. A négy mezőt pontosvessző szerint válaszd szét, és a számmezőket alakítsd számmá. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> talalat;
    string sor;
    for (int i = 1; i <= n; ++i) {
        getline(cin, sor);
        stringstream ss(sor);
        string szerzo, cim, peldany, kolcsonzott;
        getline(ss, szerzo, ';');
        getline(ss, cim, ';');
        getline(ss, peldany, ';');
        getline(ss, kolcsonzott, ';');
        if (stoi(peldany) - stoi(kolcsonzott) <= 2) talalat.push_back(i);
    }

    cout << talalat.size();
    for (int x : talalat) cout << ' ' << x;
    cout << '\n';
    return 0;
}
