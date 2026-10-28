/*
Megoldás lényege: a kifejezést egy sorban olvassuk be, a három részfeladatot egymástól függetlenül ellenőrizzük. Az első részben a nyitó és a záró zárójelek darabszámát vetjük össze. A második részben egy számlálóval haladunk balról jobbra: nyitónál nő, záró zárójelnél csökken; ha negatívba megy, vagy a végén nem nulla, a zárójelek nincsenek megfelelően egymásba ágyazva. A harmadik részben minden műveleti jelet megvizsgálunk: nem állhat a kifejezés szélén, a bal oldali szomszédja csak számjegy vagy zárójel-bezárás, a jobb oldali szomszédja csak számjegy vagy zárójel-nyitás lehet. A kifejezés legfeljebb 200 karakter, így minden ellenőrzés O(L) időben fut. Minden részfeladat eredménye elé egyetlen # sor kerül.
*/
/*
Hint 1: || Mindhárom részfeladathoz elég a kifejezést egyszer végigolvasni, de minden részfeladatra külön eredményt kell kiírni. ||
Hint 2: || A zárójelek egymásba ágyazásához használj egy számlálót: nyitó zárójelnél nő, záró zárójelnél csökken. Ha a számláló valaha negatív lesz, vagy a végén nem nulla, a kifejezés hibás. ||
Hint 3: || Műveleti jelnél nézd meg a bal és a jobb oldali szomszédját, és ellenőrizd, hogy a feladat szerinti karakterkészletbe esnek-e; a kifejezés első és utolsó karaktere nem lehet műveleti jel. ||
*/
#include <bits/stdc++.h>
using namespace std;

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isOp(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int len = s.size();

    // 1. részfeladat: a nyitó és záró zárójelek száma megegyezik-e
    int opens = 0, closes = 0;
    for (char c : s) {
        if (c == '(') opens++;
        else if (c == ')') closes++;
    }
    cout << "#\n";
    cout << (opens == closes ? "Helyes" : "Hiba") << '\n';

    // 2. részfeladat: a zárójelpárok megfelelően egymásba ágyazottak-e
    bool nested = true;
    int balance = 0;
    for (char c : s) {
        if (c == '(') {
            balance++;
        } else if (c == ')') {
            balance--;
            if (balance < 0) {
                nested = false;
                break;
            }
        }
    }
    if (balance != 0) nested = false;
    cout << "#\n";
    cout << (nested ? "Helyes" : "Hiba") << '\n';

    // 3. részfeladat: a műveleti jelek megfelelő helyen állnak-e
    bool opsOk = true;
    for (int i = 0; i < len && opsOk; i++) {
        if (!isOp(s[i])) continue;
        if (i == 0 || i == len - 1) {
            opsOk = false;
            break;
        }
        char before = s[i - 1];
        char after = s[i + 1];
        if (!(isDigit(before) || before == ')')) opsOk = false;
        if (!(isDigit(after) || after == '(')) opsOk = false;
    }
    cout << "#\n";
    cout << (opsOk ? "Helyes" : "Hiba") << '\n';

    return 0;
}
