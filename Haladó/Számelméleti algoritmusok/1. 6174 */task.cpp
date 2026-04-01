/*
 * 6174-es tétel: a négyjegyű szám számjegyeit rendezgetve ismételt kivonással
 * eljutunk a 6174-hez. Az egyes lépésekhez kiírjuk a rendezett számokat és a
 * különbséget, majd megkeressük a legkisebb azonos lépésszámú négyjegyű számot.
 
Hint 1: || Egy lépésben csak a négy számjegyet kell rendezni csökkenő és növekvő sorrendbe, majd kivonni őket. ||
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
