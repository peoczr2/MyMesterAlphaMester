/*
Megoldás lényege:
Január 1. hétnapját ismerjük, ezért bármely hónap 13. napjának hétnapja kiszámítható: a 13. nap január
1. után annyi nappal esik, amennyi az előző hónapok napjainak összege, plusz 12. Ezt a számot a január
1. hétnapjának sorszámához (hétfő = 0, …, vasárnap = 6) adva és 7-tel osztva megkapjuk a hétnapot,
a péntek sorszáma 4. A szökőévet a szokásos szabállyal (4-gyel osztható, de 100-zal nem, vagy 400-zal
osztható) döntjük el, ettől függ a február napjainak száma. A hónapok száma állandó, így az időigény
is állandó.
*/
/*
Hint 1: || Egy hónap 13. napja január 1. után annyi nappal van, amennyi az előző hónapok napjainak összege, plusz 12. ||
Hint 2: || Számozd a hétnapokat 0-tól 6-ig, tárold a hónapok hosszát egy 12 elemű tömbben, és szökőévben februárt 29 napnak vedd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int year;
    string first;
    cin >> year >> first;

    map<string, int> dayIndex = {
        {"hetfo", 0}, {"kedd", 1}, {"szerda", 2}, {"csutortok", 3},
        {"pentek", 4}, {"szombat", 5}, {"vasarnap", 6}
    };
    int start = dayIndex[first];

    bool leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    int len[12] = {31, leap ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const char *names[12] = {
        "januar", "februar", "marcius", "aprilis", "majus", "junius",
        "julius", "augusztus", "szeptember", "oktober", "november", "december"
    };

    vector<string> res;
    int before = 0; // az előző hónapok napjainak száma
    for (int m = 0; m < 12; m++) {
        int weekday = (start + before + 12) % 7;
        if (weekday == 4) res.push_back(names[m]);
        before += len[m];
    }

    cout << res.size() << '\n';
    for (size_t i = 0; i < res.size(); i++) {
        if (i) cout << ' ';
        cout << res[i];
    }
    cout << '\n';
    return 0;
}
