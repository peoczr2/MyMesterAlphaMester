/*
Megoldás lényege: minden háborúban két törzs vesz részt, ezért egy logikai tömbben megjelöljük mindkét résztvevőt. Egy törzs akkor nem békés, ha legalább egy háborúban szerepel, akár támadóként, akár ellenségként, ehhez az évszámok nem kellenek. Először megszámoljuk a megjelölt törzseket, majd a sorszámaikat 1-től N-ig bejárva növekvő sorrendben írjuk ki. Az időigény O(N + K), ami a korlátok mellett azonnali.
*/
/*
Hint 1: || Egy törzs nem békés, ha legalább egy háborúban részt vesz, akár háborúzó, akár ellenséges félként. A keresés nem függ az évszámoktól, csak a sorszámoktól. ||
Hint 2: || Készíts N+1 elemű logikai tömböt, és minden háború mindkét résztvevőjét jelöld meg benne. A kiíráshoz előbb számold meg a megjelölteket, majd az 1-től N-ig tartó sorszámokat növekvő sorrendben írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<bool> resztvevo(n + 1, false);
    for (int i = 0; i < k; i++) {
        int haboruzo, ellenseges;
        int kezdet, vege;
        cin >> haboruzo >> ellenseges >> kezdet >> vege;
        resztvevo[haboruzo] = true;
        resztvevo[ellenseges] = true;
    }

    vector<int> nembekes;
    for (int i = 1; i <= n; i++)
        if (resztvevo[i])
            nembekes.push_back(i);

    cout << nembekes.size() << "\n";
    for (size_t i = 0; i < nembekes.size(); i++) {
        if (i > 0)
            cout << ' ';
        cout << nembekes[i];
    }
    cout << "\n";
    return 0;
}
