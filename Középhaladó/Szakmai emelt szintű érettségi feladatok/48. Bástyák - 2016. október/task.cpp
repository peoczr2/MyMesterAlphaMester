/*
Megoldás lényege:
Egy bástya lépésértéke azoknak a főirányoknak (fel, le, balra, jobbra) a száma, amelyeken a bástyától a tábla széléig minden mező üres. Ezt minden bástyánál a négy irányban egyesével haladva ellenőrizzük; ha a bástya már a szélen áll egy irányban, az az irány automatikusan beleszámít. Az eredeti táblát nem módosítjuk, az eredményt egy másolatba írjuk, ahol a 'B' karaktereket a lépésértékre cseréljük. A második részfeladatban a különböző lépésértékeket egy set-be gyűjtjük, és ennek méretét írjuk ki. Mivel a tábla rögzített 8x8-as, a futásidő és a memóriaigény is állandó.
*/
/*
Hint 1: || Minden bástyánál a négy főirány mindegyikén haladj a tábla széle felé, és nézd meg, van-e útközben bábu. Ha a bástya már a szélen áll abban az irányban, az az irány is beleszámít. ||
Hint 2: || A kimenetet külön másolaton állítsd elő: az eredeti táblán kell a bábuk útját vizsgálni, a lépésértéket pedig a másolatba írd. A lépésértékek 0 és 4 közötti egész számok, ezeket egy set-ben gyűjtve megszámolhatod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> t(8);
    for (auto &sor : t) {
        cin >> sor;
    }

    // irányok: fel, le, balra, jobbra
    const int dr[4] = {-1, 1, 0, 0};
    const int dc[4] = {0, 0, -1, 1};

    vector<string> ki = t;
    set<int> lepesertekek;
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (t[r][c] != 'B') {
                continue;
            }
            int ertek = 0;
            for (int d = 0; d < 4; d++) {
                bool szabad = true;
                int y = r + dr[d], x = c + dc[d];
                while (y >= 0 && y < 8 && x >= 0 && x < 8) {
                    if (t[y][x] != '.') {
                        szabad = false;
                        break;
                    }
                    y += dr[d];
                    x += dc[d];
                }
                if (szabad) {
                    ertek++;
                }
            }
            ki[r][c] = '0' + ertek;
            lepesertekek.insert(ertek);
        }
    }

    // 1. részfeladat: a tábla a bástyák lépésértékével
    cout << "#\n";
    for (const string &sor : ki) {
        cout << sor << "\n";
    }

    // 2. részfeladat: a különböző lépésértékek száma
    cout << "#\n" << lepesertekek.size() << "\n";
    return 0;
}
