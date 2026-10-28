/*
Megoldás lényege:
A szöveg minden pozíciója külön kérdés: az egyik helyen lévő betűk nem befolyásolják a másik helyet. Egy j pozícióra megszámoljuk, melyik karakter hányszor fordul elő az N másolat j-edik betűjeként. Ha van olyan karakter, amely a másolatok több mint felében szerepel, az lesz az eredeti szöveg j-edik betűje, különben a helyre # kerül. A karakterek darabszámát 256 elemű tömbben tároljuk, így minden pozíció O(N) időben feldolgozható, az összes pozíció O(N·M) időben. Ez N ≤ 10 és M ≤ 10 000 mellett bőven belefér a 0,1 mp-es időlimitbe.
*/
/*
Hint 1: || A szöveg pozíciói függetlenek egymástól: minden helyen külön kell eldönteni, melyik betű a többségi. ||
Hint 2: || Egy pozícióra számold meg, melyik karakter hányszor szerepel a másolatok azonos helyén, és nézd meg, van-e olyan, amely a másolatok több mint felében előfordul. ||
Hint 3: || A karakterek darabszámát tárold 256 elemű tömbben (a karakter kódja legyen az index). Ha nincs többségi karakter, a helyre # kerül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, m;
    cin >> n >> k >> m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> copies(n);
    for (int i = 0; i < n; i++) {
        getline(cin, copies[i]);
        if (!copies[i].empty() && copies[i].back() == '\r') {
            copies[i].pop_back();
        }
    }

    string original(m, '#');
    for (int j = 0; j < m; j++) {
        int count[256] = {0};
        for (int i = 0; i < n; i++) {
            count[(unsigned char)copies[i][j]]++;
        }
        for (int c = 0; c < 256; c++) {
            if (2 * count[c] > n) {
                original[j] = (char)c;
            }
        }
    }

    cout << original << "\n";
    return 0;
}
