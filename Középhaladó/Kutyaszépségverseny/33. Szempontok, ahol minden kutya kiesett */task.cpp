/*
Megoldás lényege:
Szempontonként megszámoljuk a kieső kutyákat (P < Min). Egy szempontot akkor veszünk fel a válaszba, ha a kiesők száma pontosan N, vagyis minden kutya kiesett belőle. A kiírásban először a darabszám áll, utána a sorszámok növekvő sorrendben, mert a szempontok balról jobbra haladnak. Az idő O(N·M), ami legfeljebb 10^4 lépés.
*/
/*
Hint 1: || Egy szempontban akkor esett ki minden kutya, ha a kiesők száma megegyezik a résztvevők számával. ||
Hint 2: || Szempontonként számold a kieséseket egy tömbben, majd a feltételnek eleget tévő sorszámokat gyűjtsd egy vektorba, és először a darabszámot írd ki. ||
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

    // azok a szempontok, ahol minden kutya kiesett
    vector<int> valasz;
    for (int j = 0; j < m; j++) {
        if (kiesett[j] == n) valasz.push_back(j + 1);
    }

    cout << valasz.size();
    for (int x : valasz) cout << " " << x;
    cout << "\n";
    return 0;
}
