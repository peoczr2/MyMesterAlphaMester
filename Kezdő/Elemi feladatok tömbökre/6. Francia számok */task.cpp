/*
Megoldás lényege:
A 0 és 19 közötti számok önálló nevét táblázatban tároljuk. A 20 és 69 közötti számoknál a tízes nevét követi az egyes, kötőjellel, a 21, 31, 41, 51 és 61 esetén pedig „et un” áll; a 20, 30, 40, 50 és 60 csak a tízes nevét kapja. A 70–79 számok a 60-ra épülnek: a 71 kivétel („soixante et onze”), a többi „soixante-” után a 10–19 közötti név következik. A 80 alakja „quatre-vingts”, a 81–99 számoknál pedig „quatre-vingt-” után az 1–19 közötti név áll. A szám a megfelelő ágra kerül, így a program állandó idejű.
*/
/*
Hint 1: || Az egyjegyű és a 10–19 közötti számoknak önálló nevük van, ezért tárold őket táblázatban. A többi szám neve tízesből és egyesből áll, így elég a számot tízesekre és egyesekre bontanod. ||
Hint 2: || Figyelj a szabályok eltéréseire: 21, 31, 41, 51 és 61 esetén „et un” áll, 71 esetén „et onze”. A 80 alakja „quatre-vingts”, a 81 és a feletti számoknál pedig „quatre-vingt-” után az 1–19 közötti számok neve következik. ||
*/
#include <bits/stdc++.h>
using namespace std;

// 0–19 önálló nevei
const string NEVEK[20] = {
    "zéro", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf",
    "dix", "onze", "douze", "treize", "quatorze", "quinze", "seize",
    "dix-sept", "dix-huit", "dix-neuf"
};

int main() {
    int n;
    cin >> n;

    string ki;
    if (n < 20) {
        ki = NEVEK[n];
    } else if (n < 70) {
        // A tízesek neve: 20, 30, 40, 50, 60
        const string tizesek[7] = {"", "", "vingt", "trente", "quarante", "cinquante", "soixante"};
        int t = n / 10;
        int e = n % 10;
        ki = tizesek[t];
        if (e == 1) ki += " et un";
        else if (e > 1) ki += "-" + NEVEK[e];
    } else if (n < 80) {
        if (n == 71) ki = "soixante et onze";
        else ki = "soixante-" + NEVEK[n - 60];
    } else if (n == 80) {
        ki = "quatre-vingts";
    } else {
        ki = "quatre-vingt-" + NEVEK[n - 80];
    }

    cout << ki << '\n';
    return 0;
}
