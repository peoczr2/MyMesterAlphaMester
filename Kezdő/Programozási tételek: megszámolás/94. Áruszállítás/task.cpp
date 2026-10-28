/*
Megoldás lényege:
Egy szakasz (a j. és a j+1. állomás között) akkor nem üres, ha legalább egy cég szállítmánya átmegy rajta, vagyis Honnan <= j < Hova. Nem kell minden céget minden szakaszra végigvizsgálni: a különbségtömb Honnan helyére +1-et, a Hova helyére -1-et ír, így a prefixösszeg minden j-re megadja, hány cég fedi le a j. szakaszt.
A prefixösszeg nulla értékű szakaszait egyetlen bejárással megszámoljuk. Az időigény O(N+M), ami az N = 1 000 000 állomásra is gyors.
*/
/*
Hint 1: || Egy cég szállítmánya pontosan akkor halad át a j. és (j+1). állomás közötti szakaszon, ha Honnan <= j és j < Hova. ||
Hint 2: || Ne számold végig minden szakaszra minden céget, mert az túl lassú. Használj különbségtömböt: a Honnan indexét növeld, a Hova indexét csökkentsd, majd vedd a prefixösszeget. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> diff(n + 2, 0);
    for (int i = 0; i < m; i++) {
        int honnan, hova;
        cin >> honnan >> hova;
        diff[honnan]++;
        diff[hova]--;
    }

    long long answer = 0;
    int covered = 0;   // a j. szakaszt lefedő cégek száma
    for (int j = 1; j < n; j++) {
        covered += diff[j];
        if (covered == 0) {
            answer++;
        }
    }

    cout << answer << "\n";
    return 0;
}
