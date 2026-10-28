/*
Megoldás lényege:
A vonatokat sorban, egyesével olvassuk be, és minden vonatnál összevetjük a menetidejét K-val. Mivel a feladat K percnél rövidebb időt kér, a feltétel szigorú: csak az M < K vonatok kerülnek be. A megfelelő vonatok sorszámát (1-től indulva) egy vektorba tesszük, amely a bejárás miatt már növekvő sorrendben lesz. A végén kiírjuk a vektor méretét, majd a sorszámokat. Az időigény O(N).
*/
/*
Hint 1: || Csak egyetlen bejárás kell: minden vonathoz elég a menetidejét összevetni K-val. Figyelj rá, hogy a feladat szigorúan rövidebb időt kér. ||
Hint 2: || Egy vektorban gyűjtsd a megfelelő vonatok sorszámait a beolvasás sorrendjében, az i-edik vonat sorszáma legyen i. A kiírt darabszám a vektor mérete. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> gyorsak;
    for (int i = 1; i <= n; i++) {
        int menetido;
        cin >> menetido;
        if (menetido < k) {
            gyorsak.push_back(i);
        }
    }

    cout << gyorsak.size();
    for (int sorszam : gyorsak) {
        cout << " " << sorszam;
    }
    cout << "\n";
    return 0;
}
