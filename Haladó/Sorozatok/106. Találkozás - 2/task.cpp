/*
Megoldás lényege:
A bináris hálóban egy végpontot csak az határoz meg, hogy hányadik sorban van, és addig összesen
hány jobbra lépés történt. Ha egy barát A lépés után J darab jobbra lépéssel ér célba, akkor egy t
lépéses közös prefix után pontosan azokból a pozíciókból folytathatja az útját, ahol az addigi jobbra
lépések száma a [max(0, J-(A-t)), min(t, J)] intervallumba esik.

Tehát minden lehetséges közös prefixhosszra kiszámítható ez az elérhető pozícióintervallum mindkét
barátra, és a legnagyobb olyan t kell, ahol a két intervallum metszi egymást. A keresett sorszám t+1.
*/
/*
Hint 1: || Egy végpont helyét csak a jobbra lépések száma határozza meg. ||
Hint 2: || Fix közös prefixhosszra azt kell nézni, hány jobbra lépés férhetett bele addig. ||
Hint 3: || Ha a két lehetséges pozícióintervallum metszi egymást, akkor addig együtt mehettek. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, A, B;
    cin >> N >> A >> B;
    string s, t;
    cin >> s >> t;

    int rightA = 0;
    int rightB = 0;
    for (char ch : s) rightA += (ch == 'J');
    for (char ch : t) rightB += (ch == 'J');

    int best = 0;
    for (int commonSteps = 0; commonSteps <= min(A, B); ++commonSteps) {
        int leftA = max(0, rightA - (A - commonSteps));
        int highA = min(commonSteps, rightA);
        int leftB = max(0, rightB - (B - commonSteps));
        int highB = min(commonSteps, rightB);
        if (max(leftA, leftB) <= min(highA, highB)) {
            best = commonSteps;
        }
    }

    cout << best + 1 << '\n';
    return 0;
}