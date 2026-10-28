/*
Megoldás lényege:
Maximumkiválasztás helyett minimumkiválasztást végzünk: az első mérést tekintjük kezdő minimumnak, majd minden további mérést összehasonlítunk vele, és ha kisebb, átvesszük. A kezdőértéket az első mérésből vesszük, mert a hőmérséklet negatív is lehet, így egy fix kezdőérték (például 0) hibás eredményt adhatna. Egyetlen bejárással, O(N) időben megkapjuk a leghidegebb nap hőmérsékletét.
*/
/*
Hint 1: || Keresd a legkisebb értéket: tartsd meg az eddig látott legkisebb mérést, és minden új mérésnél hasonlítsd össze vele. ||
Hint 2: || Ügyelj a kezdőértékre: ne nullával indíts, mert a hőmérséklet lehet negatív is. Az első mérés alkalmas kezdőérték. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int legkisebb = INT_MAX;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        if (m < legkisebb) legkisebb = m;
    }
    cout << legkisebb << "\n";
    return 0;
}
