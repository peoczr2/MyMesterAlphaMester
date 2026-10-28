/*
Megoldás lényege:
Szempontonként csak az alsó határt elérő (értékelhető) kutyák között keressük a legkisebb pontszámot, és megszámoljuk, hányan érik el. Egy kutya ebben a szempontban az értékeltek közül utolsó lett, ha a pontja ez a minimum, és rajta kívül senki más nem éri el. Az a kutya felel meg, amelyik minden szempontban vagy kiesett, vagy utolsó lett. A megfelelő kutyák száma és sorszáma kerül a kimenetre. Az időigény O(N·M).
*/
/*
Hint 1: || Szempontonként a kiesőket hagyd ki, a megmaradók közül keresd meg a legkisebb pontszámot, és számold meg, hányan érik el pontosan ezt. ||
Hint 2: || Egy kutyára minden szempontban az a feltétel, hogy a pontja a határ alatt van, vagy a pontja a legkisebb és ezt egyedül ő éri el; a sorszámokat növekvő sorrendben írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m), minPont(m);
    for (int &x : maxPont) cin >> x;
    for (int &x : minPont) cin >> x;

    vector<vector<int>> p(n, vector<int>(m));
    for (auto &sor : p)
        for (int &x : sor) cin >> x;

    // szempontonként a legkisebb értékelhető pont és az azt elérők száma
    vector<int> legkisebb(m, INT_MAX), darab(m, 0);
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++) {
            if (p[i][j] < minPont[j]) continue;
            if (p[i][j] < legkisebb[j]) {
                legkisebb[j] = p[i][j];
                darab[j] = 1;
            } else if (p[i][j] == legkisebb[j]) {
                darab[j]++;
            }
        }

    vector<int> talalt;
    for (int i = 0; i < n; i++) {
        bool mindenSzempont = true;
        for (int j = 0; j < m; j++) {
            bool kiesett = p[i][j] < minPont[j];
            bool utolso = !kiesett && p[i][j] == legkisebb[j] && darab[j] == 1;
            if (!kiesett && !utolso) {
                mindenSzempont = false;
                break;
            }
        }
        if (mindenSzempont) talalt.push_back(i + 1);
    }

    cout << talalt.size();
    for (int x : talalt) cout << ' ' << x;
    cout << '\n';
    return 0;
}
