/*
Megoldás lényege:
A két kettes számrendszerbeli számot úgy adjuk össze, ahogy papíron szoktuk: a jobb szélső számjegytől haladunk balra, és minden helyiértéken összeadjuk a két számjegyet az esetleges átvitellel együtt. Mivel a számjegyek csak 0 vagy 1 lehetnek, az adott helyiérték eredménye az összeg páros/páratlan volta alapján adódik, az átvitel pedig az összeg kettes osztásának egész része. A számok hossza legfeljebb 1000 karakter, ezért nem alakítjuk őket számmá, hanem karaktersorozatként kezeljük. Az eredmény számjegyeit fordított sorrendben kapjuk, ezért a végén visszafordítjuk őket. Mivel mindkét szám 1-essel kezdődik, az eredmény is 1-essel kezdődik. Az időigény O(L), ahol L a számjegyek maximális száma.
*/
/*
Hint 1: || Az összeadást pontosan úgy végezd, ahogy papíron: a legkisebb helyiértéktől, vagyis a jobb szélétől indulj, és az átvitelt mindig vidd tovább a következő helyiértékre. ||
Hint 2: || Ne alakítsd számmá a bemenetet, mert hosszú is lehet, hanem karakterekként dolgozz. Az indexeket a két szám végéről indítsd, és ha valamelyik szám már elfogyott, ott 0-nak vedd a számjegyet. Az eredményt fordítva kapod, ezért írd ki visszafelé. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;

    string eredmeny;
    int atvitel = 0;
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;

    while (i >= 0 || j >= 0 || atvitel) {
        int s = atvitel;
        if (i >= 0) {
            s += a[i] - '0';
            i--;
        }
        if (j >= 0) {
            s += b[j] - '0';
            j--;
        }
        eredmeny.push_back(char('0' + s % 2));
        atvitel = s / 2;
    }

    reverse(eredmeny.begin(), eredmeny.end());
    cout << eredmeny << "\n";

    return 0;
}
