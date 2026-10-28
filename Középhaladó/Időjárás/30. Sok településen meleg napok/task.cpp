/*
Megoldás lényege:
Egy nap akkor felel meg, ha a településeknek legalább a fele aznap legalább 30 fokos. A bemenet soronként egy település adatait tartalmazza, ezért a beolvasás közben minden napra külön számlálót növelünk, ha az adott érték legalább 30. A feltételt egész számokkal ellenőrizzük: 2·db ≥ N, így nincs szükség törtre. Az idő O(N·M), a memória O(M).
*/
/*
Hint 1: || A kérdés napokról szól, nem településekről: minden naphoz külön kell tudni, hány település érte el a 30 fokot. ||
Hint 2: || Számolj egy tömböt a napokra: a bemenet soronként érkezik, de minden értéket beolvasáskor azonnal a saját napjának számlálójához adhatsz. A „legalább felén” feltétel egész számokkal: 2·db ≥ N. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> meleg(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int h;
            cin >> h;
            if (h >= 30) meleg[j]++;
        }
    }

    vector<int> napok;
    for (int j = 1; j <= m; j++) {
        if (2 * meleg[j] >= n) napok.push_back(j);
    }

    cout << napok.size();
    for (int s : napok) cout << ' ' << s;
    cout << '\n';
    return 0;
}
