/*
Megoldás lényege:
A napokat sorban, egyesével olvassuk be. Egy sor egy vagy több nevet tartalmazhat, vesszővel elválasztva, ezért a sort
egészben olvassuk, majd vesszőnként szétbontjuk. A neveket levágjuk a szóközöktől és a sor végi sortörés-karakterektől.
Ha valamelyik név egyezik a keresettel, a nap sorszámát (1-től indulva) egy vektorba tesszük. Egy napot csak egyszer
jegyzünk fel, akkor is, ha a keresett név ugyanazon a napon többször szerepelne. A sorszámok a sorban olvasás miatt
növekvő sorrendben kerülnek a vektorba, így külön rendezésre nincs szükség. A végén kiírjuk a darabszámot, majd a sorszámokat.
Az időigény O(N·k), ahol k egy napon szereplő nevek száma (legfeljebb 5), ami a korlátok mellett triviális.
*/
/*
Hint 1: || Egy sorban több név is lehet, ezért a sort ne szavanként, hanem egészben olvasd be, és vesszőnként válaszd szét. ||
Hint 2: || Egy napot akkor kell kiírni, ha a sorában szereplő nevek között ott van a keresett név. A napok sorszámát a beolvasás sorrendjéből kapod, és minden napot legfeljebb egyszer számolj be. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Levágja a szóközöket és a sor végi sortörés-karaktereket a szöveg elejéről és végéről.
string trim(const string& s) {
    const char* szokoz = " \t\r\n";
    size_t eleje = s.find_first_not_of(szokoz);
    if (eleje == string::npos) return "";
    size_t vege = s.find_last_not_of(szokoz);
    return s.substr(eleje, vege - eleje + 1);
}

int main() {
    int n;
    string keresett;
    cin >> n >> keresett;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> napok;
    for (int i = 1; i <= n; ++i) {
        string sor;
        getline(cin, sor);

        bool unnep = false;
        stringstream ss(sor);
        string nev;
        while (getline(ss, nev, ',')) {
            if (trim(nev) == keresett) unnep = true;
        }
        if (unnep) napok.push_back(i);
    }

    cout << napok.size();
    for (int nap : napok) cout << ' ' << nap;
    cout << '\n';
    return 0;
}
