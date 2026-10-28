/*
Megoldás lényege:
Egy fal akkor marad őrizetlen, ha mindkét végén nincs őrség, ezért az őrség nélküli őrhelyek egybefüggő szakaszait kell vizsgálni.
Egy L hosszúságú ilyen szakaszban L-1 fal van, és egy új őrség legfeljebb két szomszédos falat fed le.
Egy szakasz lefedéséhez így legalább floor(L/2) új őrség kell, és ez elég is: minden második helyre küldünk őrséget.
A szakaszok egymástól függetlenek, mert két szakaszt legalább egy már őrzött hely választ el, ezért a válasz a szakaszonkénti floor(L/2) értékek összege.
Időigény O(N), mert az őrhelyeket egyszer végigjárjuk.
*/
/*
Hint 1: || Egy fal csak akkor marad őrizetlen, ha mindkét végén nincs őrség. Keresd meg az őrség nélküli őrhelyek egybefüggő szakaszait. ||
Hint 2: || Egy szakaszban L-1 fal van, és egy új őrség legfeljebb két szomszédos falat fed le. Próbáld ki kis L-re (1, 2, 3, 4), hány őrség kell, és figyeld meg a mintát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<bool> guarded(n + 2, false);
    for (int i = 0; i < m; i++) {
        int p;
        cin >> p;
        guarded[p] = true;
    }

    long long answer = 0;
    int run = 0;
    for (int i = 1; i <= n + 1; i++) {
        if (i <= n && !guarded[i]) {
            run++;
        } else {
            answer += run / 2;
            run = 0;
        }
    }

    cout << answer << "\n";
    return 0;
}
