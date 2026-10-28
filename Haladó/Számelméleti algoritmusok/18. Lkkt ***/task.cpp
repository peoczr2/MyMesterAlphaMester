/*
Megoldás lényege: az lcm(a,b)=N feltétel prímenként külön teljesül: a és b kitevőinek maximuma pontosan az N
kitevője. Egy p^e prímhatványra a (x,y) kitevőpárok száma, ahol max(x,y)=e, (e+1)^2 - e^2 = 2e+1, így
lkktSzamlalo(N) a prímtényezős felbontás kitevőire Π(2e+1). Az 1..N számok felbontását legkisebb prímosztókat
tartalmazó szitával kapjuk meg, az értékeket pedig összegezzük; az időigény O(N log log N).
*/
/*
Hint 1: || Egy fix N-re az lcm(a,b)=N párok száma a prímtényezők kitevőiből külön-külön számolható. ||
Hint 2: || Ha N = p1^e1 * ... * pk^ek, akkor egy prímtényezőre 2*ei+1 kitevőpár adódik, a teljes szám ezek szorzata. ||
Hint 3: || Az 1..N számok prímtényezőit egy legkisebb prímosztókat tároló szitával gyorsan megkaphatod, így mindegyikre külön-külön kiszámolható az érték, majd összegezhető. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> spf(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (!spf[i]) {
            spf[i] = i;
            if (1LL * i * i <= n) {
                for (int j = i * i; j <= n; j += i) if (!spf[j]) spf[j] = i;
            }
        }
    }
    vector<long long> ways(n + 1);
    ways[1] = 1;
    for (int x = 2; x <= n; ++x) {
        int y = x;
        long long value = 1;
        while (y > 1) {
            int p = spf[y] ? spf[y] : y;
            int e = 0;
            while (y % p == 0) {
                y /= p;
                ++e;
            }
            value *= (2 * e + 1);
        }
        ways[x] = value;
    }
    long long answer = 0;
    for (int x = 1; x <= n; ++x) answer += ways[x];
    cout << answer << '\n';
    return 0;
}
