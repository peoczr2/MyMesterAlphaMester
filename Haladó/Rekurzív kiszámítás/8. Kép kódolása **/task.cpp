/*
Megoldás lényege:
Az azonos színű négyzetekhez 0+szín kódot írunk, az eltérő színű területeket pedig
négy negyedre bontjuk, és rekurzívan kódoljuk. A kész kódhalmazt lexikografikus
sorrendben a negyedek bejárási sorrendje adja.

*/

// Hint 1: || Ha egy négyzet egyszínű, azonnal kész a kódja. ||
// Hint 2: || Egy nem homogén tartományt mindig ugyanarra a négy részre bontunk. ||
// Hint 3: || A kimenethez elég egy DFS, ami 1-2-3-4 sorrendben halad. ||

#include <bits/stdc++.h>
using namespace std;

int N;
vector<string> img;
vector<string> out;

bool sameColor(int x, int y, int len) {
    char c = img[y][x];
    for (int i = y; i < y + len; ++i) {
        for (int j = x; j < x + len; ++j) {
            if (img[i][j] != c) return false;
        }
    }
    return true;
}

void encode(int x, int y, int len, string pref) {
    if (sameColor(x, y, len)) {
        out.push_back(pref + '0' + string(1, img[y][x]));
        return;
    }
    int half = len / 2;
    encode(x, y, half, pref + '1');
    encode(x + half, y, half, pref + '2');
    encode(x, y + half, half, pref + '3');
    encode(x + half, y + half, half, pref + '4');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> N)) return 0;
    img.resize(N);
    for (int i = 0; i < N; ++i) cin >> img[i];

    encode(0, 0, N, "");
    sort(out.begin(), out.end());

    cout << N << ' ' << out.size() << '\n';
    for (const auto& s : out) cout << s << '\n';
    return 0;
}
