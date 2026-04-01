#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
Az F-ekből álló leírásban egy csomópontot egy F-lánc és az ahhoz tartozó,
zárójelbe tett gyerekszubfák írnak le. Egy szubrészfa tehát egy vagy több F-ből
álló lánccal kezdődik, majd utána a gyermekek egymás után, zárójelben következnek.

Ebből rekurzívan ki tudjuk számolni:
1. hány közvetlen gyerek van az adott csomópontnál;
2. az egész részfában mekkora a maximális gyerek-szám.

Hint 1: || A teljes fa egy F-láncból és az annak végén álló gyerek-szubfákból áll. ||
Hint 2: || Minden zárójelpár pontosan egy közvetlen gyereket jelent. ||
Hint 3: || A részfákon rekurzívan végighaladva egyszerre megkaphatod a helyi és a globális maximumot is. ||
*/

struct Res {
    int totalBranches = 0;
    int maxBranches = 0;
};

string s;
int pos;

Res parseTree() {
    int chain = 0;
    while (pos < (int)s.size() && s[pos] == 'F') {
        ++chain;
        ++pos;
    }

    Res cur;
    int children = 0;
    while (pos < (int)s.size() && s[pos] == '(') {
        ++children;
        ++pos;
        Res child = parseTree();
        cur.totalBranches += child.totalBranches;
        cur.maxBranches = max(cur.maxBranches, child.maxBranches);
        if (pos < (int)s.size() && s[pos] == ')') ++pos;
    }
    cur.totalBranches += children;
    cur.maxBranches = max(cur.maxBranches, children);
    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    pos = 0;
    Res ans = parseTree();
    cout << ans.totalBranches << '\n' << ans.maxBranches << '\n';
    return 0;
}