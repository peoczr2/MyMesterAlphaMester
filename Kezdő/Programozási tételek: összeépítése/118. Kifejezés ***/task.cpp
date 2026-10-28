/*
Megoldás lényege:
A kifejezés lineáris, ezért elég minden betű (a, b, c, d) együtthatóját külön összegezni. Egy betű előjele
a előtte álló műveleti jelektől és az őt körülvevő zárójelektől függ. A zárójelszintek előjel-szorzóit egy
veremben tároljuk: nyitó zárójelnél a szorzót betesszük, záró zárójelnél kivesszük. A karaktereket balról
jobbra egyszer dolgozzuk fel, így az időigény O(N), ahol N a kifejezés hossza.
*/
/*
Hint 1: || A kifejezés lineáris, ezért elég minden betű együtthatóját külön összegezni, a végén négy számot kell kiírni. ||
Hint 2: || Egy zárójel előtti - jel az egész zárójeles részt megfordítja. Zárójelszintenként érdemes tárolni az előjel-szorzót, és ezt egy veremben kezelni. ||
Hint 3: || Balról jobbra haladva: a - jel megfordítja a következő tag előjelét, nyitó zárójelnél tedd az aktuális előjelet a verembe, záró zárójelnél vedd ki, betűnél pedig add hozzá a verem tetejével szorzott előjelet a betű együtthatójához. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; // a karakterek száma, a kifejezést a végéig olvassuk
    cin >> n;

    long long coef[4] = {0, 0, 0, 0}; // a, b, c, d együtthatói
    vector<int> signStack = {1};      // zárójelszintenkénti előjel-szorzó
    int pending = 1;                  // a következő tag előjele a műveleti jelek alapján

    char c;
    while (cin >> c) { // a whitespace-eket a cin átugorja
        if (c == '-') {
            pending = -pending;
        } else if (c == '(') {
            signStack.push_back(pending * signStack.back());
            pending = 1;
        } else if (c == ')') {
            signStack.pop_back();
        } else if (c >= 'a' && c <= 'd') {
            coef[c - 'a'] += pending * signStack.back();
            pending = 1;
        }
        // '+' nem változtat az előjelen
    }

    for (int k = 0; k < 4; k++)
        cout << coef[k] << (k < 3 ? ' ' : '\n');
    return 0;
}
