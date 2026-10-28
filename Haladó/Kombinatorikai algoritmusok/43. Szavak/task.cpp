/*
   Szavak: az összes nem üres, a megadott betűmultihalmazból kirakható szó lexikografikus sorrendben,
   ahol a prefix kisebb a bővítményénél. A következő szó: ha S-hez még maradt felhasználható betű,
   akkor S + a legkisebb ilyen betű; különben hátulról keressük az első olyan pozíciót, ahol az aktuális
   betű egy nagyobb, még elérhető betűre cserélhető, és a szó ott véget ér. Az előző szó: ha S utolsó
   betűjét egy kisebb, elérhető betűre cseréljük (a legnagyobbra), a maradék betűket csökkenő sorrendben
   tesszük a végére; ha ez nem lehetséges, S utolsó betűjének elhagyása adja az előzőt. Egybetűs S esetén
   ciklikusan a legnagyobb szó az előző. Az időigény O(N * 26).
*/
/*
Hint 1: || Az előtag mindig kisebb a bővítményénél, ezért először azt nézd meg, maradt-e a multihalmazban olyan betű, amellyel S meghosszabbítható. Ha igen, a legkisebb ilyen betű adja a következő szót. ||
Hint 2: || Ha S minden betűt felhasznált, a következő szó S egy olyan változata, ahol hátulról keresve az első olyan pozíción a betű nagyobbra cserélhető, és a szó ott véget ér. A betűk darabszámát egy 26 elemű tömbben tartsd nyilván. ||
Hint 3: || Az előző szónál: ha S utolsó betűjét lehet kisebb, elérhető betűre cserélni, a legnagyobbra cseréld, és a maradék betűket csökkenő sorrendben fűzd a végére. Különben S utolsó betűjének elhagyása adja az előzőt, és csak egybetűs S esetén kell ciklikusan a legnagyobb szóra ugrani. ||
*/
#include <bits/stdc++.h>
using namespace std;

static string nextWord(const string& s, const vector<int>& total) {
    vector<int> used(26, 0);
    for (char c : s) used[c - 'a']++;

    for (int c = 0; c < 26; ++c) {
        if (used[c] < total[c]) return s + char('a' + c);
    }

    for (int i = (int)s.size() - 1; i >= 0; --i) {
        used[s[i] - 'a']--;
        int cur = s[i] - 'a';
        for (int c = cur + 1; c < 26; ++c) {
            if (used[c] < total[c]) return s.substr(0, i) + char('a' + c);
        }
    }

    for (int c = 0; c < 26; ++c) {
        if (total[c] > 0) return string(1, char('a' + c));
    }
    return "";
}

static string maxWord(const vector<int>& total) {
    vector<int> rem = total;
    string ans;
    while (true) {
        int c = -1;
        for (int i = 25; i >= 0; --i) if (rem[i] > 0) { c = i; break; }
        if (c < 0) break;
        ans.push_back(char('a' + c));
        --rem[c];
    }
    return ans;
}

static string prevWord(const string& s, const vector<int>& total) {
    int L = (int)s.size();
    vector<int> used(26, 0);
    for (int i = 0; i + 1 < L; ++i) used[s[i] - 'a']++;

    int cur = s[L - 1] - 'a';
    for (int c = cur - 1; c >= 0; --c) {
        if (used[c] < total[c]) {
            string ans = s.substr(0, L - 1) + char('a' + c);
            vector<int> rem = total;
            for (int j = 0; j < 26; ++j) rem[j] -= used[j];
            --rem[c];
            while (true) {
                int d = -1;
                for (int x = 25; x >= 0; --x) if (rem[x] > 0) { d = x; break; }
                if (d < 0) break;
                ans.push_back(char('a' + d));
                --rem[d];
            }
            return ans;
        }
    }
    if (L > 1) return s.substr(0, L - 1);
    return maxWord(total);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    string letters, s;
    cin >> letters >> s;

    vector<int> total(26, 0);
    for (char c : letters) total[c - 'a']++;

    cout << prevWord(s, total) << '\n' << nextWord(s, total) << '\n';
    return 0;
}