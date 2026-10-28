/*
Megoldás lényege:
A nevezéseket időrendben olvassuk, és közben futó összegben nyilvántartjuk a résztvevők számát.
Az első olyan nevezésnél, ahol ez az összeg eléri a 10 000 főt, kiírjuk a sorszámot; ha ez sosem történik meg, a válasz -1.
A helységnév szóközt is tartalmazhat, ezért sorként olvassuk be, a válaszhoz nem használjuk.
Időigény O(N), mert minden nevezést egyszer dolgozunk fel.
*/
/*
Hint 1: || Nem kell minden adatot eltárolni: elég az eddigi résztvevők összegét követni, és az első alkalommal, amikor eléri a 10 000-et, kiírni a sorszámot. ||
Hint 2: || A helységnév külön sor, akár szóközzel is: getline-nal olvasd, utána a lélekszám és a résztvevők száma következik két szóközzel elválasztott számként. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long sum = 0;
    int answer = -1;
    for (int i = 1; i <= n; i++) {
        string name;
        long long population, participants;
        cin >> ws;
        getline(cin, name);
        cin >> population >> participants;
        sum += participants;
        if (answer == -1 && sum >= 10000) {
            answer = i;
        }
    }

    cout << answer << "\n";
    return 0;
}
