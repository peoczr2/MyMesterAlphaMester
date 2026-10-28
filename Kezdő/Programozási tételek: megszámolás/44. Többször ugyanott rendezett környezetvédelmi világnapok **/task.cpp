/*
Megoldás lényege:
Az évszámok a döntéshez nem fontosak: csak azt kell tudni, hogy egy-egy ország (sorszám szerint) hány rendezvénynek adott otthont. Egy N+1 elemű darabszám-tömbben minden rendezvénynél a rendező sorszámához tartozó elemet növeljük, kivéve, ha a rendező ismeretlen (S = 0), mert ezeket a feladat nem veszi figyelembe. A végén azokat az országokat számoljuk meg, amelyekben legalább kétszer volt rendezvény. Az időigény O(R), a memóriaigény O(N), ami a korlátok mellett bőven elegendő.
*/
/*
Hint 1: || Nem kell az évszámokkal foglalkozni: csak azt kell számolni, hány rendezvény volt az egyes sorszámú országokban. Az S = 0 rendezőt hagyd ki. ||
Hint 2: || Tarts egy darabszám-tömböt, amelynek indexe az ország sorszáma; a végén azokat az indexeket számold meg, amelyek értéke legalább 2. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, r;
    cin >> n >> r;
    vector<int> db(n + 1, 0);
    for (int i = 0; i < r; i++) {
        int ev, s;
        cin >> ev >> s;
        if (s != 0) db[s]++;
    }
    int darab = 0;
    for (int i = 1; i <= n; i++)
        if (db[i] >= 2) darab++;
    cout << darab << "\n";
    return 0;
}
