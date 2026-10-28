/*
Megoldás lényege:
Minden kutyát a bemenet sorrendjében egyszer nézünk végig. Egy kutya akkor kerül a listába, ha legalább egy szempontban a pontszáma pontosan az adott szempont alsó ponthatárával egyezik. A kiesés itt nem számít: a minimumon álló kutya akkor is bekerül, ha máshol az alsó határ alatt van. Egy logikai jelzővel biztosítjuk, hogy egy kutya akkor is csak egyszer szerepeljen, ha több szempontban is minimumot ért el. Az idő O(N·M).
*/
/*
Hint 1: || Egy kutya szempontonként vizsgálható: ha valamelyik pontja pontosan az ott megadott alsó határral egyezik, a kutya kérdéses. ||
Hint 2: || Soronként elég egy logikai jelző: a sor végén döntsd el, bekerül-e a listába, így a kutya sorszáma is csak egyszer szerepel. ||
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

    vector<int> valasz;
    for (int i = 1; i <= n; i++) {
        bool minimumon = false;
        for (int j = 0; j < m; j++) {
            int p;
            cin >> p;
            if (p == minPont[j]) minimumon = true;
        }
        if (minimumon) valasz.push_back(i);
    }

    cout << valasz.size();
    for (int x : valasz) cout << ' ' << x;
    cout << '\n';
    return 0;
}
