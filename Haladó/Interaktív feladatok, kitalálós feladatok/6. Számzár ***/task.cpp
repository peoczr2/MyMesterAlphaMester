/*
Megoldás lényege: legyen s_i a chip állapota a jelszó első i jegye után. Az N+2 állapot miatt vagy van két egyező s_i = s_k (i < k), és akkor a p[0..i) + p[k..N) szó már nyit, vagy minden s_i különbözik, és a maradék egy állapot (d) nyelőként viselkedik. Ez utóbbi esetben egy másik nyitó szó csak úgy létezhet, hogy egy rossz számjegy után a láncra ér vissza, vagy d-ből indulva nyit; ezt a p[0..i) + c + p[k..N) és a c + e + p[k..N) alakú szavakkal teszteljük. A keresés minden i, c, k párra kimerítő, ezért ha egyik próba sem nyit, a jelszó az egyetlen nyitó szó, és nyit(p) hívandó. Az időigény kb. 9·N² kérdés, mindegyik O(N) hosszú, azaz O(N³), N = 100 esetén kb. 10^7 lépés.
*/
/*
Hint 1: || Ne a chip belső szerkezetét próbáld felderíteni, hanem a jelszó prefixeiből kiindulva keress olyan szót, amely nyit, de nem egyezik a jelszóval. ||
Hint 2: || Ha két prefixállapot egyezik, a p[0..i) + p[k..N) szó nyit. Ha egy rossz számjegy a láncra visszavisz, akkor a p[0..i) + c + p[k..N) szó nyit. ||
Hint 3: || Ha ezek nem nyitnak, a maradék egy állapot (nyelő). Ebből egy c számjegy (c != p[0]) után egy e számjeggyel és a jelszó egy suffixével (c + e + p[k..N)) kell próbálkozni. ||
*/
#include "zar.h"
#include <bits/stdc++.h>
using namespace std;

// Igaz, ha a w szó resetA() után nyitó állapotba viszi a zárat.
static bool nyitSzo(const string& w) {
    resetA();
    for (char ch : w) be(ch);
    return nyito();
}

int main() {
    string p = jelszo();
    int n = (int)p.size();

    // 1. Két prefixállapot egyezése: p[0..i) + p[k..n), i < k.
    for (int i = 0; i < n; i++)
        for (int k = i + 1; k <= n; k++) {
            string w = p.substr(0, i) + p.substr(k);
            if (nyitSzo(w)) nyit(w);
        }

    // 2. Rossz számjegy a jelszó-láncra vezet: p[0..i) + c + p[k..n).
    for (int i = 0; i <= n; i++)
        for (char c = '0'; c <= '9'; c++) {
            if (i < n && c == p[i]) continue;
            for (int k = 0; k <= n; k++) {
                string w = p.substr(0, i) + c + p.substr(k);
                if (nyitSzo(w)) nyit(w);
            }
        }

    // 3. Nyelő állapot: c (c != p[0]), majd e, majd a jelszó egy suffixe.
    string c0(1, (n > 0 && p[0] == '0') ? '1' : '0');
    if (nyitSzo(c0)) nyit(c0);
    for (char e = '0'; e <= '9'; e++)
        for (int k = 0; k <= n; k++) {
            string w = c0 + e + p.substr(k);
            if (nyitSzo(w)) nyit(w);
        }

    nyit(p);
    return 0;
}
