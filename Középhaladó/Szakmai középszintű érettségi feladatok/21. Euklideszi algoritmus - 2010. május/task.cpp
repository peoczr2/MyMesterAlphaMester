/*
Megoldás lényege:
Az euklideszi algoritmus szerint két szám legnagyobb közös osztója nem változik, ha a nagyobbat lecseréljük a kisebbel való osztás maradékára, vagyis gcd(a, b) = gcd(b, a mod b). Ezt a lépést addig ismételjük, amíg a második szám nulla lesz; ekkor az első szám a keresett érték. Ha a két szám mindkettő nulla, a ciklus azonnal véget ér, és a 0 az eredmény. Minden párra O(log max(A, B)) lépés kell, így a teljes időigény O(N log C), ami 20 000 párra bőven megfelel az időkorlátnak.
*/
/*
Hint 1: || Használd az összefüggést: gcd(a, b) = gcd(b, a mod b). Ez azt jelenti, hogy a két szám legnagyobb közös osztója nem változik, ha a nagyobb helyére a kisebbel való osztás maradékát írjuk. ||
Hint 2: || Az eljárást addig ismételd, amíg a második szám nulla nem lesz; ekkor az első szám a keresett legnagyobb közös osztó. Minden párt külön dolgozz fel, és az eredményt a bemenet sorrendjében írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

long long legnagyobbKozosOszto(long long a, long long b) {
    while (b != 0) {
        long long maradek = a % b;
        a = b;
        b = maradek;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        long long a, b;
        cin >> a >> b;
        cout << legnagyobbKozosOszto(a, b) << "\n";
    }

    return 0;
}
