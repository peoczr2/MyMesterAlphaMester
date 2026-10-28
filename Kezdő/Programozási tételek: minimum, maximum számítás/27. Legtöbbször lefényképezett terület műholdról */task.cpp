/*
Megoldás lényege:
Azt a pontot keressük, amelyet a legtöbb fénykép lefed, a téglalapok széle is hozzátartozik. Egy 2D különbségi tömbben (imos-módszer) minden téglalaphoz négy sarkánál végzünk módosítást, majd a tömböt előbb sorok, utána oszlopok mentén összegezzük, így minden egész koordinátájú pont fedettsége megkapható. A válasz ezeknek az értékeknek a maximuma. A koordináták legfeljebb 1000-esek, ezért az időigény O(N + C^2), ahol C = 1000, a memóriaigény O(C^2).
*/
/*
Hint 1: || Nem kell a képeket páronként összehasonlítani: keress egy olyan egész koordinátájú pontot, amelyet a legtöbb téglalap lefed. ||
Hint 2: || Egy téglalaphoz a bal felső sarkánál +1, a jobb oldali és az alsó oldali szomszédos sarkoknál −1, a jobb alsó sarok mögötti pontnál ismét +1 kerül egy különbségi tömbbe. ||
Hint 3: || Az összegzés után minden pontra megkapod a fedettséget, a válasz a tömb maximuma. A jobb alsó sarok indexe legfeljebb 1001 lehet, ezért a tömb mérete legyen 1003. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXC = 1001;
int cover[MAXC + 2][MAXC + 2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int bfx, bfy, jax, jay;
        cin >> bfx >> bfy >> jax >> jay;
        // a jobb alsó sarok is a téglalap része, ezért a lezáró módosítás egy egységgel odébb kerül
        cover[bfx][bfy] += 1;
        cover[jax + 1][bfy] -= 1;
        cover[bfx][jay + 1] -= 1;
        cover[jax + 1][jay + 1] += 1;
    }

    for (int x = 1; x <= MAXC; x++)
        for (int y = 0; y <= MAXC; y++)
            cover[x][y] += cover[x - 1][y];
    for (int x = 0; x <= MAXC; x++)
        for (int y = 1; y <= MAXC; y++)
            cover[x][y] += cover[x][y - 1];

    int best = 0;
    for (int x = 0; x <= 1000; x++)
        for (int y = 0; y <= 1000; y++)
            best = max(best, cover[x][y]);

    cout << best << "\n";
    return 0;
}
