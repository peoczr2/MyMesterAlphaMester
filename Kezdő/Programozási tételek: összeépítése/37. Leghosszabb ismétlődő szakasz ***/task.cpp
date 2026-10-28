/*
Megoldás lényege:
Két nem átfedő előfordulás egy t[i..] és egy t[j..] kezdetű (i < j) azonos szakasz, amelynek hossza legfeljebb j - i. Minden (i, j) párra a közös előtag hosszát egy LCP-táblázatban tárolom, amelyet a sorozat végéről visszafelé töltök: ha t[i] = t[j], akkor lcp[i][j] = lcp[i+1][j+1] + 1, különben 0. A párhoz tartozó legjobb nem átfedő hossz min(lcp[i][j], j - i). A maximumot balról jobbra keresem, és csak szigorúan hosszabb érték írja felül az eredményt, így a legkisebb kezdőindexű, vagyis a legelőször előforduló leghosszabb ismétlődés marad. Ha a hossz kisebb kettőnél, üres sort írok. Időigény és memóriaigény O(n^2), n <= 255 mellett bőven belül van.
*/
/*
Hint 1: || Az ismétlődés két nem átfedő előfordulást jelent: válassz két kezdőpozíciót (i és j, i < j), és nézd meg, meddig egyezik a sorozat i-től, illetve j-től kezdődő része. ||
Hint 2: || A két előfordulás akkor nem fedheti egymást, ha a közös szakasz hossza legfeljebb j - i. Így az (i, j) párhoz tartozó legjobb hossz a közös előtag hosszának és a j - i értéknek a minimuma. ||
Hint 3: || A közös előtag hosszait táblázatban tárold, és a sorozat végéről visszafelé töltsd: ha az i. és a j. karakter megegyezik, az érték az (i+1, j+1) mező értéke plusz egy, különben nulla. ||
Hint 4: || Az összes párt végigpróbálva tartsd meg a legnagyobb értéket; ha több azonos hosszú van, a legkisebb i-hez tartozót vedd. Ha a végeredmény nem legalább kettő hosszú, üres sort írj. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string t;
    cin >> t;
    int n = t.size();

    // lcp[i][j]: a t[i..] és t[j..] szuffixek közös előtagjának hossza
    vector<vector<int>> lcp(n + 1, vector<int>(n + 1, 0));
    for (int i = n - 1; i >= 0; i--)
        for (int j = n - 1; j >= 0; j--)
            if (t[i] == t[j]) lcp[i][j] = lcp[i + 1][j + 1] + 1;

    int legHossz = 0, legElso = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int h = min(lcp[i][j], j - i);   // a két előfordulás nem fedheti egymást
            if (h > legHossz) {
                legHossz = h;
                legElso = i;
            }
        }

    if (legHossz >= 2) cout << t.substr(legElso, legHossz) << "\n";
    else cout << "\n";
    return 0;
}
