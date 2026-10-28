/*
Megoldás lényege:
A modulok közötti függőséget irányított gráfként kezeljük: i → j, ha az i modulnak szüksége van a j modulra. Az A) részhez az M csúcsból az élek irányában elérhető modulokat gyűjtjük össze (M nélkül). A B) részhez azok a modulok kellenek, amelyek közvetlenül használják M-et, vagyis az M-be mutató élek; ezek szerzőit gyűjtjük össze, M saját szerzőjét pedig kihagyjuk, mert ő maga változtatja M-et. A C) részhez szerzőnként megnézzük, hogy az általa írt modulok minden függősége ugyanattól a szerzőtől származik-e; az első ilyen szerzőt írjuk ki, különben -1-et. Minden rész O(N+F) időben fut.
*/
/*
Hint 1: || Tekintsd a modulokat csúcsoknak, és az „i-nek szüksége van j-re” összefüggést irányított élnek i → j; így a kérdések gráfbejárásra vezethetők vissza. ||
Hint 2: || Az A) részhez az M-ből kiinduló bejárást végezz az élek irányában; a B) részhez az éleket fordítva kell nézni, és csak az M-et közvetlenül használó modulok szerzői számítanak, M saját szerzőjét kihagyva. ||
Hint 3: || A C) résznél szerzőnként ellenőrizd az általa írt modulok függőségeit: ha mindegyik ugyanannak a szerzőnek a modulja, a szerző megfelel; a modullal nem rendelkező szerző is megfelel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, S, M, F;
    cin >> N >> S >> M >> F;

    vector<int> author(N + 1);
    for (int i = 1; i <= N; ++i) cin >> author[i];

    vector<vector<int>> needs(N + 1), needed_by(N + 1);
    for (int k = 0; k < F; ++k) {
        int i, j;
        cin >> i >> j;
        needs[i].push_back(j);
        needed_by[j].push_back(i);
    }

    auto reach = [&](const vector<vector<int>>& g) {
        vector<char> seen(N + 1, 0);
        queue<int> q;
        seen[M] = 1;
        q.push(M);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                if (!seen[v]) {
                    seen[v] = 1;
                    q.push(v);
                }
            }
        }
        return seen;
    };

    // A) M-hez szükséges további modulok
    vector<char> dep = reach(needs);
    vector<int> compile;
    for (int i = 1; i <= N; ++i) {
        if (i != M && dep[i]) compile.push_back(i);
    }
    cout << compile.size();
    for (int x : compile) cout << ' ' << x;
    cout << "\n";

    // B) M-et közvetlenül használó modulok szerzői, M saját szerzőjét kivéve
    vector<char> notify(S + 1, 0);
    for (int i : needed_by[M]) {
        if (author[i] != author[M]) notify[author[i]] = 1;
    }
    vector<int> authors;
    for (int a = 1; a <= S; ++a) {
        if (notify[a]) authors.push_back(a);
    }
    cout << authors.size();
    for (int a : authors) cout << ' ' << a;
    cout << "\n";

    // C) olyan szerző, aki nem használ más szerzőtől való modult
    int answer = -1;
    for (int a = 1; a <= S && answer == -1; ++a) {
        bool ok = true;
        for (int i = 1; i <= N && ok; ++i) {
            if (author[i] != a) continue;
            for (int j : needs[i]) {
                if (author[j] != a) {
                    ok = false;
                    break;
                }
            }
        }
        if (ok) answer = a;
    }
    cout << answer << "\n";
    return 0;
}
