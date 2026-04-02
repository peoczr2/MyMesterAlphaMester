/*
Megoldás lényege:
Egy rögzített [0..R] prefixre két végéről haladva csak háromféle lépés történhet:
ha a két szélső betű azonos, akkor mindkettőt megtartjuk és beljebb megyünk;
ha különböznek, akkor pontos megoldásban csak balról vagy jobbról törölhetünk egyet.
Ezért egy állapotot elég a felhasznált törlések száma és azon belül a jobbról
törölt betűk száma alapján leírni. Egy ilyen állapotból a még megmaradt intervallum
egyértelműen meghatározható, és abból mindig greedyn le lehet vágni az azonos szélső
betűkből álló leghosszabb szakaszt.

Legyen d az eddig felhasznált törlések száma, v ezek közül a jobbról töröltek száma,
és legyen best[d][v] a greedyn összehúzott intervallum bal széle. Ekkor a jobb széle
képlettel visszaszámolható, így minden állapotból legfeljebb két átmenet van:
egy bal oldali és egy jobb oldali törlés. Ha valamelyik állapotban a megmaradt rész
hossza legfeljebb 1, vagy a maradék törlések számával 1 hosszúra rövidíthető,
akkor az adott prefix jó.

Az azonos szélső betűk greedyn levágott hossza sokszor kell. Ezt nem karakterenként,
hanem a szó és a fordítottja fölé épített suffix array + LCP struktúrával kérdezzük le
O(1) időben. Így egy prefix ellenőrzése O(K^2), a teljes megoldás O(n*K^2), ahol
n <= 10000.
*/
/*
Hint 1: || Egy prefix akkor jó, ha két végéről haladva legfeljebb K törléssel el tudsz jutni üres vagy egybetűs részszóig. ||
Hint 2: || Ha már eldöntötted, hogy eddig összesen d törlést használtál, és ebből v darabot jobbról, akkor a jelenlegi bal és jobb index képlettel visszaszámolható. ||
Hint 3: || Egy állapotból a szélső egyező betűk levágása kényszerített; ezt érdemes előre gyors lekérdezéssé alakítani a szó és a fordítottja között. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct SuffixArray {
    int n;
    string text;
    vector<int> sa;
    vector<int> rank_pos;
    vector<int> lcp;
    vector<int> log2_floor;
    vector<vector<int>> sparse;

    explicit SuffixArray(const string& s) : n(static_cast<int>(s.size())), text(s), sa(n), rank_pos(n) {
        build_sa();
        build_lcp();
        build_sparse();
    }

    void build_sa() {
        vector<int> new_rank(n);
        for (int i = 0; i < n; ++i) {
            sa[i] = i;
            rank_pos[i] = static_cast<unsigned char>(text[i]);
        }

        for (int step = 1;; step <<= 1) {
            auto cmp = [&](int a, int b) {
                if (rank_pos[a] != rank_pos[b]) {
                    return rank_pos[a] < rank_pos[b];
                }
                int ra = (a + step < n ? rank_pos[a + step] : -1);
                int rb = (b + step < n ? rank_pos[b + step] : -1);
                return ra < rb;
            };

            sort(sa.begin(), sa.end(), cmp);
            new_rank[sa[0]] = 0;
            for (int i = 1; i < n; ++i) {
                new_rank[sa[i]] = new_rank[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
            }
            rank_pos.swap(new_rank);
            if (rank_pos[sa[n - 1]] == n - 1) {
                break;
            }
        }
    }

    void build_lcp() {
        if (n == 1) {
            return;
        }
        lcp.assign(n - 1, 0);
        int common = 0;
        for (int i = 0; i < n; ++i) {
            int rank = rank_pos[i];
            if (rank == n - 1) {
                common = 0;
                continue;
            }
            int j = sa[rank + 1];
            while (i + common < n && j + common < n && text[i + common] == text[j + common]) {
                ++common;
            }
            lcp[rank] = common;
            if (common > 0) {
                --common;
            }
        }
    }

    void build_sparse() {
        int m = static_cast<int>(lcp.size());
        log2_floor.assign(max(2, m + 1), 0);
        for (int i = 2; i <= m; ++i) {
            log2_floor[i] = log2_floor[i / 2] + 1;
        }
        if (m == 0) {
            return;
        }
        int levels = log2_floor[m] + 1;
        sparse.assign(levels, vector<int>(m));
        sparse[0] = lcp;
        for (int level = 1; level < levels; ++level) {
            int len = 1 << level;
            int half = len >> 1;
            for (int i = 0; i + len <= m; ++i) {
                sparse[level][i] = min(sparse[level - 1][i], sparse[level - 1][i + half]);
            }
        }
    }

    int common_prefix(int a, int b) const {
        if (a == b) {
            return n - a;
        }
        int ra = rank_pos[a];
        int rb = rank_pos[b];
        if (ra > rb) {
            swap(ra, rb);
        }
        int left = ra;
        int right = rb - 1;
        int len = right - left + 1;
        int level = log2_floor[len];
        return min(sparse[level][left], sparse[level][right - (1 << level) + 1]);
    }
};

struct Solver {
    int n;
    int k;
    string s;
    string rev;
    int rev_base;
    SuffixArray suffix_array;
    vector<int> best;

    Solver(int k_value, string word)
        : n(static_cast<int>(word.size())),
          k(min(k_value, max(0, static_cast<int>(word.size()) - 1))),
          s(std::move(word)),
          rev(s.rbegin(), s.rend()),
          rev_base(n + 1),
          suffix_array(s + "{" + rev),
          best((k + 1) * (k + 1), -1) {}

    int index(int deleted, int right_deleted) const {
        return deleted * (k + 1) + right_deleted;
    }

    int matched_pairs(int left, int right) const {
        if (left >= right) {
            return 0;
        }
        int limit = (right - left + 1) / 2;
        int reversed_pos = rev_base + (n - 1 - right);
        return min(limit, suffix_array.common_prefix(left, reversed_pos));
    }

    int shrink_left(int left, int right) const {
        return left + matched_pairs(left, right);
    }

    bool good_prefix(int right_end) {
        fill(best.begin(), best.end(), -1);
        best[index(0, 0)] = shrink_left(0, right_end);

        for (int deleted = 0; deleted <= k; ++deleted) {
            for (int right_deleted = 0; right_deleted <= deleted; ++right_deleted) {
                int left = best[index(deleted, right_deleted)];
                if (left < 0) {
                    continue;
                }

                int right = right_end - left + deleted - 2 * right_deleted;
                if (left >= right) {
                    return true;
                }
                if (right - left <= k - deleted) {
                    return true;
                }
                if (deleted == k) {
                    continue;
                }

                int next_left = shrink_left(left + 1, right);
                int& keep_right = best[index(deleted + 1, right_deleted)];
                if (next_left > keep_right) {
                    keep_right = next_left;
                }

                next_left = shrink_left(left, right - 1);
                int& drop_right = best[index(deleted + 1, right_deleted + 1)];
                if (next_left > drop_right) {
                    drop_right = next_left;
                }
            }
        }

        return false;
    }

    int solve() {
        if (n == 0 || k >= n - 1) {
            return n;
        }
        for (int right_end = n - 1; right_end >= 0; --right_end) {
            if (good_prefix(right_end)) {
                return right_end + 1;
            }
        }
        return 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    string s;
    cin >> k >> s;

    Solver solver(k, s);
    cout << solver.solve() << '\n';
    return 0;
}