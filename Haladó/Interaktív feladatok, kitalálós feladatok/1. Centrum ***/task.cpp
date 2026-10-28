/*
Megoldás lényege:
A központ az a terminál, amely minden másikkal össze van kötve. Ha egy jelölt terminált végigkérdezünk az összes többivel (N-1 kérdés), két eset van. Ha mindenkivel össze van kötve, akkor ő a központ. Ha van nem összekötött párja, akkor nem lehet a központ, mert a központ minden terminállal össze van kötve, így a központ a jelölt szomszédai között van. Ha a jelöltnek csak egy szomszédja van, az a szomszéd biztosan a központ. Egyébként a következő jelöltet a még nem vizsgált nem összekötött párok közül választjuk: a leveles terminál (amely csak a központtal van összekötve) mindig ilyen pár, így a második végigkérdezés után a központ megtalálható. A korábbi kérdések eredményeit tároljuk, hogy egy párt ne kérdezzünk meg kétszer. A leveles központ-szerkezetben a teljes kérdésszám legfeljebb 2N-3.
*/
/*
Hint 1: || Ha egy terminál nem a központ, akkor van hozzá nem kötött terminál, és a központ biztosan össze van kötve vele. Egy jelölt összes kérdésével eldöntheted, hogy ő-e a központ. ||
Hint 2: || Ha a jelölt csak egyetlen másik terminállal van összekötve, akkor az a terminál a központ. Ha van nem összekötött párja, a következő jelöltet a nem összekötött párjai közül válaszd, mert a leveles terminál ilyen. ||
Hint 3: || Tárold el a már feltett kérdések eredményét, hogy ugyanazt a párt ne kérdezd meg kétszer; így a második jelölt végigkérdezése csak az új párokat teszi ki. ||
*/
#include <bits/stdc++.h>
#include "tudakozo.h"
using namespace std;

int main() {
    int N = hany();
    map<int, vector<signed char>> rows;   // a már végigkérdezett jelöltek sorai (-1: ismeretlen)

    auto ask = [&](int x, int y) -> int {
        if (x == y) return 1;
        auto it = rows.find(x);
        if (it != rows.end()) return it->second[y];
        it = rows.find(y);
        if (it != rows.end()) return it->second[x];
        return kerdes(x, y);
    };

    int cand = 1;
    vector<char> scanned(N + 1, 0);
    while (true) {
        vector<signed char> row(N + 1, -1);
        row[cand] = 1;
        for (int y = 1; y <= N; y++)
            if (y != cand) row[y] = (signed char)ask(cand, y);
        rows[cand] = row;
        scanned[cand] = 1;

        int zeros = 0, ones = 0, oneNb = -1;
        for (int y = 1; y <= N; y++) {
            if (y == cand) continue;
            if (row[y] == 0) zeros++;
            else { ones++; oneNb = y; }
        }
        if (zeros == 0) {                 // mindenkivel össze van kötve: ő a központ
            megoldas(cand);
            return 0;
        }
        if (ones == 1) {                  // csak egy szomszéd: az a központ
            megoldas(oneNb);
            return 0;
        }

        int next = -1;                    // következő jelölt: egy nem összekötött, még nem vizsgált pár
        for (int y = 1; y <= N && next == -1; y++)
            if (row[y] == 0 && !scanned[y]) next = y;
        for (int y = 1; y <= N && next == -1; y++)
            if (row[y] == 1 && !scanned[y]) next = y;
        if (next == -1) {                 // elvileg nem fordul elő
            megoldas(cand);
            return 0;
        }
        cand = next;
    }
    return 0;
}
