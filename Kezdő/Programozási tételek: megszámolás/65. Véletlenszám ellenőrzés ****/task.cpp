/*
Megoldás lényege:
Két egymást követő Ai-előfordulás között nincs másik Ai, ezért elég ezeket a szomszédos párokat végignézni, és mindegyikben megszámolni a Bi értékeket. Mivel M legfeljebb 100, minden érték előfordulásait prefixösszeggel tároljuk: elo[b][i] megmutatja, hány b van az 1..i pozíciókon, így egy szakaszban a b-k száma két kivonással adódik. Minden (a, b) párra tároljuk a szomszédos a-párok közül a legnagyobb b-számot; ha az a értékből nincs két előfordulás, a válasz −1 marad. Az előkészítés O(N·M), a kérdések O(1) időben megválaszolhatók; a memóriaigény O(N·M).
*/
/*
Hint 1: || Egy kérdésre a sorozatban az Ai-előfordulásokat kell sorra venni, és minden szomszédos párra meg kell számolni a közöttük lévő Bi-k számát. Ha Ai-ból legfeljebb egy van, a válasz −1. ||
Hint 2: || A kérdések száma akár 10 000 is lehet, ezért ne minden kérdésnél járd be a teljes sorozatot. Mivel az értékek 1 és M között vannak, és M legfeljebb 100, minden értékhez tárolj prefixösszeg-tömböt az előfordulásokról. ||
Hint 3: || Készíts egy M×M-es táblázatot: az (a, b) helyen legyen a szomszédos a-párok közötti b-k maximuma. Minden szomszédos a-párra és minden b értékre egy kivonással megkapod a db számát, és a táblázatot ennek maximumával frissíted. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> seq(n + 1);
    vector<vector<int>> hely(m + 1);  // hely[a]: az a érték pozíciói növekvő sorrendben
    for (int i = 1; i <= n; i++) {
        cin >> seq[i];
        hely[seq[i]].push_back(i);
    }

    // elo[b][i]: hányszor fordul elő b az 1..i pozíciókon
    vector<vector<int>> elo(m + 1, vector<int>(n + 1, 0));
    for (int b = 1; b <= m; b++)
        for (int i = 1; i <= n; i++)
            elo[b][i] = elo[b][i - 1] + (seq[i] == b ? 1 : 0);

    // valasz[a][b]: a szomszédos a-előfordulások közötti b-k maximuma, −1 ha nincs két a
    vector<vector<int>> valasz(m + 1, vector<int>(m + 1, -1));
    for (int a = 1; a <= m; a++) {
        for (size_t j = 0; j + 1 < hely[a].size(); j++) {
            int bal = hely[a][j];
            int jobb = hely[a][j + 1];
            for (int b = 1; b <= m; b++) {
                int db = elo[b][jobb - 1] - elo[b][bal];
                valasz[a][b] = max(valasz[a][b], db);
            }
        }
    }

    while (k--) {
        int a, b;
        cin >> a >> b;
        cout << valasz[a][b] << "\n";
    }
    return 0;
}
