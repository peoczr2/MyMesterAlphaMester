/*
Megoldás lényege:
Egy nap akkor kerül a listába, ha minden településen szigorúan melegebb, mint az előző napon. Ezt úgy vizsgáljuk, hogy minden településnél végigmegyünk a napokon, és ha valahol a hőmérséklet nem nő, a nap kiesik. A bemenetet egyszer olvassuk be, a tömb csak a napok jelzőit tárolja. Az idő O(N·M), a memória O(M).
*/
/*
Hint 1: || Egy nap akkor jó, ha *minden* településen nő a hőmérséklet az előző naphoz képest. Elég a rossz napokat kizárni: egyetlen település csökkenése vagy egyenlősége is kizárja a napot. ||
Hint 2: || Két egymást követő napot kell összevetned, ezért soronként az előző értéket tartsd meg. Egy M elemű logikai tömbben jegyezd, melyik nap maradt jó, a végén pedig a jó napok sorszámát (1-től számozva) írd ki egy sorba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // jo[j]: a j. napon (0-tól számozva) minden településen melegebb-e, mint az előző napon
    vector<bool> jo(m, true);
    for (int i = 0; i < n; i++) {
        int elozo;
        cin >> elozo;
        for (int j = 1; j < m; j++) {
            int akt;
            cin >> akt;
            if (akt <= elozo) jo[j] = false;
            elozo = akt;
        }
    }

    vector<int> napok;
    for (int j = 1; j < m; j++)
        if (jo[j]) napok.push_back(j + 1);

    cout << napok.size();
    for (int nap : napok) cout << ' ' << nap;
    cout << '\n';
    return 0;
}
