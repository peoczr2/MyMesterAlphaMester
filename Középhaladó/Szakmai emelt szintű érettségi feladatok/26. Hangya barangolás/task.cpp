/*
Megoldás lényege:
Két egymást követő mérés között K másodperc telik el, így az átlagsebesség a köztük lévő
egyenes távolság osztva K-val; méterből milliméter/s-ba a szorzó 1000. Ezért elég az
egymást követő pontpárok legnagyobb távolságát megkeresni. Mivel a gyökvonás monoton,
a legnagyobb négyzetes távolságot egész számként, pontosan keressük meg, és csak a végén
vonunk gyököt. A végeredményt matematikai módon kerekítjük (a pontosan .5-ös érték felfelé).
Az időigény O(N).
*/
/*
Hint 1: || Két egymást követő mérés között K másodperc telik el, így a sebesség a két pont közti egyenes távolság osztva K-val. ||
Hint 2: || A legnagyobb négyzetes távolságot egész számokkal keresd meg, mert a gyökvonás monoton; a gyökvonást és az 1000-es mértékegység-váltást csak a végén alkalmazd, majd kerekíts egészre. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];

    long long legnagyobb = 0; // legnagyobb négyzetes távolság két egymást követő mérés között
    for (int i = 0; i + 1 < n; i++) {
        long long dx = x[i + 1] - x[i];
        long long dy = y[i + 1] - y[i];
        legnagyobb = max(legnagyobb, dx * dx + dy * dy);
    }

    double sebesseg = 1000.0 * sqrt((double)legnagyobb) / k; // mm/s
    cout << llround(sebesseg) << "\n";
    return 0;
}
