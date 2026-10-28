/*
Megoldás lényege: minden háborúban két törzs vesz részt, ezért egy logikai tömbben megjelöljük mindkét résztvevőt. Az évszámok a feladathoz nem kellenek, csak a sorszámok számítanak. A végén a meg nem jelölt törzsek száma adja a békés törzsek darabszámát, sorszámaikat 1-től N-ig bejárva növekvő sorrendben írjuk ki. Az időigény O(N + K), ami a korlátok mellett azonnali.
*/
/*
Hint 1: || Egy törzs akkor békés, ha egyetlen háborúban sem szerepel, sem háborúzóként, sem ellenségként. Az évszámokra ehhez nincs szükség, elég a sorszámokat figyelni. ||
Hint 2: || Készíts N+1 elemű logikai tömböt, és minden háború sorában jelöld meg a két sorszámot. A végén az 1-től N-ig tartó sorszámok közül azokat írd ki, amelyek nincsenek megjelölve. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<bool> harcolt(n + 1, false);
    for (int i = 0; i < k; i++) {
        int haboruzo, ellenseges;
        int kezdet, vege;
        cin >> haboruzo >> ellenseges >> kezdet >> vege;
        harcolt[haboruzo] = true;
        harcolt[ellenseges] = true;
    }

    vector<int> bekes;
    for (int i = 1; i <= n; i++)
        if (!harcolt[i])
            bekes.push_back(i);

    cout << bekes.size() << "\n";
    for (size_t i = 0; i < bekes.size(); i++) {
        if (i > 0)
            cout << ' ';
        cout << bekes[i];
    }
    cout << "\n";
    return 0;
}
