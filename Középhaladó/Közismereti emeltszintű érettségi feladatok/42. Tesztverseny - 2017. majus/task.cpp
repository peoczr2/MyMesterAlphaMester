/*
Megoldás lényege:
A versenyzők válaszait és a helyes megoldást karakterláncokban tároljuk, így egy kérdés eltalálása a két string azonos helyén álló karakterének összehasonlításával dönthető el.
Az 1. és a 2. részfeladatban a megadott kódú versenyző válaszai, illetve a helyes megoldás alá írt „+” jeles sor állítható elő.
A 3. részfeladatban a J-edik karakterek egyezését számoljuk meg, a százalékot egész aritmetikával, két tizedesjegyre, félre felfelé kerekítve írjuk ki.
A 4. részfeladatban a q-adik kérdés pontja 3 plusz azoknak a ponthatároknak a száma, amelyek legfeljebb q, így a versenyzők pontszámát ezek összegeként kapjuk.
Az 5. részfeladatban a pontszámok három legnagyobb különböző értékét keressük meg, és a bemeneti sorrendet megtartó stabil rendezéssel, csökkenő pontszám szerint írjuk ki a hozzájuk tartozó versenyzőket.
Az időigény O(N*K + N log N), ami a 0.1 mp-es korláton belül bőven marad.
*/
/*
Hint 1: || Egy kérdés eltalálása azt jelenti, hogy a versenyző és a helyes megoldás ugyanazon pozícióján ugyanaz a betű áll, így minden részfeladat ebből a két stringből számolható. ||
Hint 2: || A pontszámnál a ponthatárok száma dönt: a q-adik kérdés pontját 3-ról kezdve növeld eggyel minden olyan ponthatárnál, amely nem nagyobb q-nál. ||
Hint 3: || Az 5. részfeladatban a pontszámok különböző értékeit csökkenő sorba rendezd, a három legnagyobb értéket tartsd meg, és a versenyzőket a bemeneti sorrendben, stabil rendezéssel írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    string correct;
    cin >> correct;

    string qcode;
    int j;
    cin >> qcode >> j;

    int l;
    cin >> l;
    vector<int> limit(l);
    for (int i = 0; i < l; i++) cin >> limit[i];

    vector<string> code(n), ans(n);
    for (int i = 0; i < n; i++) cin >> code[i] >> ans[i];

    int me = 0;
    for (int i = 0; i < n; i++) {
        if (code[i] == qcode) {
            me = i;
            break;
        }
    }

    // 1. részfeladat: a megadott versenyző válaszai
    cout << "#\n" << ans[me] << "\n";

    // 2. részfeladat: a helyes megoldás és a találatok jelölése
    cout << "#\n" << correct << "\n";
    for (int q = 0; q < k; q++) cout << (ans[me][q] == correct[q] ? '+' : ' ');
    cout << "\n";

    // 3. részfeladat: a J-edik kérdésre helyes választ adók száma és aránya
    int good = 0;
    for (int i = 0; i < n; i++)
        if (ans[i][j - 1] == correct[j - 1]) good++;
    long long hundredths = (2LL * good * 10000 + n) / (2LL * n);
    cout << "#\n" << good << "\n";
    cout << hundredths / 100 << "." << setw(2) << setfill('0') << hundredths % 100 << setfill(' ') << "%\n";

    // 4. részfeladat: kérdésenkénti pontok, majd a versenyzők pontszámai
    vector<int> pts(k);
    for (int q = 1; q <= k; q++) {
        int p = 3;
        for (int lim : limit)
            if (lim <= q) p++;
        pts[q - 1] = p;
    }
    vector<int> score(n, 0);
    for (int i = 0; i < n; i++)
        for (int q = 0; q < k; q++)
            if (ans[i][q] == correct[q]) score[i] += pts[q];

    cout << "#\n";
    for (int i = 0; i < n; i++) cout << code[i] << " " << score[i] << "\n";

    // 5. részfeladat: a három legmagasabb különböző pontszámhoz tartozó versenyzők
    vector<int> top = score;
    sort(top.begin(), top.end(), greater<int>());
    top.erase(unique(top.begin(), top.end()), top.end());
    if (top.size() > 3) top.resize(3);

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    stable_sort(order.begin(), order.end(), [&](int a, int b) { return score[a] > score[b]; });

    cout << "#\n";
    for (int i : order) {
        auto it = find(top.begin(), top.end(), score[i]);
        if (it != top.end()) cout << (it - top.begin()) + 1 << " " << score[i] << " " << code[i] << "\n";
    }
    return 0;
}
