/*
Megoldás lényege:
Két szomszédos nap változását a két keresztkombináció nagyobbik abszolút különbsége adja: az első nap maximuma és a második nap minimuma különbsége, illetve a második nap maximuma és az első nap minimuma különbsége. Ezt a két értéket összevetve kapjuk a párra jellemző változást. Mivel a két keresztkülönbség összege mindig a két nap hőmérsékletsávjainak összege, nem nulla, így a nagyobb abszolút érték egyben a nagyobb előjeles érték is. A napokon egy menetben haladunk az (i, i+1) párokon, és csak szigorúan nagyobb változásnál frissítünk, így holtverseny esetén az első pár marad. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Két szomszédos nap változását két keresztkülönbség adja: az egyik nap maximuma és a másik nap minimuma közötti eltérés. Mindkét irányt érdemes megnézni. ||
Hint 2: || Egy menetben járd be a szomszédos párokat, és csak az előző nap minimumát és maximumát tartsd meg; a párhoz tartozó változásnál a pár első napjának sorszámát jegyezd fel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int prevMin, prevMax;
    cin >> prevMin >> prevMax;

    int bestChange = -1;
    int bestFirst = 1;
    for (int day = 2; day <= n; day++) {
        int mn, mx;
        cin >> mn >> mx;
        int change = max(abs(prevMax - mn), abs(mx - prevMin));
        if (change > bestChange) {
            bestChange = change;
            bestFirst = day - 1;
        }
        prevMin = mn;
        prevMax = mx;
    }

    cout << bestFirst << " " << bestFirst + 1 << "\n";
    return 0;
}
