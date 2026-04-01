/*
Megoldás lényege:
Ha minden betűt egy csak 'A' karakterekből álló szóra cserélünk, akkor a két
kapott kép pontosan akkor egyezik meg, ha a teljes hossz megegyezik. Ezért elég
az egyes betűkhöz rendelt hosszakat meghatározni.

Legyen c1[X] és c2[X] az X betű előfordulásszáma a két szóban. Az L közös hossz
feltétele:

sum c1[X] * len[X] = sum c2[X] * len[X],   len[X] >= 1.

Átrendezve:

sum (c1[X] - c2[X]) * len[X] = 0.

Mivel a hosszakat minimalizálni akarjuk, kezdetben minden betűhöz 1-et adunk,
és csak a szükséges oldalon növelünk. Így egy egyváltozós, korlátlan hátizsák
DP-t kapunk: az eltérést pontosan ki kell egyenlíteni minimális többlethosszal.

Az elkészült hosszakból a konkrét helyettesítés egyszerű: minden betű képe legyen
"A" ismételve a neki kiosztott hossz szerint.

Idő: O(26 * |len1-len2|)
*/
/*
Hint 1: || Nem magukat a helyettesítő szavakat kell először keresni, hanem csak a hosszukat. ||
Hint 2: || Ha minden kép csak 'A' betűkből áll, akkor az egyenlőséghez csak a teljes hossz számít. ||
Hint 3: || Az alapértelmezett 1 hossz után csak azon a betűhalmazon kell növelni, amelyik a rövidebb oldalt tudja felhozni. ||
*/

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;

    vector<int> cnt1(26, 0), cnt2(26, 0), present(26, 0);
    for (char ch : a) {
        cnt1[ch - 'A']++;
        present[ch - 'A'] = 1;
    }
    for (char ch : b) {
        cnt2[ch - 'A']++;
        present[ch - 'A'] = 1;
    }

    int base_diff = (int)a.size() - (int)b.size();
    vector<int> len(26, 1);

    if (base_diff != 0) {
        int need = abs(base_diff);
        vector<int> weight, cost, letter;
        for (int i = 0; i < 26; ++i) {
            int diff = cnt1[i] - cnt2[i];
            if ((base_diff < 0 && diff > 0) || (base_diff > 0 && diff < 0)) {
                weight.push_back(abs(diff));
                cost.push_back(cnt1[i]);
                letter.push_back(i);
            }
        }

        const int INF = 1e9;
        vector<int> dp(need + 1, INF), parent_sum(need + 1, -1), parent_item(need + 1, -1);
        dp[0] = 0;
        for (int sum = 0; sum <= need; ++sum) {
            if (dp[sum] == INF) {
                continue;
            }
            for (int i = 0; i < (int)weight.size(); ++i) {
                int next_sum = sum + weight[i];
                if (next_sum > need) {
                    continue;
                }
                if (dp[sum] + cost[i] < dp[next_sum]) {
                    dp[next_sum] = dp[sum] + cost[i];
                    parent_sum[next_sum] = sum;
                    parent_item[next_sum] = i;
                }
            }
        }

        int cur = need;
        while (cur > 0) {
            int item = parent_item[cur];
            len[letter[item]]++;
            cur = parent_sum[cur];
        }
    }

    long long total = 0;
    for (int i = 0; i < 26; ++i) {
        total += 1LL * cnt1[i] * len[i];
    }

    cout << total << '\n';
    for (int i = 0; i < 26; ++i) {
        if (!present[i]) {
            continue;
        }
        cout << char('A' + i) << ' ' << string(len[i], 'A') << '\n';
    }

    return 0;
}