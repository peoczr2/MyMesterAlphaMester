/*
Megoldás lényege:
Minden számjegy morzekódja pontosan öt jelből áll, ezért a teljes morzekódot balról jobbra haladva, 5 karakteres darabokra vágva minden darab egyetlen számjegynek felel meg. A 0–9 számjegyek kódjait egy tízelemű tömbben tároljuk, és minden darabot ezzel vetünk össze; az egyező számjegyet a végeredmény végére fűzzük. A számot szövegként írjuk ki, így a számjegyek sorrendje változatlan marad. A program a bemenet hosszával arányos időben fut.
*/
/*
Hint 1: || Vizsgáld meg, hány jelből áll egy számjegy morzekódja: a táblázatban minden kód ugyanolyan hosszú, így nem kell elválasztójel. ||
Hint 2: || Ha a kód hossza állandó, a bemenetet 5 karakterenként daraboljuk, és minden darabot a 0–9 kódtáblázattal hasonlítunk össze. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    // A 0–9 számjegyek morzekódja, pontosan 5 jel hosszú.
    const vector<string> code = {
        "-----", ".----", "..---", "...--", "....-",
        ".....", "-....", "--...", "---..", "----."
    };

    string morse;
    cin >> morse;

    string number;
    for (size_t start = 0; start + 5 <= morse.size(); start += 5) {
        string piece = morse.substr(start, 5);
        for (int digit = 0; digit <= 9; ++digit) {
            if (piece == code[digit]) {
                number += char('0' + digit);
            }
        }
    }

    cout << number << '\n';
    return 0;
}
