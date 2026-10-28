/*
Megoldás lényege:
Az utat 1 kilométeres darabokra bontjuk, és egy N elemű logikai tömbben jelöljük azokat a kilométereket, amelyeket legalább egy felújítás lefed. Minden felújításnál a K és a V-1 index közötti elemeket (mindkettőt beleértve) igazra állítjuk; az átfedések ilyenkor magától helyesen kezelődnek. Végül a nem jelölt kilométereket számoljuk meg. Az időigény legrosszabb esetben O(M*N), ami kb. 10^6 művelet, a memóriaigény O(N).
*/
/*
Hint 1: || Érdemes kilométerenként vizsgálni az utat: a 0-tól N-1-ig számozott kilométer-szakaszok közül kell megszámolni azokat, amelyeket egyetlen felújítás sem fed le. ||
Hint 2: || Tárolj egy N hosszú logikai tömböt. Minden felújításnál a K. és a V-1. index közötti elemeket (mindkettőt beleértve) állítsd igazra, majd számold meg a hamis elemeket. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<bool> felujitott(n, false);
    for (int i = 0; i < m; i++) {
        int k, v;
        cin >> k >> v;
        for (int km = k; km < v; km++) felujitott[km] = true;
    }
    int hiany = 0;
    for (int km = 0; km < n; km++)
        if (!felujitott[km]) hiany++;
    cout << hiany << "\n";
    return 0;
}
