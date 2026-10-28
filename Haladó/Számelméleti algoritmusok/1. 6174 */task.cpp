/*
Megoldás lényege:
A 6174-es tétel szerint a négyjegyű szám számjegyeit csökkenő (A) és növekvő (B)
sorrendbe rendezve az A - B különbség újabb négyjegyű számot ad, és ezt ismételve
mindig eljutunk a 6174-hez. A program az N kiindulóértéktől kezdve kiírja minden
lépés A, B és az új szám értékét, amíg 6174-et nem kapunk. Az utolsó sorba a
legkisebb olyan négyjegyű szám kerül, amelynek ugyanannyi lépés kell a 6174-hez:
ezt az 1000 és 9999 közötti számokon keressük, a csupa azonos jegyből álló
számokat kihagyva (azok nullához vezetnek). Egy lépés konstans idejű, a keresés
legfeljebb 9000 szám végigpróbálása, ezért gyorsan lefut.
*/
/*
Hint 1: || Egy lépésben csak a négy számjegyet kell rendezni csökkenő és növekvő sorrendbe, majd kivonni őket. ||
Hint 2: || A keresésnél először számold ki N lépésszámát, majd 1000-től 9999-ig minden számra ugyanezt, és az első egyezőt írd ki. ||
*/

#include "../common.hpp"

static int step_count(int n) {
    int steps = 0;
    while (n != 6174) {
        string s = to_string(n);
        while ((int)s.size() < 4) s.insert(s.begin(), '0');
        string a = s, b = s;
        sort(a.begin(), a.end(), greater<char>());
        sort(b.begin(), b.end());
        n = stoi(a) - stoi(b);
        ++steps;
    }
    return steps;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int current = n;
    while (current != 6174) {
        string s = to_string(current);
        while ((int)s.size() < 4) s.insert(s.begin(), '0');
        string a = s, b = s;
        sort(a.begin(), a.end(), greater<char>());
        sort(b.begin(), b.end());
        int next = stoi(a) - stoi(b);
        cout << stoi(a) << ' ' << stoi(b) << ' ' << next << '\n';
        current = next;
    }
    int target_steps = step_count(n);
    int best = 10000;
    for (int x = 1000; x <= 9999; ++x) {
        string s = to_string(x);
        if (count(s.begin(), s.end(), s[0]) == 4) continue;
        if (step_count(x) == target_steps) {
            best = x;
            break;
        }
    }
    cout << best << '\n';
    return 0;
}
