/*
Megoldas lenyege:
Elmentjuk a hivatalos nyelveket a megadott sorrendben es egy gyors lookup mapben is.
Ezutan vegigolvassuk a tanulok valasztasait: ami nincs a mapben, az illegalis, ami benne
van, annal noveljuk az adott nyelv valasztottsagat.

A kiirasnal az illegalis tanulosorszamokat, a senki altal nem valasztott nyelveket es a
valasztott nyelvek darabszamait a feladat altal kert formatumban, a megadott nyelvsorrendet
megtartva allitjuk elo.
*/
/*
Hint 1: || A nyelvek szama kicsi, de a nevekhez gyors keresest egy map egyszeruen ad. ||
Hint 2: || Az illegalis valasztasoknal a tanulo sorszamat kell eltárolni. ||
Hint 3: || A masodik es harmadik sorban a nyelvek eredeti sorrendjet tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

static void trimCarriageReturn(string& s) {
    if (!s.empty() && s.back() == '\r') s.pop_back();
}

static void printJoined(const vector<string>& parts) {
    for (int i = 0; i < (int)parts.size(); ++i) {
        if (i) cout << ',';
        cout << parts[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    string line;
    getline(cin, line);

    vector<string> languages(n);
    unordered_map<string, int> indexOf;
    for (int i = 0; i < n; ++i) {
        getline(cin, languages[i]);
        trimCarriageReturn(languages[i]);
        indexOf[languages[i]] = i;
    }

    vector<int> count(n, 0), illegalStudents;
    for (int i = 1; i <= m; ++i) {
        string choice;
        getline(cin, choice);
        trimCarriageReturn(choice);
        auto it = indexOf.find(choice);
        if (it == indexOf.end()) {
            illegalStudents.push_back(i);
        } else {
            ++count[it->second];
        }
    }

    cout << illegalStudents.size();
    if (!illegalStudents.empty()) {
        cout << ' ';
        for (int i = 0; i < (int)illegalStudents.size(); ++i) {
            if (i) cout << ',';
            cout << illegalStudents[i];
        }
    }
    cout << '\n';

    vector<string> unused;
    for (int i = 0; i < n; ++i) {
        if (count[i] == 0) unused.push_back(languages[i]);
    }
    cout << unused.size();
    if (!unused.empty()) cout << ' ';
    if (!unused.empty()) {
        for (int i = 0; i < (int)unused.size(); ++i) {
            if (i) cout << ',';
            cout << unused[i];
        }
    }
    cout << '\n';

    vector<string> used;
    for (int i = 0; i < n; ++i) {
        if (count[i] > 0) used.push_back(languages[i] + ":" + to_string(count[i]));
    }
    printJoined(used);
    return 0;
}