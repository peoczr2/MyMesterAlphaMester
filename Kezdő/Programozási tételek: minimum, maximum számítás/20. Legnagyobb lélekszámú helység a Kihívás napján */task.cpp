/*
Megoldás lényege:
Maximumkiválasztás egy menetben: a nevezéseket sorban olvassuk, és nyilvántartjuk az eddigi legnagyobb lélekszámot, annak sorszámát és a hozzá tartozó résztvevők számát. Csak szigorúan nagyobb lélekszám esetén frissítünk, így holtverseny esetén a korábbi (kisebb sorszámú) helység marad. A helységneveket beolvassuk, de nem tároljuk, mert a válaszhoz nem kellenek. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell az összes nevezést tárolni: egyetlen bejárás elég, ha közben a jelenlegi maximumot és annak sorszámát megjegyzed. ||
Hint 2: || A helységnév szóközt is tartalmazhat, ezért sorként (getline) olvasd be, majd a lélekszámot és a résztvevők számát ugyanabban a körben olvasd ki. A maximumot csak szigorúan nagyobb lélekszámnál írd felül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int bestIdx = 0;
    int bestPop = -1;
    int bestPart = 0;
    for (int i = 1; i <= n; i++) {
        string name;
        int pop, part;
        cin >> ws;
        getline(cin, name);
        cin >> pop >> part;
        if (pop > bestPop) {
            bestPop = pop;
            bestIdx = i;
            bestPart = part;
        }
    }

    cout << bestIdx << " " << bestPart << "\n";
    return 0;
}
