/*
Megoldás lényege: a sorozat elemeit egyenként választjuk ki visszalépéses kereséssel, és minden pozícióra
a még nem használt számokat növekvő sorrendben próbáljuk. Mivel a számokat mindig a legkisebbtől a legnagyobbig
járjuk be, a kiírt sorozatok lexikografikusan növekvők lesznek. A használt számokat jelölőtömb tartja nyilván,
így egy elem ellenőrzése O(1). Az időigény O(N!/(N-K)! · K), mert pontosan ennyi sort és számot írunk ki;
a kiírást egy pufferen keresztül végezzük, hogy a nagy kimenet is gyors legyen.
*/
/*
Hint 1: || A sorozat elemei különbözők, tehát egy használt jelölőtömb elég. ||
Hint 2: || Lexikografikus sorrendhez mindig a legkisebb még szabad számot próbáljuk először. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n, k;
int valasztott[10];
bool hasznalt[11];
char buf[1 << 16];
int pos = 0;

void kiir() {
    if (pos > (int)sizeof(buf) - 64) {
        fwrite(buf, 1, pos, stdout);
        pos = 0;
    }
    for (int i = 0; i < k; ++i) {
        if (i) buf[pos++] = ' ';
        if (valasztott[i] >= 10) buf[pos++] = '1';  // N <= 10: a 10 kétjegyű
        buf[pos++] = char('0' + valasztott[i] % 10);
    }
    buf[pos++] = '\n';
}

void dfs(int melyseg) {
    if (melyseg == k) {
        kiir();
        return;
    }
    for (int x = 1; x <= n; ++x) {
        if (hasznalt[x]) continue;
        hasznalt[x] = true;
        valasztott[melyseg] = x;
        dfs(melyseg + 1);
        hasznalt[x] = false;
    }
}

int main() {
    // A bemenet két száma szóközzel vagy vesszővel is elválasztható.
    string s;
    getline(cin, s);
    replace(s.begin(), s.end(), ',', ' ');
    stringstream in(s);
    in >> n >> k;
    dfs(0);
    fwrite(buf, 1, pos, stdout);
    return 0;
}
