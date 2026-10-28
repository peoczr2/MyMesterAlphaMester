/*
Megoldás lényege:
Minden tanulóra a jegyek darabszámából kiszámoljuk a pontszámot: az ötösök 3, a négyesek 2 pontot érnek, a kettesek -1, az elégtelenek -2 pontot, a hármas nem változtat az eredményen. A pontszámokat egy tömbben tároljuk, és közben összegezzük őket. Az átlag az összeg és a tanulók számának hányadosa, amelyet kilenc tizedesjegyre írunk ki. Az átlag feletti tanulókat úgy választjuk ki, hogy a pontszám és a tanulók száma szorzata nagyobb az összegnél: így az összehasonlítás egész számokkal, kerekítési hiba nélkül történik. A legjobb pontszám a tömb maximuma, és az azt elérő tanulók neveit a bemenet sorrendjében írjuk ki. A nevet teljes sorként olvassuk be, mert a névben szóköz is lehet. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Egy tanuló pontszámához nem kell a jegyeket külön-külön figyelni: elég a darabszámokat megszorozni a jegyek pontértékével és összeadni. A hármasnak nincs pontja. ||
Hint 2: || Az átlag feletti feltétel egész számokkal is felírható: ha a tanuló pontszáma szorozva a tanulók számával nagyobb, mint az összes pontszám, akkor az átlag felett van. Így nem kell lebegőpontos osztással dolgozni. ||
Hint 3: || A nevek szóközt is tartalmazhatnak, ezért a nevet teljes sorként, getline függvénnyel olvasd be, a jegyek sorát pedig külön. A legjobb pontszámot a maximum adja, a kiírás mindig a bemenet sorrendjét követi. ||
*/
#include <bits/stdc++.h>
using namespace std;

string sorVeg(string s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n')) s.pop_back();
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string sor;
    getline(cin, sor);
    int n = stoi(sor);

    vector<string> nevek(n);
    vector<long long> pontok(n);
    long long osszeg = 0;

    for (int i = 0; i < n; i++) {
        getline(cin, nevek[i]);
        nevek[i] = sorVeg(nevek[i]);

        getline(cin, sor);
        istringstream be(sor);
        long long otos, negyes, harmas, kettes, elegtelen;
        be >> otos >> negyes >> harmas >> kettes >> elegtelen;
        pontok[i] = 3 * otos + 2 * negyes - kettes - 2 * elegtelen;
        osszeg += pontok[i];
    }

    // 1. részfeladat: a pontszámok
    cout << "#\n";
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " ";
        cout << pontok[i];
    }
    cout << "\n";

    // 2. részfeladat: az átlag
    cout << "#\n";
    cout << fixed << setprecision(9) << (double)osszeg / n << "\n";

    // 3. részfeladat: az átlag feletti tanulók és pontszámaik
    cout << "#\n";
    for (int i = 0; i < n; i++) {
        if (pontok[i] * n > osszeg) {
            cout << nevek[i] << "\n" << pontok[i] << "\n";
        }
    }

    // 4. részfeladat: a legjobb pontszámot elérő tanulók
    cout << "#\n";
    long long legjobb = *max_element(pontok.begin(), pontok.end());
    for (int i = 0; i < n; i++) {
        if (pontok[i] == legjobb) cout << nevek[i] << "\n";
    }

    return 0;
}
