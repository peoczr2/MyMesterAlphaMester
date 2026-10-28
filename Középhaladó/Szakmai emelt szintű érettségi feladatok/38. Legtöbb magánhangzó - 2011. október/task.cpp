/*
Megoldás lényege:
Minden szóra megszámoljuk a benne lévő magánhangzókat (a, e, i, o, u kis- és nagybetűben), és közben nyilván tartjuk az eddigi legnagyobb értéket. A kötőjel nem magánhangzó, ezért nem számít. A szavakat egyesével olvassuk be, nem tároljuk őket, így a memóriaigény O(1). Egy szóban legfeljebb 100 karakter van, így az összes szó feldolgozása legfeljebb 10^6 lépés, az időigény O(N * L), ahol L a szavak hossza.
*/
/*
Hint 1: || Szavanként külön számold a magánhangzókat, a végeredmény pedig a szavak eredményeinek a maximuma. ||
Hint 2: || Egy karakter magánhangzó-e, ellenőrizheted az "aeiouAEIOU" karakterlistában való kereséssel, így a nagybetűket nem kell külön kezelni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    const string vowels = "aeiouAEIOU";

    int n;
    cin >> n;

    int best = 0;
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;

        int count = 0;
        for (char c : word) {
            if (vowels.find(c) != string::npos) {
                count++;
            }
        }
        best = max(best, count);
    }

    cout << best << "\n";
    return 0;
}
