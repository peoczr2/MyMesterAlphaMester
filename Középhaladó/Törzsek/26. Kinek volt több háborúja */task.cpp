/*
Megoldás lényege:
Minden törzsnek megszámoljuk a háborúit: egy háború a törzsnek számít, ha a sorszáma a háborúzó vagy az ellenséges oszlopban szerepel. Végül a két kérdezett törzs számlálóját hasonlítjuk össze: nagyobb számnál az A vagy a B betű, egyenlőnél az „ugyanannyi” szó kerül a kimenetre. Egyetlen beolvasás és egy összehasonlítás, az időigény O(K).
*/
/*
Hint 1: || Nem kell a háborúkat listázni: elég minden sor beolvasása után mindkét törzs számlálóját eggyel növelni. ||
Hint 2: || A számlálókat tömbben tárold, ahol az index a törzs sorszáma. Az utolsó sor két törzsének számlálóját hasonlítsd össze, és ennek megfelelően írd ki az A, a B vagy az „ugyanannyi” szót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> haboruk(n + 1, 0);
    for (int i = 0; i < k; ++i) {
        int a, b, s, e;
        cin >> a >> b >> s >> e;
        ++haboruk[a];
        ++haboruk[b];
    }
    int a, b;
    cin >> a >> b;

    if (haboruk[a] > haboruk[b])
        cout << "A\n";
    else if (haboruk[b] > haboruk[a])
        cout << "B\n";
    else
        cout << "ugyanannyi\n";
    return 0;
}
