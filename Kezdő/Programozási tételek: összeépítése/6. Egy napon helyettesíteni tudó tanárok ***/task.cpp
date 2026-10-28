/*
Megoldás lényege: a T. tanár H. napi óráit gyűjtjük ki, és óra szerint rendezzük őket. Minden ilyen órához
keressük a legkisebb sorszámú olyan másik tanárt, aki ugyanazt a tantárgyat tanítja, és abban az órában nincs
lekötve. A tanárok, napok és órák foglaltságát a busy[tanár][nap][óra] logikai tömbben, a tanítási
jogosultságot a teaches[tanár][tantárgy] táblázatban tároljuk, így egy szabadság-ellenőrzés O(1).
Ha valamelyik órához nincs szabad szakos helyettesítő, a kiírás egyetlen -1. Időigény: O(O + órák száma · N).
*/
/*
Hint 1: || A T. tanár H. napi óráihoz kell helyettesítő: először gyűjtsd ki ezeket az órákat, majd minden órához
nézd meg, melyik tanár tanítja ugyanazt a tantárgyat, és abban az órában szabad. ||
Hint 2: || Tárold háromdimenziós tömbben, hogy melyik tanár mikor (nap, óra) tanít, és külön táblázatban, hogy
melyik tanár melyik tantárgyat tanítja. Így minden szabadság-ellenőrzés egyetlen tömbolvasás. ||
Hint 3: || Az órákat óra szerint rendezd. Minden órához a tantárgy tanárai közül keresd a legkisebb számút, amelyik
nem T, és abban az órában nem tanít. Ha bármelyik órához nincs ilyen, csak -1-et írj ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int o, n, m, t, h;
    cin >> o >> n >> m >> t >> h;

    static bool busy[101][6][10];
    static bool teaches[101][101];
    vector<pair<int, int>> mine; // (óra, tantárgy) a T. tanár H. napi órái

    for (int i = 0; i < o; i++) {
        int tc, sc, d, hr;
        cin >> tc >> sc >> d >> hr;
        busy[tc][d][hr] = true;
        teaches[tc][sc] = true;
        if (tc == t && d == h) mine.push_back({hr, sc});
    }

    sort(mine.begin(), mine.end());

    vector<int> subs;
    for (auto [hr, sc] : mine) {
        int found = -1;
        for (int x = 1; x <= n && found == -1; x++) {
            if (x != t && teaches[x][sc] && !busy[x][h][hr]) found = x;
        }
        if (found == -1) {
            cout << -1 << '\n';
            return 0;
        }
        subs.push_back(found);
    }

    cout << subs.size();
    for (int x : subs) cout << ' ' << x;
    cout << '\n';
    return 0;
}
