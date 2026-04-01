/*
Megoldás lényege:
Jelöljük C-vel azoknak a kérdéseknek a számát, ahol ugyanazt válaszoltuk, és D=N-C-vel az eltérőket.
Az egyező helyeken vagy mindketten jók vagy mindketten rosszak, az eltérő helyeken pedig pontosan
az egyikünk adhatott jó választ. Ha az egyező helyek közül X darabon voltunk mindketten jók, akkor
a barát pontszáma miatt X + Y = P teljesül, ahol Y az eltérő helyek azon száma, ahol ő volt jó.

Innen X csak egy intervallumban mozoghat, és a saját pontszámom D - P + 2*X alakú, tehát a minimum
és maximum a megengedett X intervallum két végpontján adódik.
*/
/*
Hint 1: || Az azonos válaszú kérdéseknél együtt nyerünk vagy együtt veszítünk pontot. ||
Hint 2: || Az eltérő válaszú kérdéseknél pontosan egyikőtök lehet helyes. ||
Hint 3: || Írd fel az egyező helyeken közösen jó válaszok számát ismeretlenként, és abból mindkét szélsőérték kijön. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    cin >> n >> p;
    string friendAnswers, myAnswers;
    cin >> friendAnswers >> myAnswers;

    int same = 0;
    for (int i = 0; i < n; ++i) {
        if (friendAnswers[i] == myAnswers[i]) {
            ++same;
        }
    }
    int diff = n - same;

    int minCommonCorrect = max(0, p - diff);
    int maxCommonCorrect = min(same, p);

    int minScore = diff - p + 2 * minCommonCorrect;
    int maxScore = diff - p + 2 * maxCommonCorrect;
    cout << minScore << ' ' << maxScore << '\n';
    return 0;
}