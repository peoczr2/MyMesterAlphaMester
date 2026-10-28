/*
Megoldás lényege:
Az életkor legfeljebb 150, ezért nem kell a teljes sorozatot rendezni: elég megszámolni, hány ember van az egyes korokban.
Az N páratlan, így a rendezett sorban a középső ember a (N+1)/2. helyen áll.
A korokon növekvő sorrendben haladva kumuláljuk a darabszámokat, és az első olyan kornál megállunk, ahol az összeg eléri a (N+1)/2-t; ez a keresett életkor.
Az időigény O(N + 150).
*/
/*
Hint 1: || A középső elem sorszáma a rendezés után (N+1)/2, de nem kell rendezni: elég az előfordulásokat számolni. ||
Hint 2: || Az életkor legfeljebb 150, ezért egy gyakoriság-tömbben számolhatod az egyes korok darabszámát, majd a kumulált darabszámot nézed. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> cnt(151, 0);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        cnt[k]++;
    }

    int target = (n + 1) / 2;
    int seen = 0;
    for (int age = 1; age <= 150; age++) {
        seen += cnt[age];
        if (seen >= target) {
            cout << age << "\n";
            break;
        }
    }
    return 0;
}
