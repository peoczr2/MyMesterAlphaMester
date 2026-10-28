/*
Megoldás lényege:
Budapesttől a k-adik állomásig a vonat útja k − 1 szakaszból áll, így az út kiadása V · (k − 1). Az utasok bevétele ugyanezen az úton az egyes szakaszokon U · utasszám, ezeket összeadva kapjuk az eddigi bevételt.
A feladat szerint az út közben sem lehet veszteséges, ezért minden állomásnál ellenőrizzük, hogy az eddigi összes bevétel legalább akkora-e, mint az eddigi kiadás. A bejárást futó összegekkel, egy menetben végezzük.
Az első olyan állomásnál, ahol a bevétel kisebb a kiadásnál, az előző állomás sorszámát írjuk ki. Ha minden állomásnál teljesül a feltétel, az utolsó állomás a válasz. Az időigény O(N), N ≤ 1000 mellett gyors.
*/
/*
Hint 1: || Az út k-adik állomásig akkor gazdaságos, ha az addig befolyt összes bevétel legalább annyi, mint a k − 1 szakasz összes kiadása. ||
Hint 2: || Egy ciklusban olvasd be az állomásokat, az i-edik szakasz bevételét U · utasszám formában add az eddigi bevételhez, és ha a bevétel kisebb V · i-nél, akkor az (i+1)-edik állomásig tartó út veszteséges, így az i a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long u, v;
    cin >> n >> u >> v;
    long long utasok = 0;
    long long bevetel = 0;
    int valasz = n;
    for (int i = 1; i <= n; i++) {
        long long le, fel;
        cin >> le >> fel;
        utasok += fel - le;
        if (i < n) {
            bevetel += u * utasok;
            if (bevetel < v * i) {
                valasz = i;
                break;
            }
        }
    }
    cout << valasz << endl;
    return 0;
}
