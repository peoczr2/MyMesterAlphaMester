/*
Megoldás lényege:
Azt keressük, hogy melyik az első olyan állomás, ahol nem volt felszálló, vagyis ahol a felszállók száma nulla.
Az állomásokat sorban beolvassuk, és az első ilyen állomás sorszámát megjegyezzük; a későbbi találatok már nem számítanak.
A leszállók száma ehhez nem kell, és az utolsó állomáson biztosan nincs felszálló, így a válasz mindig létezik.
Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Csak a felszállók száma számít: keresd az első állomást, ahol ez nulla. A leszállók számával nem kell foglalkozni. ||
Hint 2: || Minden állomást beolvashatsz sorban, de csak az első találatot tartsd meg. A később talált nullás állomás ne írja felül az eredményt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int answer = -1;  // az első állomás sorszáma, ahol nem volt felszálló
    for (int i = 1; i <= n; i++) {
        int le, fel;
        cin >> le >> fel;
        if (answer == -1 && fel == 0) answer = i;
    }

    cout << answer << "\n";
    return 0;
}
