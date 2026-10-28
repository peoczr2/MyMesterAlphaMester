/*
Megoldás lényege:
Minden székhez feljegyezzük, melyik diák ül rajta, és a diák jelenlegi székéből a célszékébe (a sorszámába) húzunk egy élt. Így a székek egy útra és diszjunkt körökre bomlanak: az út az (N+1)-es széknél indul és az üres széknél végződik, a körök ettől függetlenek.
Minden rosszul ülő diáknak legalább egy átülés kell. Egy legalább kétszékes körhöz ezen felül még egy átülés kell: a kör egyik diákja előbb az üres székre ül, a kör többi tagja a helyére megy, végül ő is átül a saját székére.
A válasz tehát: a rosszul ülő diákok száma plusz a legalább kétszékes körök száma. Az élek bejárása O(N) időben megoldható.
*/
/*
Hint 1: || Ne a diákokat, hanem a székeket tekintsd csomópontoknak: a diák jelenlegi székéből a célszékébe húzz egy élt, és figyeld meg, mi történik az üres székkel. ||
Hint 2: || Minden széknek legfeljebb egy bejövő és legfeljebb egy kimenő éle van. Az (N+1)-es széknek nincs bejövő éle, az üres széknek nincs kimenő éle, ezért a gráf egy útból és körökből áll. ||
Hint 3: || A válasz két részből áll: a rosszul ülő diákok száma, és a legalább kétszékes körök száma. Mindkettő egy bejárással kiszámolható, ha tárolod, melyik széken melyik diák ül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> seat(n + 1);     // seat[i]: az i. diák széke
    vector<int> who(n + 2, 0);   // who[s]: a s. széken ülő diák sorszáma (0, ha üres)
    for (int i = 1; i <= n; i++) {
        cin >> seat[i];
        who[seat[i]] = i;
    }

    long long answer = 0;
    for (int i = 1; i <= n; i++) {
        if (seat[i] != i) {
            answer++;
        }
    }

    vector<char> visited(n + 2, 0);

    // Az (N+1)-es széktől az üres székig vezető út.
    int cur = n + 1;
    while (who[cur] != 0) {
        visited[cur] = 1;
        cur = who[cur];
    }
    visited[cur] = 1;

    // A maradék körök: a legalább kétszékes körök számát adjuk hozzá.
    for (int s = 1; s <= n; s++) {
        if (visited[s]) {
            continue;
        }
        if (who[s] == s) {
            visited[s] = 1;
            continue;
        }
        answer++;
        cur = s;
        while (!visited[cur]) {
            visited[cur] = 1;
            cur = who[cur];
        }
    }

    cout << answer << "\n";
    return 0;
}
