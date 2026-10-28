/*
Megoldás lényege:
Egy madárfaj akkor megfelelő, ha minden olyan helységben előfordult, ahol volt bármilyen madár. Minden faj jelzőjét igazra állítjuk, majd soronként haladva minden olyan, madarat tartalmazó helységnél, ahol egy faj nem volt jelen, a faj jelzőjét hamisra állítjuk. A megmaradt fajok közül az első sorszámát írjuk ki, ha nincs ilyen, akkor 0-t. A futásidő O(M·N), a memóriaigény O(N), mert a sorokat egyenként olvassuk.
*/
/*
Hint 1: || Az üres helységek (ahol nem volt madár) nem befolyásolják az eredményt, ezért csak a madarat tartalmazó helységeket vizsgáld. ||
Hint 2: || Tarts minden fajról egy igaz/hamis jelzőt, amely kezdetben igaz. Egy helység átolvasásakor minden olyan fajnál, amelyből ott nem láttak egyet, állítsd a jelzőt hamisra. Az első igaz jelzésű faj sorszáma lesz a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N;
    cin >> M >> N;
    vector<bool> jelolt(N, true);
    for (int i = 0; i < M; ++i) {
        vector<int> sor(N);
        bool vanMadar = false;
        for (int j = 0; j < N; ++j) {
            cin >> sor[j];
            if (sor[j] > 0) vanMadar = true;
        }
        if (!vanMadar) continue;
        for (int j = 0; j < N; ++j)
            if (sor[j] == 0) jelolt[j] = false;
    }

    int valasz = 0;
    for (int j = 0; j < N; ++j)
        if (jelolt[j]) {
            valasz = j + 1;
            break;
        }

    cout << valasz << '\n';
    return 0;
}
