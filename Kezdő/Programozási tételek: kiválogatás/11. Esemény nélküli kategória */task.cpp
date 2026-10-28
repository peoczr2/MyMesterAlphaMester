/*
Megoldás lényege:
Az eseményeket egyesével olvassuk be, és minden esemény kategóriáját egy logikai tömbben megjelöljük.
A kategóriák neveit a bemenet végén olvassuk be, a sorszámuk szerinti sorrendben. A kiíráshoz azokat a
kategóriákat gyűjtjük, amelyekhez egyetlen esemény sem tartozik, és ezeket kategória-sorszám szerinti
sorrendben írjuk ki a darabszámukkal együtt. Az év-intervallum sort beolvassuk, de a mintapéldák szerint
a számítás nem használja fel. Az esemény nevét teljes sorként olvassuk, így a szóközös nevek is helyesek.
Az időigény O(N + KSZ), ami a korlátok mellett triviális.
*/
/*
Hint 1: || Elég azt nyilvántartani, mely kategóriákhoz tartozik legalább egy esemény. ||
Hint 2: || Használj egy logikai tömböt, amelynek hossza KSZ+1, és minden eseménynél állítsd igazra az esemény kategóriájának elemét. ||
Hint 3: || Minden esemény 3 sorból áll: év, kategória, név. A név sorát getline-nal olvasd be, mielőtt a következő eseményre lépsz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, ksz;
    cin >> n >> ksz;

    vector<bool> hasEvent(ksz + 1, false);
    for (int i = 0; i < n; ++i) {
        int year, category;
        cin >> year >> category;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string eventName;
        getline(cin, eventName);
        hasEvent[category] = true;
    }

    int from, to;
    cin >> from >> to;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<string> names(ksz + 1);
    for (int c = 1; c <= ksz; ++c) {
        getline(cin, names[c]);
        if (!names[c].empty() && names[c].back() == '\r') names[c].pop_back();
    }

    vector<string> empty;
    for (int c = 1; c <= ksz; ++c) {
        if (!hasEvent[c]) empty.push_back(names[c]);
    }

    cout << empty.size();
    for (const string& name : empty) cout << ' ' << name;
    cout << '\n';
    return 0;
}
