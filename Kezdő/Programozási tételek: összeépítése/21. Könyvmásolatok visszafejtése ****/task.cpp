/*
Megoldás lényege:
A másolatok keletkezési sorrendben vannak, ezért minden szöveghez az előtte lévő szövegek közül keressük a szülőt. Egy j szöveg akkor lehet az i-edik szöveg szülője, ha legfeljebb K betűben tér el tőle, és a különbségi pozíciók közül egyiket sem változtatták meg már a j szöveg származási láncában (a megváltozott betű nem változik tovább). Az érvényes jelöltek közül azt választjuk, amelytől a legkevesebb betűben tér el; egyenlőség esetén a kisebb sorszámút. Minden szövegnél egy logikai tömbben tároljuk, mely pozíciókat változtatták meg a láncában, így a következő jelöltek ellenőrzése egyszerű. Az időigény O(N²·M), ami N ≤ 10 és M ≤ 1000 mellett bőven belefér a 0,1 mp-es időlimitbe.
*/
/*
Hint 1: || Minden másolatot a korábbi szövegek egyikéből kell levezetni, ezért a szövegeket sorban, egyesével dolgozd fel. ||
Hint 2: || Egy jelölt szülő akkor érvényes, ha legfeljebb K betűben tér el az aktuális szövegtől, és a különbségi pozíciók között nincs olyan, amelyet a jelölt származási láncában már megváltoztattak. ||
Hint 3: || Minden szövegnél tárolj egy logikai tömböt arról, mely pozíciókat változtatták meg a láncában. A kiválasztott szülő tömbjét másold át, majd jelöld meg a különbségi pozíciókat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> texts(n);
    for (int i = 0; i < n; i++) {
        getline(cin, texts[i]);
        if (!texts[i].empty() && texts[i].back() == '\r') {
            texts[i].pop_back();
        }
    }

    int m = texts[0].size();
    vector<vector<bool>> changed(n, vector<bool>(m, false));
    vector<int> parent(n, -1);

    for (int i = 1; i < n; i++) {
        int best = -1;
        int bestDiff = INT_MAX;
        for (int j = 0; j < i; j++) {
            int diff = 0;
            bool valid = true;
            for (int p = 0; p < m; p++) {
                if (texts[i][p] != texts[j][p]) {
                    if (changed[j][p]) {
                        valid = false;
                        break;
                    }
                    diff++;
                }
            }
            if (valid && diff <= k && diff < bestDiff) {
                best = j;
                bestDiff = diff;
            }
        }

        parent[i] = best;
        changed[i] = changed[best];
        for (int p = 0; p < m; p++) {
            if (texts[i][p] != texts[best][p]) {
                changed[i][p] = true;
            }
        }
    }

    for (int i = 1; i < n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << parent[i] + 1;
    }
    cout << "\n";
    return 0;
}
