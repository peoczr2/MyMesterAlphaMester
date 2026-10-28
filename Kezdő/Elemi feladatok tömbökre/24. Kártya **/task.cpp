/*
Megoldás lényege:
Összegezzük az összes kártyát: legyen S. Ha S osztható N-nel, akkor a végén mindenkinek pontosan K = S / N kártya lesz, és aki K-nál többet tart, annak a többletét kell odaadnia, a többiek nem adnak semmit. Ha S nem osztható N-nel, akkor egyetlen igazságos felosztás sem létezik, és a legkevesebb szerzendő kártya az, amellyel S a következő N-es többszörösére egészíthető ki, vagyis N - (S mod N). Mindkét eset egyetlen összegzéssel és egy osztással megoldható, az idő O(N).
*/
/*
Hint 1: || Számold ki a kártyák összegét. Akkor lehet igazságosan elosztani, ha ez az összeg osztható N-nel, mert így mindenkinek ugyanannyi jut. ||
Hint 2: || Ha osztható, a végén mindenkinek S / N kártya lesz. Az i. gyereknek A_i - S / N darabot kell adnia, ha ez pozitív, különben semennyit. Ha nem osztható, a hiányzó darabszám N - (S % N). ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> a(n);
    long long osszeg = 0;
    for (auto &x : a) {
        cin >> x;
        osszeg += x;
    }

    if (osszeg % n != 0) {
        // nincs igazságos felosztás: a hiányzó kártyák száma
        cout << "NEM\n";
        cout << n - osszeg % n << "\n";
        return 0;
    }

    // mindenkinek K kártya lesz a végén
    long long k = osszeg / n;
    cout << "IGEN\n";
    for (int i = 0; i < n; i++) {
        // csak a K-nál többet tartó gyerek ad el kártyát
        long long elad = max(0LL, a[i] - k);
        if (i) cout << ' ';
        cout << elad;
    }
    cout << "\n";
    return 0;
}
