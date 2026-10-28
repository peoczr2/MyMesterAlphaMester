/*
Megoldás lényege:
Minden számjegy morzekódja pontosan 5 jelből áll, ezért a bemenetet 5 karakteres blokkokra bontjuk.
Minden blokkot összevetünk a tíz számjegy kódjával, és a megegyező kódú számjegyet kiírjuk a helyes sorrendben.
Az időigény O(n), ahol n legfeljebb 1000, így az időkorlát bőven teljesíthető.
*/
/*
Hint 1: || Hány jelből áll egy számjegy morzekódja? Ha ezt tudod, a bemenetet fix méretű darabokra vághatod. ||
Hint 2: || Készíts egy tömböt a tíz számjegy kódjából, ahol az index maga a számjegy, és minden 5 karakteres darabot hasonlíts össze ezekkel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    const string kod[10] = {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};
    string s;
    cin >> s;
    for (size_t i = 0; i + 5 <= s.size(); i += 5) {
        string blokk = s.substr(i, 5);
        for (int d = 0; d < 10; d++) {
            if (kod[d] == blokk) {
                cout << d;
                break;
            }
        }
    }
    cout << "\n";
    return 0;
}
