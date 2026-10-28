/*
Megoldás lényege:
A szavak lexikografikus (ábécé szerinti) sorrendben követik egymást, és egy szó közvetlenül a saját prefixe után következik. Ezért a rákövetkező szó két esetből adódik: ha S után még maradt betű, akkor S-hez fűzzük a legkisebb maradék betűt; ha nem maradt, akkor S-ben a legutolsó olyan pozíciót keressük, ahol a prefix elhasználása után még van nála nagyobb betű, ott ezt írjuk a helyére, és az előtte álló prefixet megtartjuk.
Az előző szó szimmetrikus: az utolsó pozícióban keresünk nála kisebb, még elérhető betűt, és a maradék betűket csökkenő sorrendben fűzzük utána; ha ilyen nincs, S utolsó betű nélküli prefixe az előző szó. Ha nincs következő szó, a ciklikus szabály szerint az ábécé legkisebb szava (egyetlen betű) a válasz; ha nincs előző szó, akkor az összes betűből csökkenő sorrendben összerakott, legnagyobb szó.
A betűk darabszámát 26 elemű tömbben tartjuk nyilván, így minden lépés O(26 · |S|), ami a feladat méreteihez bőven belefér.
*/
/*
Hint 1: || A szavak sorrendjében egy szó közvetlenül a saját prefixe után áll. Ha S után még maradt elérhető betű, akkor a következő szó S és a legkisebb maradék betű összefűzése. ||
Hint 2: || Ha S-ből már nem marad betű, egy pozíción kell felfelé lépned: keresd meg a legnagyobb k indexet, amelyre az S[0..k-1] előtag elhasználása után még van S[k]-nál nagyobb betű. Ekkor a válasz S[0..k-1] és a legkisebb ilyen betű összefűzése. ||
Hint 3: || Az előző szó tükörképe: az S utolsó betűjénél kisebb, még elérhető betűt keresd, és az elhasznált betűk nélküli maradékot csökkenő sorrendben fűzd utána. Ha ilyen betű nincs, az S utolsó betű nélküli előtagja lesz az előző szó. ||
Hint 4: || A ciklikus szabály miatt az ábécé első szavának megelőzője a legnagyobb lehetséges szó, vagyis az összes betű csökkenő sorrendben, a legutolsóé pedig a legkisebb betű. Tartsd nyilván a 26 betű darabszámát, és az előtagok elhasználását egyetlen tömb módosításával kövesd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    array<long long, 26> cnt{};
    for (int i = 0; i < n; i++) {
        char ch;
        cin >> ch;
        cnt[ch - 'a']++;
    }

    string s;
    cin >> s;
    int m = s.size();

    // Az S előtt: az S[0..m-2] előtag elhasználása után maradt betűk.
    array<long long, 26> rem = cnt;
    for (int i = 0; i + 1 < m; i++) rem[s[i] - 'a']--;

    // Előző szó (ciklikusan).
    string prev;
    {
        int last = s[m - 1] - 'a';
        int y = -1;
        for (int c = last - 1; c >= 0; c--) {
            if (rem[c] > 0) {
                y = c;
                break;
            }
        }
        if (y >= 0) {
            prev = s.substr(0, m - 1);
            prev.push_back('a' + y);
            rem[y]--;
            for (int c = 25; c >= 0; c--) prev.append(rem[c], 'a' + c);
        } else if (m >= 2) {
            prev = s.substr(0, m - 1);
        } else {
            for (int c = 25; c >= 0; c--) prev.append(cnt[c], 'a' + c);
        }
    }

    // Következő szó (ciklikusan).
    string next;
    array<long long, 26> left = cnt;
    for (char ch : s) left[ch - 'a']--;
    long long leftTotal = 0;
    for (int c = 0; c < 26; c++) leftTotal += left[c];

    if (leftTotal > 0) {
        int x = 0;
        while (left[x] == 0) x++;
        next = s + char('a' + x);
    } else {
        // Nincs több betű: a legnagyobb k-t keressük, ahol S[k]-nál nagyobb betű még elérhető.
        // acc = az S[k..m-1] betűi, ez megegyezik a cnt - S[0..k-1] maradékkal.
        array<long long, 26> acc{};
        bool found = false;
        for (int k = m - 1; k >= 0 && !found; k--) {
            acc[s[k] - 'a']++;
            for (int y = s[k] - 'a' + 1; y < 26; y++) {
                if (acc[y] > 0) {
                    next = s.substr(0, k) + char('a' + y);
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            int x = 0;
            while (cnt[x] == 0) x++;
            next = string(1, char('a' + x));
        }
    }

    cout << prev << "\n" << next << "\n";
    return 0;
}
