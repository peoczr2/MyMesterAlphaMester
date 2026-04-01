/*
Megoldas lenyege:
Minden program sorait végigolvassuk, és a tag-eket egy veremmel ellenőrizzük.
Nyitó tag esetén a nevet betesszük a verembe, záró tag esetén pedig azt
vizsgáljuk, hogy a verem tetején ugyanez a név áll-e. A program akkor helyes,
ha a feldolgozás végére a verem üres, és közben nem történt eltérés.
*/
/*
Hint 1: || A tag-ek helyességét veremmel lehet ellenőrizni. ||
Hint 2: || Nyitó tagot mindig betesszük, zárónál pedig a verem tetejét kell megnézni. ||
Hint 3: || A program akkor jó, ha a végén a verem üres marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

static void processLine(const string& line, vector<string>& st, bool& ok) {
    for (size_t i = 0; i < line.size() && ok; ) {
        if (line[i] != '<') { ++i; continue; }
        size_t j = line.find('>', i);
        string tag = line.substr(i + 1, j - i - 1);
        if (!tag.empty() && tag[0] == '/') {
            string name = tag.substr(1);
            if (st.empty() || st.back() != name) ok = false;
            else st.pop_back();
        } else {
            st.push_back(tag);
        }
        i = j + 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    string line;
    getline(cin, line);
    for (int t = 0; t < k; ++t) {
        vector<string> st;
        bool ok = true;
        while (getline(cin, line)) {
            if (line == "*") break;
            processLine(line, st, ok);
        }
        if (!st.empty()) ok = false;
        cout << (ok ? "HELYES" : "ROSSZ") << '\n';
    }
    return 0;
}
