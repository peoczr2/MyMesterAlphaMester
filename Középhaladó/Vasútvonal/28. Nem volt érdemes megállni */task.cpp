/*
Megoldás lényege:
Egy állomáson nem érte meg megállni a vonatnak, ha ott sem leszálló, sem felszálló nem volt, vagyis mindkét szám nulla.
Az első és az utolsó állomáson a vonat mindenképpen megáll, ezért ezeket nem vizsgáljuk.
Az állomásokat sorban beolvassuk, és a köztes állomások közül az első olyan sorszámát megjegyezzük, ahol le és fel is nulla.
Ha nincs ilyen állomás, a válasz -1.
Az időigény O(N), a memóriaigény O(1), mert csak egy sorszámot tárolunk.
*/
/*
Hint 1: || Egyetlen végigmenés elég: minden állomásnál csak azt kell megnézni, hogy a leszállók és a felszállók száma is nulla-e. ||
Hint 2: || Az első és az utolsó állomást ne vedd figyelembe, mert ott a vonat mindenképpen megáll. Az első találatot tartsd meg, a későbbieket már ne írd felül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int answer = -1;  // az első olyan köztes állomás sorszáma, ahol nem volt le- és felszálló
    for (int i = 1; i <= n; i++) {
        int le, fel;
        cin >> le >> fel;
        bool middle = (i > 1 && i < n);  // a kezdő és a végállomáson mindenképpen megáll a vonat
        if (answer == -1 && middle && le == 0 && fel == 0) answer = i;
    }

    cout << answer << "\n";
    return 0;
}
