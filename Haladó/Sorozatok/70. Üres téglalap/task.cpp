/*
Megoldás lényege:
A legnagyobb üres téglalap felső határa a tábla széle, vagy egy fasor alatti sor; alsó határa a tábla
széle, vagy egy fasor feletti sor. Ezért elég a fasorok közötti vízszintes sávokat vizsgálni: legfeljebb
K+1 lehetséges felső határ van, és mindegyikhez egy lefelé tartó sávot kell bejárni.

Egy adott felső határhoz a sáv alját alulról felfelé vizsgáljuk: kezdetben a felső határ alatt álló
összes fa tiltja az oszlopát, felfelé haladva pedig fákat törlünk. Egy oszlop akkor szabadul fel, ha
már egyetlen fa sem áll benne, és ilyenkor a két szomszédos tiltott oszlop közti rés egyetlen réssé
olvad össze. Mivel a törlés sosem csökkenti a legnagyobb rést, az egy lépésben frissíthető, a tiltott
oszlopokat pedig kétirányú láncolt listában tartjuk. Az összidő O(K^2), ami a 7000 fára is belefér
az időlimitbe.
*/
/*
Hint 1: || Az optimális téglalap felső és alsó széle a tábla szélén van, vagy egy fasor közvetlen szomszédságában. ||
Hint 2: || Fix felső határ alatt alulról felfelé haladva a tiltott oszlopok halmaza csak szűkül, így a legnagyobb rés csak nőhet. ||
Hint 3: || Két szomszédos tiltott oszlop közti rés egy oszlop felszabadulásakor egyetlen réssé olvad össze, a szomszédokat láncolt lista adja. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n, k;
    cin >> m >> n >> k;

    vector<pair<int, int>> trees(k);
    for (auto &t : trees) cin >> t.first >> t.second;
    sort(trees.begin(), trees.end());

    // fasorok (növekvő), és a soraikhoz tartozó tartomány a trees-ben
    vector<int> rows;
    vector<int> rowBegin;
    for (int i = 0; i < k; ++i) {
        if (i == 0 || trees[i].first != trees[i - 1].first) {
            rows.push_back(trees[i].first);
            rowBegin.push_back(i);
        }
    }
    const int R = (int)rows.size();
    rowBegin.push_back(k);

    // oszlopok tömörítése: colId[i] a trees[i] oszlopának sorszáma a cols listában
    vector<int> cols;
    for (auto &t : trees) cols.push_back(t.second);
    sort(cols.begin(), cols.end());
    cols.erase(unique(cols.begin(), cols.end()), cols.end());
    const int C = (int)cols.size();

    vector<int> colId(k);
    for (int i = 0; i < k; ++i) {
        colId[i] = (int)(lower_bound(cols.begin(), cols.end(), trees[i].second) - cols.begin());
    }

    // láncolt lista csomópontjai: 0 = bal határ (0), c+1 = cols[c], C+1 = jobb határ (n+1)
    vector<int> val(C + 2);
    val[0] = 0;
    for (int c = 0; c < C; ++c) val[c + 1] = cols[c];
    val[C + 1] = n + 1;

    vector<int> cnt(C, 0);   // hány fa van az adott oszlopban a vizsgált sávon belül
    vector<int> cur(C);
    vector<int> prv(C + 2), nxt(C + 2);
    long long answer = 0;

    // t = -1: felső határ a tábla széle; t >= 0: felső határ a t. fasor alatti sor
    // cnt mindig azoknak a fáknak a számát tartalmazza, amelyek sora nagyobb, mint t
    for (int t = R - 1; t >= -1; --t) {
        int top = (t < 0 ? 1 : rows[t] + 1);
        if (top <= m) {
            cur = cnt;
            int maxGap = 0;
            int last = 0;
            for (int c = 0; c < C; ++c) {
                if (cur[c] == 0) continue;
                int node = c + 1;
                maxGap = max(maxGap, val[node] - val[last] - 1);
                nxt[last] = node;
                prv[node] = last;
                last = node;
            }
            maxGap = max(maxGap, val[C + 1] - val[last] - 1);
            nxt[last] = C + 1;
            prv[C + 1] = last;

            // alsó határ a tábla alja
            answer = max(answer, (long long)(m - top + 1) * maxGap);

            // alulról felfelé: a q. fasor törlése után az állapot a q. sor feletti sávnak felel meg
            for (int q = R - 1; q > t; --q) {
                for (int j = rowBegin[q]; j < rowBegin[q + 1]; ++j) {
                    int c = colId[j];
                    if (--cur[c] == 0) {
                        int node = c + 1;
                        int a = prv[node], b = nxt[node];
                        maxGap = max(maxGap, val[b] - val[a] - 1);
                        nxt[a] = b;
                        prv[b] = a;
                    }
                }
                if (rows[q] > top) {
                    answer = max(answer, (long long)(rows[q] - top) * maxGap);
                }
            }
        }
        if (t >= 0) {
            for (int j = rowBegin[t]; j < rowBegin[t + 1]; ++j) ++cnt[colId[j]];
        }
    }

    cout << answer << '\n';
    return 0;
}
