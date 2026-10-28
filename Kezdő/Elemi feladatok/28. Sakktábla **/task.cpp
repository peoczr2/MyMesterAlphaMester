/*
Megoldás lényege: egy K×K-s sakktáblán az egyik színből ceil(K²/2), a másikból floor(K²/2) sütemény kell, a sarok színe pedig szabadon választható. Ezért K akkor készíthető el, ha a kisebb készlet legalább floor(K²/2), a nagyobb készlet pedig legalább ceil(K²/2). Ha egy K megfelel, akkor a kisebb K-k is megfelelnek, így K-t 1-től felfelé növelve az utolsó megfelelő érték a válasz. A válasz legfeljebb kb. 1415, ezért a ciklus néhány ezer lépésben lefut.
*/
/*
Hint 1: || Egy K×K-s táblán a két szín darabszáma legfeljebb eggyel különbözik: páros K² esetén egyenlő, páratlan esetén az egyik szín eggyel több. A sarok színe szabadon választható, tehát a kisebb készletet a kisebb, a nagyobbat a nagyobb részre kell illesztened. ||
Hint 2: || Legyen a = min(N, M), b = max(N, M), és egy K-ra kis = K*K/2 (egész osztás), nagy = K*K - kis. A K akkor jó, ha kis ≤ a és nagy ≤ b. K-t 1-től növelve az első rossz K előtti érték a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;

    long long kisebb = min(n, m);
    long long nagyobb = max(n, m);

    long long legnagyobb = 0;
    for (long long k = 1; ; k++) {
        long long kis = k * k / 2;
        long long nagy = k * k - kis;
        if (kis > kisebb || nagy > nagyobb) break;
        legnagyobb = k;
    }

    cout << legnagyobb << "\n";
    return 0;
}
