/*
A feladat lényege az, hogy a műveletsor hatását egyetlen állapotváltozó-párra vezessük vissza: a pozícióra és az irányra. A végeredményhez elég a parancsokat sorrendben végigvinni, és minden lépésnél az aktuális irány szerint frissíteni az elmozdulást.
*/
/*
Hint 1: || A parancsokat egyetlen balról jobbra bejárással is feldolgozhatod; az irány állapota mindig csak 4 értéket vehet fel. ||
Hint 2: || A végső helyzethez elég a lépések hatását külön összesíteni az aktuális irány mellett. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    int dir = 0;
    int x = 0, y = 0;
    for (char c : s) {
        if (c == 'J') dir = (dir + 1) % 4;
        else if (c == 'B') dir = (dir + 3) % 4;
        else {
            if (dir == 0) ++y;
            else if (dir == 1) ++x;
            else if (dir == 2) --y;
            else --x;
        }
    }

    static const char *names[] = {"észak", "kelet", "dél", "nyugat"};
    cout << x << ' ' << y << '\n' << names[dir] << '\n';
    return 0;
}