/*
Megoldas lenyege:
Minden nyelvhez es sporthoz felvesszuk, hogy mely diakok valasztottak azt. Mivel a diakok
szama legfeljebb 1000, ezeket egy azonos hosszu binaris karakterlancba kodolhatjuk, ahol az
i-edik hely akkor 1, ha az i-edik diak valasztotta az adott nyelvet vagy sportot. Ha ket
karakterlanc megegyezik, akkor a ket halmaz is megegyezik, tehat ezt kell megszamolni.
*/
/*
Hint 1: || A diákok halmazát egy fix hosszúságú 0/1 sorozattal is eltárolhatod. ||
Hint 2: || Ugyanaz a halmaz akkor és csak akkor jelenik meg, ha a két kód pontosan megegyezik. ||
Hint 3: || A válaszhoz elég a nyelvek kódjait megszámolni, majd a sportoknál ezekhez hozzászámolni a találatokat. ||
*/
#include <bits/stdc++.h>
using namespace std;

static string readSet(int d) {
    int cnt;
    cin >> cnt;
    string code(d, '0');
    for (int i = 0; i < cnt; ++i) {
        int x;
        cin >> x;
        code[x - 1] = '1';
    }
    return code;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int d, n, s;
    cin >> d >> n >> s;

    unordered_map<string, int> langCount;
    langCount.reserve(n * 2 + 1);
    for (int i = 0; i < n; ++i) {
        ++langCount[readSet(d)];
    }

    long long answer = 0;
    for (int i = 0; i < s; ++i) {
        string sport = readSet(d);
        auto it = langCount.find(sport);
        if (it != langCount.end()) answer += it->second;
    }

    cout << answer << '\n';
    return 0;
}
