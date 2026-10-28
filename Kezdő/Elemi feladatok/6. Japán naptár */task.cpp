/*
Megoldás lényege:
Az évek 60 évente ismétlődnek, és 1984 a ciklus első éve, ezért az évszám és 1984 különbségének 60-as maradéka megadja, hányadik évben vagyunk a ciklusban (0-tól számolva). Az évek párosával azonos színűek, így a sorszámot kettővel egész osztva megkapjuk a párt, és ennek 5-tel vett maradéka adja a színt. Az 1984 előtti évekre a negatív maradék elkerülése miatt 60-at adunk a különbséghez a maradékképzés előtt. A művelet ideje konstans.
*/
/*
Hint 1: || Az évek 60 évente ismétlődnek, és 1984 a ciklus első éve. Számold ki az évszám és 1984 különbségének 60-as maradékát: ez mutatja, hányadik évben vagyunk a ciklusban. ||
Hint 2: || Az évek párokban azonos színűek, és öt szín követi egymást. Ha a ciklusbeli sorszámot kettővel egész osztod, megkapod a párt, és annak 5-tel vett maradéka adja a színt. Az 1984 előtti évekre figyelj a negatív maradékra. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int ev;
    cin >> ev;

    // Az évek sorszáma a ciklusban: 0 az 1984-es év, 59 a 2043-as
    int sorszam = ((ev - 1984) % 60 + 60) % 60;

    // Párok szerint: 0 zöld, 1 piros, 2 sárga, 3 fehér, 4 fekete
    int szin = (sorszam / 2) % 5;
    string nevek[5] = {"zold", "piros", "sarga", "feher", "fekete"};

    cout << nevek[szin] << "\n";
    return 0;
}
