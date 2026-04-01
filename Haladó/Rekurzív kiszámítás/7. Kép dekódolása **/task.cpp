/*
Megoldás lényege:
Az input egy quadtree-kódhalmaz: minden kód egy homogén négyzetet jelöl. A kód elején
álló 1..4 számjegyek a negyedeket jelölik, a 0 utáni karakter pedig a színt. A teljes
kép visszaállítása egyszerű rekurzív bejárással elvégezhető.

*/

// Hint 1: || A kód eleje a négy rész egyikébe vezető út, a 0 utáni karakter pedig a szín. ||
// Hint 2: || Egy kód csak egy négyzetet fed le, ezért elég a megfelelő tartományt kitölteni. ||
// Hint 3: || A négy negyed koordinátáit mindig ugyanabban a sorrendben kezeld. ||

#include <bits/stdc++.h>
using namespace std;

struct Item {
    string code;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<string> code(M);
    for (int i = 0; i < M; ++i) cin >> code[i];

    vector<string> img(N, string(N, '?'));

    auto paint = [&](auto&& self, int x, int y, int len, const string& s, int pos) -> void {
        if (s[pos] == '0') {
            char color = s[pos + 1];
            for (int i = y; i < y + len; ++i) {
                for (int j = x; j < x + len; ++j) img[i][j] = color;
            }
            return;
        }
        int half = len / 2;
        int q = s[pos] - '1';
        int nx = x + (q % 2) * half;
        int ny = y + (q / 2) * half;
        self(self, nx, ny, half, s, pos + 1);
    };

    for (const string& s : code) paint(paint, 0, 0, N, s, 0);

    cout << N << '\n';
    for (int i = 0; i < N; ++i) cout << img[i] << '\n';
    return 0;
}
