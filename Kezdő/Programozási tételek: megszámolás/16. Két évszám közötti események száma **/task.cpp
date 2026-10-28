/*
Megoldás lényege:
Az eseményeket egyenként olvassuk be: évszám, kategória, majd az esemény neve külön sorban. A név szóközöket is tartalmazhat, ezért sorként olvassuk be, és a kategória után a sor végéig is átugorjuk.
Az évszámokat eltároljuk, majd a két határoló év beolvasása után megszámoljuk azokat, amelyek a zárt [Év1, Év2] intervallumba esnek.
A kategórianevek a számláláshoz nem kellenek, ezeket nem olvassuk be. Az időigény O(N).
*/
/*
Hint 1: || Az esemény neve szóközöket is tartalmazhat, ezért ne tokenenként olvasd, hanem a sort egészben (getline). ||
Hint 2: || Az évszámokat tárold el egy tömbben, majd a határoló évek beolvasása után számold meg, hány évszám esik a két határ közé, a határokat is beleértve. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, ksz;
    cin >> n >> ksz;
    vector<int> evek(n);
    for (int i = 0; i < n; i++) {
        int kategoria;
        string nev;
        cin >> evek[i] >> kategoria >> ws;
        getline(cin, nev);
    }
    int ev1, ev2;
    cin >> ev1 >> ev2;
    int db = 0;
    for (int i = 0; i < n; i++) {
        if (evek[i] >= ev1 && evek[i] <= ev2) {
            db++;
        }
    }
    cout << db << endl;
    return 0;
}
