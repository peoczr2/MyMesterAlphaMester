/*
Megoldas lenyege:
A lokalisan meleg es hideg napok definicioja globalis: eloszor az egesz meressorozatban jeloljuk
meg, mely napok lokalis maximumok es minimumok, es egy idoszakban ezek kozul kell pontosan K,
illetve L darabot szamolni.

Ezert eleg ket 0/1 sorozatot kepezni: hot[i], cold[i]. Ha PH es PC ezek prefixosszegei,
akkor egy [L,R] szakaszban a ket darabszam PH[R]-PH[L-1], illetve PC[R]-PC[L-1]. Minden jobb
veghez azt kell megszamolni, hany korabbi prefixre igaz, hogy (PH[L-1],PC[L-1]) =
(PH[R]-K, PC[R]-L). Ezt egy hash map tarolja az eddig latott prefixparok gyakorisagaval.
*/
/*
Hint 1: || Az idoszak ket vegpontja nem lehet lokalis csucs az adott idoszakon belul. ||
Hint 2: || A belso napok csucsszamai prefixosszegekkel szamolhatok. ||
Hint 3: || A keresett intervallumok szama par-differencia megszamlalas lesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, needHot, needCold;
    cin >> n >> needHot >> needCold;
    vector<int> h(n + 1);
    for (int i = 1; i <= n; ++i) cin >> h[i];

    vector<int> hot(n + 1, 0), cold(n + 1, 0);
    for (int i = 2; i <= n - 1; ++i) {
        hot[i] = (h[i] > h[i - 1] && h[i] > h[i + 1]);
        cold[i] = (h[i] < h[i - 1] && h[i] < h[i + 1]);
    }

    vector<int> prefHot(n + 1, 0), prefCold(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prefHot[i] = prefHot[i - 1] + hot[i];
        prefCold[i] = prefCold[i - 1] + cold[i];
    }

    unordered_map<long long, long long> count;
    count.reserve(2 * n + 1);
    auto encode = [](int a, int b) -> long long {
        return (static_cast<long long>(a) << 32) ^ static_cast<unsigned int>(b);
    };

    long long answer = 0;
    count[encode(0, 0)] = 1;
    for (int right = 1; right <= n; ++right) {
        long long key = encode(prefHot[right] - needHot, prefCold[right] - needCold);
        auto it = count.find(key);
        if (it != count.end()) answer += it->second;
        count[encode(prefHot[right], prefCold[right])]++;
    }

    cout << answer << '\n';
    return 0;
}