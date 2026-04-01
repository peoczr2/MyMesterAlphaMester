/*
 * N összes legalább K-jegyű rész-osztóját keressük. Minden részsztringet ellenőrzünk,
 * és az előírt sorrendben kiírjuk a valódi osztókat.
 
Hint 1: || A rész-osztó definíciója miatt a szám összes folytonos részsztringjét végig lehet nézni. ||
Hint 2: || A jó részsztringek közül csak azokat írd ki, amelyek számmá alakítva valódi osztói N-nek, és tartsd meg az előírt hossz- majd pozíciórendet. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    int k;
    cin >> n >> k;
    string s = to_string(n);
    vector<string> answer;
    for (int len = (int)s.size(); len >= k; --len) {
        for (int pos = 0; pos + len <= (int)s.size(); ++pos) {
            string t = s.substr(pos, len);
            long long x = stoll(t);
            if (x != n && n % x == 0) answer.push_back(t);
        }
    }
    for (int i = 0; i < (int)answer.size(); ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}
