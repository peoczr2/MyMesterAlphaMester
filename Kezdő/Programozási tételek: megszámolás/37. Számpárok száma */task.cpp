/*
Megoldás lényege:
Mivel N legfeljebb 100, az összes (i, j) pár i<j feltétellel egyszerűen végigpróbálható. Két egymásba ágyazott ciklussal minden i-hez a j indexet i+1-től az utolsó elemig futtatjuk, és ha A[i] < A[j], növeljük a számlálót. Az időigény O(N²), ami 100 elemnél legfeljebb 4950 párt jelent; a memóriaigény O(N).
*/
/*
Hint 1: || Mivel N legfeljebb 100, minden i<j párt egyesével meg lehet vizsgálni: két egymásba ágyazott ciklus elég. ||
Hint 2: || A belső ciklus j-t i+1-től indítsa, így csak az i<j párok kerülnek sorra. Ha A[i] < A[j] teljesül, növeld a számlálót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int db = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] < a[j]) db++;
    cout << db << "\n";
    return 0;
}
