/*
Megoldás lényege: a munkákat a bemenet szerinti (növekvő) határidejük sorrendjében dolgozzuk fel. Ha eddig k munkát
vállaltunk, a következő munkát akkor vesszük el, ha a (k+1). napon még el tudjuk végezni, azaz k+1 <= Hi.
Helyesség: a határidők szerint haladva az elfogadott munkák mindig a 1..k napokra ütemezhetők, és egy
elfogadott munka sem blokkol olyan későbbi munkát, amelyet egy optimális megoldás elfogadna (csereargumentum).
Időigény: O(N), a bemenet beolvasása dominál.
*/
/*
Hint 1: || Ha egy munka határideje d, akkor legkésőbb a d. napon készülhet el. ||
Hint 2: || Tartsd számon, hány munkát vállaltál már: ez lesz a következő munka napja. ||
Hint 3: || Növekvő határidőnél az első elfogadható munkákból épített mohó halmaz optimális. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> chosen;
    chosen.reserve(N);

    for (int i = 1; i <= N; ++i) {
        int h;
        cin >> h;
        if ((int)chosen.size() + 1 <= h) {
            chosen.push_back(i);
        }
    }

    cout << chosen.size() << '\n';
    for (int i = 0; i < (int)chosen.size(); ++i) {
        if (i) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}
