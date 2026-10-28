/*
Megoldás lényege:
Minden serpenyőnél eldöntjük, hogy a tojást páratlanszor kell-e megfordítani, vagyis a kezdeti és a cél állapot különbözik-e. Egy lépés az 1. serpenyőtől a k.-ig minden tojást megfordít, ezért a szomszédos serpenyők jelöléseinek eltérését csak a k. és a (k+1). serpenyő közötti határ billenti át.
Akkor vagyunk készen, ha minden határon nincs eltérés, az utolsó serpenyő után pedig képzeletben egy nulla jelölésű serpenyő áll. Így a szükséges lépések száma pontosan azoknak a határoknak a száma, ahol a jelölés eltér. Ez egy bejárással O(N) időben kiszámolható.
*/
/*
Hint 1: || Csak azt figyeld, hol különbözik a kezdeti és a cél állapot: ott a tojást páratlanszor, máshol páros számszor kell megfordítani. ||
Hint 2: || Egy lépés pontosan egy határt billent át: az 1-től k-ig tartó megfordítás a k. és (k+1). serpenyő közötti határon változtat. Számold meg a határokat, ahol a jelölés eltér, és az utolsó serpenyő után képzelj egy nulla jelölésű őrszemet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string kezdeti, cel;
    cin >> n >> kezdeti >> cel;

    // d[i] = 1, ha az i. serpenyőben a kezdeti és a cél állapot különbözik; d[n] = 0 őrszem.
    vector<int> d(n + 1, 0);
    for (int i = 0; i < n; i++) {
        d[i] = (kezdeti[i] != cel[i]) ? 1 : 0;
    }

    int answer = 0;
    for (int i = 0; i < n; i++) {
        if (d[i] != d[i + 1]) {
            answer++;
        }
    }

    cout << answer << "\n";
    return 0;
}
