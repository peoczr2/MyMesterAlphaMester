/*
Megoldás lényege:
Szempontonként megkeressük a legjobb pontszámot, és megszámoljuk, hány kutya éri el. Holtversenyes győzelemről beszélünk, ha a legjobb pont legalább az alsó határ, és legalább két kutya osztozik rajta. Egy kutya akkor kerül a listába, ha legalább egy ilyen szempontban holtversenyben a legjobbak között van. Az ellenőrzés egy-két bejárással történik, az idő O(N·M).
*/
/*
Hint 1: || Szempontonként keresd meg a legnagyobb pontszámot, és számold meg, hányan érik el. Két vagy több kutya közös első helye holtverseny. ||
Hint 2: || Egy kutya akkor kerül a listába, ha van olyan szempont, ahol ő is a legjobb pontszámot kapta, és ezen a ponton legalább két kutya osztozik. Ne felejtsd el az alsó határt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // A szempontok maximumai most nem kellenek: beolvassuk, de nem tároljuk.
    for (int j = 0; j < m; j++) {
        int x;
        cin >> x;
    }

    vector<int> minPont(m);
    for (int &x : minPont) cin >> x;

    vector<vector<int>> p(n, vector<int>(m));
    for (auto &sor : p)
        for (int &x : sor) cin >> x;

    vector<int> legjobb(m, -1), darab(m, 0);
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            legjobb[j] = max(legjobb[j], p[i][j]);
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            if (p[i][j] == legjobb[j]) darab[j]++;

    vector<int> valasz;
    for (int i = 0; i < n; i++) {
        bool holtverseny_gyoztes = false;
        for (int j = 0; j < m; j++) {
            if (legjobb[j] >= minPont[j] && p[i][j] == legjobb[j] && darab[j] >= 2)
                holtverseny_gyoztes = true;
        }
        if (holtverseny_gyoztes) valasz.push_back(i + 1);
    }

    cout << valasz.size();
    for (int x : valasz) cout << ' ' << x;
    cout << '\n';
    return 0;
}
