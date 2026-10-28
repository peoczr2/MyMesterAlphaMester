/*
Megoldás lényege:
Szempontonként megszámoljuk a kieső kutyákat (P < Min), majd azokat a szempontokat gyűjtjük ki, ahol a kiesők száma nagyobb, mint a résztvevők fele. A „több mint fele” feltételt egész számokkal írjuk fel: 2·db > N, így nincs törtes szám és kerekítési hiba. A kiírásban először a darabszám áll, utána a sorszámok növekvő sorrendben, mert a szempontok balról jobbra haladnak. Az idő O(N·M), ami legfeljebb 10^4 lépés.
*/
/*
Hint 1: || „Több mint fele” azt jelenti, hogy a kiesők száma nagyobb, mint N/2. Egész számokkal ezt szorzással írd fel, hogy ne legyen törtes szám. ||
Hint 2: || Először szempontonként számold meg a kiesőket egy tömbbe, majd a feltételnek megfelelő sorszámokat gyűjtsd egy vektorba, és először a vektor méretét írd ki. ||
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

    // azok a szempontok, ahol a kiesők száma nagyobb, mint a résztvevők fele
    vector<int> valasz;
    for (int j = 0; j < m; j++) {
        if (2 * kiesett[j] > n) valasz.push_back(j + 1);
    }

    cout << valasz.size();
    for (int x : valasz) cout << " " << x;
    cout << "\n";
    return 0;
}
