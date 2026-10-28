/*
Megoldás lényege:
Azt keressük, hogy melyik az utolsó állomás, ahol nem volt leszálló, vagyis ahol a leszállók száma nulla.
Az állomásokat sorban beolvassuk, és minden ilyen állomás sorszámát megjegyezzük, így a végén az utolsó találat marad meg.
A felszállók száma ehhez nem számít, és az első állomáson biztosan nincs leszálló, így van találat.
Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Csak a leszállók száma számít: keresd azokat az állomásokat, ahol ez nulla. A felszállókkal nem kell foglalkozni. ||
Hint 2: || Ne az első ilyen állomást tartsd meg, hanem minden találatnál írd felül a sorszámot. Így a végén az utolsó találat marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    int answer = -1;  // az utolsó állomás sorszáma, ahol nem volt leszálló
    for (int i = 1; i <= n; i++) {
        int le, fel;
        cin >> le >> fel;
        if (le == 0) answer = i;  // minden találatnál felülírjuk, így az utolsó marad
    }

    cout << answer << "\n";
    return 0;
}
