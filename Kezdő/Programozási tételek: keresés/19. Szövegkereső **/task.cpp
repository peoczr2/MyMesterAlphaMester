/*
Megoldás lényege:
A közös szót karakterről karakterre építjük, és mindkét keresőszóban nyomon követjük, hányadik elemnél tartunk: az (i, j) pár azt jelenti, hogy az első szó i, a második j elemét már feldolgoztuk. Ha mindkét elem betű vagy kérdőjel, egyszerre egy karaktert fogyasztanak, és a karakter a betű lesz (két kérdőjel esetén bármi lehet, ezt pontnak írjuk). Ha az egyik elem csillag, az elnyelhet a másik szó következő elemének megfelelő karaktert, vagy nulla karaktert illeszthet, azaz kihagyható. A keresést visszalépéses bejárással (DFS) végezzük, a már sikertelen állapotokat megjegyezzük, így legfeljebb (n+1)·(m+1) állapotot járunk be. Ha nincs közös szó, a NEM kerül a kimenetre. Az időigény O(n·m), ahol n és m a két keresőszó hossza.
*/
/*
Hint 1: || Karakterről karakterre építsd a közös szót, és a két keresőszóban külön-külön jegyezd, meddig jutottál. Egy karakter csak akkor kerülhet a szóba, ha mindkét keresőszó elfogadja a helyén. ||
Hint 2: || A csillag két dolgot tehet: vagy nulla karaktert illeszt (kihagyjuk), vagy még egy karaktert elnyel a másik szó következő elemétől. Mindkét lehetőséget próbáld ki visszalépéses kereséssel. ||
Hint 3: || Ha egy (i, j) állapotból már nem lehet eljutni a végére, jegyezd meg, hogy ne számold ki újra, így a futásidő a két szó hosszának szorzata. ||
*/
#include <bits/stdc++.h>
using namespace std;

string p, q;
int n, m;
string word;
vector<vector<char>> dead;

bool dfs(int i, int j) {
    if (i == n && j == m) return true;
    if (dead[i][j]) return false;

    bool starP = i < n && p[i] == '*';
    bool starQ = j < m && q[j] == '*';

    // A csillag elnyeli a másik szó következő elemének karakterét
    if (starP && j < m && !starQ) {
        word.push_back(q[j] == '?' ? '.' : q[j]);
        if (dfs(i, j + 1)) return true;
        word.pop_back();
    }
    if (starQ && i < n && !starP) {
        word.push_back(p[i] == '?' ? '.' : p[i]);
        if (dfs(i + 1, j)) return true;
        word.pop_back();
    }
    // Mindkét elem betű vagy kérdőjel: egy közös karakter
    if (i < n && j < m && !starP && !starQ) {
        if (p[i] == q[j] || p[i] == '?' || q[j] == '?') {
            char c = (p[i] != '?') ? p[i] : (q[j] != '?' ? q[j] : '.');
            word.push_back(c);
            if (dfs(i + 1, j + 1)) return true;
            word.pop_back();
        }
    }
    // Nulla karakter: a csillag kihagyható
    if (starP && dfs(i + 1, j)) return true;
    if (starQ && dfs(i, j + 1)) return true;

    dead[i][j] = 1;
    return false;
}

int main() {
    cin >> p >> q;
    n = p.size();
    m = q.size();
    dead.assign(n + 1, vector<char>(m + 1, 0));
    if (dfs(0, 0)) {
        cout << word << "\n";
    } else {
        cout << "NEM\n";
    }
    return 0;
}
