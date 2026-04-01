/*
Megoldás lényege:
Ebben a hálóban egy lefelé lépés B esetén 0-val, K esetén 1-gyel, J esetén 2-vel növeli az aktuális
pozíció "oszlopszámát". Így egy végpontot csak az út hossza és a lépések összpontszáma határoz meg,
nem a sorrendjük.

Ha egy barát A lépés alatt S összpontszámot ért el, akkor t közös lépés után pontosan azokból a
pozíciókból folytathatja, ahol az addigi összpontszám a [max(0, S-2*(A-t)), min(2*t, S)] intervallumba
esik. A legnagyobb olyan t kell, ahol a két barát lehetséges intervalluma metszi egymást. A válasz t+1.
*/
/*
Hint 1: || A végpont helyét itt az összegzett B/K/J-érték határozza meg: 0, 1, illetve 2. ||
Hint 2: || Fix közös prefixhosszra nézd meg, milyen prefixösszeg-értékekből érhető még el a célpont. ||
Hint 3: || Ha a két lehetséges prefixösszeg-intervallum metszi egymást, addig együtt mehettek. ||
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

    auto value = [](char ch) {
        if (ch == 'B') return 0;
        if (ch == 'K') return 1;
        return 2;
    };

    int sumA = 0;
    int sumB = 0;
    for (char ch : s) sumA += value(ch);
    for (char ch : t) sumB += value(ch);

    int best = 0;
    for (int commonSteps = 0; commonSteps <= min(A, B); ++commonSteps) {
        int leftA = max(0, sumA - 2 * (A - commonSteps));
        int highA = min(2 * commonSteps, sumA);
        int leftB = max(0, sumB - 2 * (B - commonSteps));
        int highB = min(2 * commonSteps, sumB);
        if (max(leftA, leftB) <= min(highA, highB)) {
            best = commonSteps;
        }
    }

    cout << best + 1 << '\n';
    return 0;
}