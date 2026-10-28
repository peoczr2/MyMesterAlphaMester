/*
Megoldás lényege:
Egyetlen bejárással végigmegyünk a napokon, és minden olyan nap sorszámát eltároljuk,
amelyen a hőmérséklet nagyobb a K foknál. A sorszámok a bejárás sorrendjében, tehát már
növekvő sorrendben kerülnek a vektorba, így nincs szükség rendezésre. A kiíráskor előbb
a darabszám (a vektor mérete) kerül az első sorba, utána a sorszámok. Az időigény O(N),
ami N legfeljebb 100 mellett bőven belefér az időkorlátba.
*/
/*
Hint 1: || Járd végig a napokat egymás után, és minden napnál csak azt döntsd el, hogy a hőmérséklet nagyobb-e K-nál. ||
Hint 2: || A megfelelő napok sorszámait gyűjtsd egy vektorba. A kiíráskor először a vektor mérete (a darabszám) kerüljön ki, utána a sorszámok. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> melegebb;
    for (int i = 1; i <= n; i++) {
        int h;
        cin >> h;
        if (h > k) {
            melegebb.push_back(i);
        }
    }

    cout << melegebb.size();
    for (int nap : melegebb) {
        cout << " " << nap;
    }
    cout << "\n";
    return 0;
}
