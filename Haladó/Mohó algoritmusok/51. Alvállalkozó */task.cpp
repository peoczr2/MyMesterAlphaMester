/*
Feladat: Egynapos munkák határidőkkel adottak (növekvő sorrendben), egy alvállalkozó naponta legfeljebb egyet végezhet. A cél a maximálisan kiadható munkaszám.
Ötlet: Határidő szerinti egyetlen bejárás. Ha eddig k munkát vállaltunk, akkor a következő csak akkor fér be, ha a (k+1)-edik nap még nem késő a határidőhöz képest, azaz k+1 <= Hi. Ez a klasszikus egynapos, határidős maximum-kardinalitású kiválasztás.
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
