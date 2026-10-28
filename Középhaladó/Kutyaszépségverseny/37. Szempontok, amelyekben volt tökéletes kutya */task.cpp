/*
Megoldás lényege:
Szempontonként azt nézzük, van-e olyan kutya, amely a szempont maximális pontszámát kapta. A tökéletes pontszám mindig eléri az alsó határt, ezért ehhez nem kell a kieső kutyákat külön kiszűrni. A tökéletes kutyás szempontok sorszámait gyűjtjük, a kimenetbe először a darabszám kerül, utána a sorszámok balról jobbra haladva, így növekvő sorrendben. Az időigény O(N·M), a memóriaigény O(M).
*/
/*
Hint 1: || Egy szempontban akkor volt tökéletes kutya, ha valakinek a pontszáma pontosan a szempont maximális pontja. Ezt szempontonként külön ellenőrizd. ||
Hint 2: || Tarts egy logikai tömböt szempontonként, amely azt jelöli, volt-e tökéletes pontszám. A végén a megjelölt szempontok sorszámait írd ki, elé a darabszámot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> maxPont(m);
    for (int &x : maxPont) cin >> x;

    // az alsó határok ehhez a kérdéshez nem kellenek, csak beolvassuk őket
    for (int j = 0; j < m; j++) {
        int alsoHatar;
        cin >> alsoHatar;
    }

    // volt[j]: volt-e tökéletes kutya a j. szempontban
    vector<bool> volt(m, false);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int p;
            cin >> p;
            if (p == maxPont[j]) volt[j] = true;
        }
    }

    vector<int> valasz;
    for (int j = 0; j < m; j++) {
        if (volt[j]) valasz.push_back(j + 1);
    }

    cout << valasz.size();
    for (int x : valasz) cout << ' ' << x;
    cout << '\n';
    return 0;
}
