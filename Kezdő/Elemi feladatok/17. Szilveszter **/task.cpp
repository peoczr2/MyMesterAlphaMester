/*
Megoldás lényege:
A céldátum mindig a következő év január 1., 0:00:00. A kezdő időpontot és a céldátumot mezőnként kivonjuk, mint az írásbeli kivonásnál: ha egy mező negatívba menne, a következő nagyobb egységből kölcsönzünk. A napoknál a kölcsönzött napok száma december 31 nap, mert a céldátum előtti hónap mindig december. A hónapok száma így 13 − hónap, és ha a napoknál kellett kölcsönözni, ebből még egy hónap levonandó. Az év 12 hónapból áll, ezért a hónapok számát 12-vel osztva kapjuk az éveket. A művelet állandó idejű.
*/
/*
Hint 1: || A céldátum mindig a következő év január 1., 0:00:00. Érdemes a kezdő időpontot mezőnként kivonni a céldátumból, és ha egy mező negatív lenne, a nagyobb egységtől kölcsönözni. ||
Hint 2: || A napoknál a kölcsönzés a céldátum előtti hónapból jön, ami most december, 31 nappal. A hónapok száma 13 − hónap, és ha a napoknál kölcsönöztünk, ebből még egy hónap marad le. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int year, month, day, hour, minute, second;
    cin >> year >> month >> day >> hour >> minute >> second;

    int borrow = 0;

    int seconds = 0 - second;
    if (seconds < 0) { seconds += 60; borrow = 1; }

    int minutes = 0 - minute - borrow;
    borrow = 0;
    if (minutes < 0) { minutes += 60; borrow = 1; }

    int hours = 0 - hour - borrow;
    borrow = 0;
    if (hours < 0) { hours += 24; borrow = 1; }

    int days = 1 - day - borrow;
    borrow = 0;
    if (days < 0) { days += 31; borrow = 1; }  // december 31 napja

    int totalMonths = 13 - month - borrow;
    int years = totalMonths / 12;
    int months = totalMonths % 12;

    vector<pair<int, string>> parts = {
        {years, "ev"}, {months, "honap"}, {days, "nap"},
        {hours, "ora"}, {minutes, "perc"}, {seconds, "masodperc"}
    };

    bool first = true;
    for (auto &[value, unit] : parts) {
        if (value == 0) continue;
        if (!first) cout << ' ';
        cout << value << ' ' << unit;
        first = false;
    }
    cout << '\n';
    return 0;
}
