/*
Megoldás lényege:
A háborúkat kezdő év szerint rendezzük, majd egy menetben haladunk végig rajtuk, és közben nyilvántartjuk az eddig látott legkésőbbi befejezési évet.
Ha a következő háború később kezdődik, mint ez az év, a köztes időszak béke, hossza a kezdő év és a legkésőbbi befejezés különbsége.
Ezek közül a legrövidebb pozitív hosszúságút tartjuk meg; egyenlőségnél a korábbi marad, mert csak szigorúan rövidebbel frissítünk.
Ha nincs ilyen szakasz, a válasz 0 0. Az idő O(K log K) a rendezés miatt, a memória O(K).
*/
/*
Hint 1: || Béke csak két háború között lehet, ezért a háborúkat kezdő év szerint rendezve egymás utáni párokat kell nézned. ||
Hint 2: || Ne a következő háború befejezését tartsd nyilván, hanem az eddigi háborúk közül a legkésőbbi befejezési évet: átfedő háborúknál ez a fontos. ||
Hint 3: || Ha a következő háború kezdete nagyobb ennél az évnél, a különbség a béke hossza. A legrövidebb pozitív különbséget keresd, és egyenlőségnél a korábbi szakaszt tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<array<int, 4>> wars(k); // támadó, védő, kezdet, befejezés
    for (auto &w : wars) cin >> w[0] >> w[1] >> w[2] >> w[3];

    if (k < 2) {
        cout << "0 0\n";
        return 0;
    }

    sort(wars.begin(), wars.end(), [](const array<int, 4> &a, const array<int, 4> &b) {
        return a[2] < b[2];
    });

    bool found = false;
    int bestLen = 0, bestFrom = 0, bestTo = 0;
    int lastEnd = wars[0][3];
    for (int i = 1; i < k; i++) {
        int gap = wars[i][2] - lastEnd;
        if (gap > 0 && (!found || gap < bestLen)) {
            found = true;
            bestLen = gap;
            bestFrom = lastEnd;
            bestTo = wars[i][2];
        }
        lastEnd = max(lastEnd, wars[i][3]);
    }

    if (found) cout << bestFrom << " " << bestTo << "\n";
    else cout << "0 0\n";
    return 0;
}
