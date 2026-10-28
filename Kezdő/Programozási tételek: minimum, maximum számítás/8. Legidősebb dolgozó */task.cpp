/*
Megoldás lényege: Egyetlen menetben haladunk végig a dolgozókon, és mindig az eddig látott legnagyobb koruk fizetését tartjuk meg. Csak szigorúan nagyobb kor esetén cserélünk, így egyenlő kor esetén a korábbi (kisebb sorszámú) dolgozó fizetése marad. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Nem kell eltárolni az összes dolgozót: elég az eddig látott legidősebb kort és a hozzá tartozó fizetést megjegyezni. ||
Hint 2: || Egy új dolgozó csak akkor írja felül az eddigi választ, ha a kora szigorúan nagyobb, különben az eddigi (korábbi sorszámú) marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int bestAge = -1;
    long long bestSalary = 0;
    for (int i = 0; i < n; i++) {
        int k;
        long long f;
        cin >> k >> f;
        if (k > bestAge) {
            bestAge = k;
            bestSalary = f;
        }
    }
    cout << bestSalary << "\n";
    return 0;
}
