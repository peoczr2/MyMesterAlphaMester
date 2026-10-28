/*
Megoldás lényege:
Minden kutyánál egy bejárásban összegezzük a pontjait, és közben ellenőrizzük, hogy valamelyik szempontban az alsó ponthatár alatt maradt-e. A feladat szerint az ilyen kutya automatikusan kiesik, ezért a kiesett kutyák összpontszámát a bemenet sorrendjében gyűjtjük. A kimenet első száma a kiesők darabszáma, utána a pontszámaik következnek. Az idő O(N·M).
*/
/*
Hint 1: || Egy kutya kiesik, ha legalább egy szempontban a pontja kisebb az adott szempont alsó határánál. Ehhez elég egyetlen szempontot találni. ||
Hint 2: || Az összpontszámot ugyanabban a bejárásban add össze: sorban olvasd be a kutya pontjait, összegezd őket, és közben jelöld, volt-e alsó határ alatti pont. ||
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

    vector<long long> kieso;  // a kiesők összpontszáma, bemeneti sorrendben
    for (int i = 0; i < n; i++) {
        long long osszeg = 0;
        bool kiesett = false;
        for (int j = 0; j < m; j++) {
            int p;
            cin >> p;
            osszeg += p;
            if (p < minPont[j]) kiesett = true;
        }
        if (kiesett) kieso.push_back(osszeg);
    }

    cout << kieso.size();
    for (long long x : kieso) cout << ' ' << x;
    cout << '\n';
    return 0;
}
