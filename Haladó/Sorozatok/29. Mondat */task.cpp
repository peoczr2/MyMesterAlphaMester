/*
Megoldas lenyege:
A mondat szavait eloszor feldaraboljuk. Ezutan az egyes átalakítások már csak
a szavak listájának egyszerű újrarendezését vagy betűszintű megfordítását
jelentik. Minden kimeneti sor külön, függetlenül állítható elő.
*/
/*
Hint 1: || Először bontsd szavakra a bemeneti mondatot. ||
Hint 2: || Az első három átalakítás csak a szavak sorrendjét vagy elejét használja. ||
Hint 3: || A negyedik sorhoz az egyes szavakat külön-külön kell megfordítani. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    if (line.empty()) getline(cin, line);

    vector<string> words;
    string cur;
    stringstream ss(line);
    while (ss >> cur) words.push_back(cur);

    for (int i = (int)words.size() - 1; i >= 0; --i) {
        if (i != (int)words.size() - 1) cout << ' ';
        cout << words[i];
    }
    cout << '\n';

    bool first = true;
    for (int i = 0; i < (int)words.size(); i += 2) {
        if (!first) cout << ' ';
        first = false;
        cout << words[i];
    }
    cout << '\n';

    for (int i = 0; i < (int)words.size(); ++i) {
        if (i) cout << ' ';
        cout << char(toupper(words[i][0]));
    }
    cout << '\n';

    for (int i = 0; i < (int)words.size(); ++i) {
        if (i) cout << ' ';
        string rev = words[i];
        reverse(rev.begin(), rev.end());
        cout << rev;
    }
    cout << '\n';
    return 0;
}
