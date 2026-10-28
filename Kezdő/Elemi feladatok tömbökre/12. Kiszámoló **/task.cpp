/*
Megoldás lényege:
A kör gyerekeit egy tömb tárolja, a tömb elemei a gyerekek sorszámai. A kiszámolás mindig a kezdő indexről indul, így a K-adik gyerek indexe a kezdő index plusz K-1, maradékosan a tömb aktuális méretével. Ezt a gyereket kiírjuk és a tömbből töröljük, majd a következő kiszámolás a törölt hely indexéről indul, amelyet ismét a tömb új mérete szerint kell maradékolni. A ciklus addig fut, amíg legalább két gyerek van, az utolsó megmaradt pedig a tömb egyetlen eleme. Mivel N legfeljebb 10 000, az O(N^2) összes törlés memmozgatásként bőven belefér az időlimitbe.
*/
/*
Hint 1: || Tárold a kör gyerekeit tömbben, és jegyezd meg, melyik indexről indul a következő számolás. A K-adik gyerek indexe ekkor a kezdő index plusz K-1, a tömb aktuális méretével vett maradékként. ||
Hint 2: || Egy gyerek kiesése után töröld a tömbből: a következő számolás a törölt hely indexéről indul, vagyis ugyanaz az index marad, csak az új mérettel vett maradékkal számolunk. Addig ismételd, amíg legalább két gyerek van a körben. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    // a kör gyerekeinek sorszámait tömbben tároljuk
    vector<int> kor(n);
    iota(kor.begin(), kor.end(), 1);

    vector<int> kiesett;
    size_t kezdo = 0;   // az az index, ahonnan a következő kiszámolás indul
    while (kor.size() > 1) {
        size_t i = (kezdo + k - 1) % kor.size();   // a K-adik gyerek indexe
        kiesett.push_back(kor[i]);
        kor.erase(kor.begin() + i);
        kezdo = i % kor.size();                    // a törölt helyen a következő gyerek áll
    }

    for (size_t i = 0; i < kiesett.size(); i++) {
        if (i) cout << ' ';
        cout << kiesett[i];
    }
    cout << "\n" << kor[0] << "\n";
    return 0;
}
