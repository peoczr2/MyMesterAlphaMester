/*
Megoldás lényege:
A kifejezés lineáris, ezért elég minden betű (a, b, c, d) együtthatóját külön összegezni. Egy betű előjele
a közvetlenül előtte álló előjelektől (akár több is állhat egymás után) és az őt körülvevő zárójelektől függ.
A zárójelszintek előjel-szorzóit egy veremben tároljuk: nyitó zárójelnél a szorzót betesszük, záró zárójelnél
kivesszük. Az előjeleket szorozzuk, betűnél pedig a verem tetejével szorzott előjelet adjuk az együtthatóhoz.
A karaktereket balról jobbra egyszer dolgozzuk fel, így az időigény O(N), ahol N a kifejezés hossza.
*/
/*
Hint 1: || A kifejezés lineáris, ezért elég minden betű együtthatóját külön összegezni, a végén négy számot kell kiírni. ||
Hint 2: || Egy tag előjele a közvetlenül előtte álló előjelektől és az összes körülötte lévő zárójel előjelétől függ. Zárójelszintenként tárold az előjel-szorzót egy veremben. ||
Hint 3: || A műveleti jel és az előjel is a következő tag előjelét módosítja: a - megfordítja, a + nem változtat rajta. Betűnél szorozd ezt az előjelet a verem tetejével, add az együtthatóhoz, majd állítsd vissza 1-re. ||
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
    int pending = 1;                  // a következő tag előjele a műveleti jelek és előjelek alapján

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
