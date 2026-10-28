/*
Megoldás lényege:
A kódban az első számjegytől való eltérések előtagösszegét számoljuk: a + jel +1, a 0 jel 0, a - jel -1. Ha az első számjegy x, akkor a j-edik számjegy x plusz ez az eltérés. A kód akkor állítható elő, ha van olyan x, amelyre x legalább 1 (N+1 jegyű szám), és minden számjegy 0 és 9 közé esik, azaz x >= 1, x + mn >= 0 és x + mx <= 9, ahol mn és mx az eltérések minimuma és maximuma. A lehetséges x-ek egy intervallumot alkotnak; a legkisebb számot a legkisebb x, a legnagyobbat a legnagyobb x adja, mert az első számjegy határozza meg a sorrendet. Az idő O(N).
*/
/*
Hint 1: || Az első számjegy ismeretében minden további számjegy egyértelmű: a + jel eggyel nagyobb, a 0 ugyanaz, a - jel eggyel kisebb az előzőnél. Számold ki, mennyivel térhet el a legalacsonyabb és a legmagasabb számjegy a kezdő számjegytől. ||
Hint 2: || A kezdő számjegy csak akkor jó, ha minden számjegy 0 és 9 közé esik, és a kezdő számjegy nem lehet 0, hiszen N+1 jegyű számot keresünk. Ha nincs ilyen kezdő számjegy, a válasz ROSSZ. ||
Hint 3: || A legkisebb szám a megengedett legkisebb, a legnagyobb a megengedett legnagyobb kezdő számjegyből indul; a többi számjegyet egyetlen bejárással tudod karakterenként felépíteni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string code;
    cin >> n >> code;

    // cur: az eltérés az első számjegytől; mn és mx ennek minimuma és maximuma
    int cur = 0, mn = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        if (code[i] == '+') cur++;
        else if (code[i] == '-') cur--;
        mn = min(mn, cur);
        mx = max(mx, cur);
    }

    // az első számjegy x: x >= 1, x + mn >= 0, x + mx <= 9
    int lo = max(1, -mn), hi = 9 - mx;
    if (lo > hi) {
        cout << "ROSSZ\n";
        return 0;
    }

    for (int x : {lo, hi}) {
        string num(n + 1, '0');
        int d = x;
        num[0] = char('0' + d);
        for (int i = 0; i < n; i++) {
            if (code[i] == '+') d++;
            else if (code[i] == '-') d--;
            num[i + 1] = char('0' + d);
        }
        cout << num << "\n";
    }
    return 0;
}
