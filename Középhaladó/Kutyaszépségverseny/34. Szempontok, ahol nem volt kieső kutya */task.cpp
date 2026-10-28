/*
Megoldás lényege:
Szempontonként megszámoljuk a kieső kutyákat (P < Min). Az a szempont kerül a válaszba, ahol ez a szám nulla, vagyis minden kutya eléri az adott szempont alsó ponthatárát. A kiírásban először a darabszám áll, utána a sorszámok növekvő sorrendben, mert a szempontok balról jobbra haladnak. Az idő O(N·M), ami legfeljebb 10^4 lépés.
*/
/*
Hint 1: || Egy szempontban akkor nincs kieső kutya, ha egyetlen pontszám sem esik az alsó határ alá. Ezt elég szempontonként ellenőrizni. ||
Hint 2: || Szempontonként számold a kieséseket egy tömbben, majd a nulla értékű szempontok sorszámait gyűjtsd egy vektorba, és először a darabszámot írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // a maximális pontokra a számításhoz nincs szükség, csak beolvassuk őket
    vector<int> maxPont(m);
    for (int j = 0; j < m; j++) cin >> maxPont[j];

    vector<int> alsoHatar(m);
    for (int j = 0; j < m; j++) cin >> alsoHatar[j];

    // kiesett[j]: hány kutya esett ki a j. szempontból
    vector<int> kiesett(m, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int p;
            cin >> p;
            if (p < alsoHatar[j]) kiesett[j]++;
        }
    }

    // azok a szempontok, ahol nem volt kieső kutya
    vector<int> valasz;
    for (int j = 0; j < m; j++) {
        if (kiesett[j] == 0) valasz.push_back(j + 1);
    }

    cout << valasz.size();
    for (int x : valasz) cout << " " << x;
    cout << "\n";
    return 0;
}
