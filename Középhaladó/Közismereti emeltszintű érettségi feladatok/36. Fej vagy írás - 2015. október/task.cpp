/*
Megoldás lényege:
Az összes dobást egyszer végigolvassuk, a fejek számából kiszámoljuk a relatív gyakoriságot.
A fejfutamokat (egymás után álló F betűket) egy bejárással gyűjtjük ki: minden futamnak ismerjük
a hosszát és az első elemének helyét, így a 2. és a 3. részfeladat ebből egyszerűen adódik.
A 4. részfeladatban minden olyan pozícióra, ahol három egymás utáni F áll, megnézzük a negyedik dobást.
Az időigény O(N), ami N <= 1000 esetén bőven belefér az időlimitbe.
*/
/*
Hint 1: || Egyetlen végigolvasással megkapod a fejek számát az 1. részfeladathoz. A futamokat úgy keresd, hogy megjegyzed, hol kezdődik és hol ér véget egy egybefüggő F-szakasz. ||
Hint 2: || Egy futam hossza a vége és az eleje közti különbség. A 2. részfeladatban a pontosan kettő hosszú futamokat számold, a 3.-ban a leghosszabb első előfordulását keresd (1-től indexelve). ||
Hint 3: || A 4. részfeladatnál minden i pozícióra nézd meg, hogy az i, i+1, i+2 karakter F-e, és az i+3. karakter F vagy I. Az átfedő ablakok is külön esetnek számítanak. A kerekítéshez egész számolás is elég: (200*F + N) / (2*N). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    int len = s.size();

    // 1. részfeladat: a fejek relatív gyakorisága százalékban, egészre kerekítve
    int fejek = count(s.begin(), s.end(), 'F');
    long long szazalek = (200LL * fejek + len) / (2LL * len);
    cout << "#\n" << szazalek << "\n";

    // Fejfutamok: (kezdőindex 0-tól, hossz)
    vector<pair<int, int>> futamok;
    for (int i = 0; i < len;) {
        if (s[i] != 'F') {
            i++;
            continue;
        }
        int j = i;
        while (j < len && s[j] == 'F') j++;
        futamok.push_back({i, j - i});
        i = j;
    }

    // 2. részfeladat: pontosan kettő hosszú fejsorozatok száma
    int pontosanKet = 0;
    for (const auto& f : futamok)
        if (f.second == 2) pontosanKet++;
    cout << "#\n" << pontosanKet << "\n";

    // 3. részfeladat: a leghosszabb fejsorozat hossza és első elemének helye (1-től)
    int leghosszabb = 0, hely = -1;
    for (const auto& f : futamok) {
        if (f.second > leghosszabb) {
            leghosszabb = f.second;
            hely = f.first + 1;
        }
    }
    cout << "#\n" << leghosszabb << " " << hely << "\n";

    // 4. részfeladat: háromtagú fejsorozatot követő fej, illetve írás
    int utanFej = 0, utanIras = 0;
    for (int i = 0; i + 3 < len; i++) {
        if (s[i] == 'F' && s[i + 1] == 'F' && s[i + 2] == 'F') {
            if (s[i + 3] == 'F') utanFej++;
            else utanIras++;
        }
    }
    cout << "#\n" << utanFej << " " << utanIras << "\n";
    return 0;
}
