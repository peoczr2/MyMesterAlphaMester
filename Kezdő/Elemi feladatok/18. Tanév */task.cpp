/*
Megoldás lényege:
A tanév napjait szeptember 1-jétől számított sorszámmal (eltolással) azonosítjuk, a hét napját pedig a megadott szeptember 1-jei napból maradékosan számoljuk. Minden szünet a hetekhez igazodik: megkeressük a dátumot tartalmazó hét hétfőjét, és ebből kapjuk a szünet előtti pénteket (hétfő − 3) és a szünet utáni első hétfőt (hétfő + 7, a téli szünetnél + 14). A tavaszi szünet a húsvétvasárnapot tartalmazó hét, húsvéthétfő és a hétfői újrakezdés helyett a kedd (húsvét + 2). Az első tanítási nap a szeptember első hétfője, az utolsó a június második péntek. A hónapok hosszát (szökőévben februárral) táblázatban tároljuk. Az időigény állandó.
*/
/*
Hint 1: || Minden dátumot érdemes egy közös sorszámmal kezelni, amely szeptember 1-jétől indul. A hét napját ebből a sorszámból és a szeptember 1-jei napból kapjuk meg maradékszámítással. ||
Hint 2: || A szünetek mindig hétfőhöz kötöttek: keresd meg a dátumot tartalmazó hét hétfőjét, és onnan számold a péntek (hétfő − 3) és a következő hétfő határokat. A június második pénteke az első péntek + 7. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Honap {
    int ev, ho, hossz;
};

vector<Honap> honapok;   // szeptembertől júniusig
int elsoNapHet;          // szeptember 1. hete: 0 = hétfő, 6 = vasárnap

// A dátum sorszáma (0 = szeptember 1.)
int sorszam(int ev, int ho, int nap) {
    int off = 0;
    for (const Honap &h : honapok) {
        if (h.ev == ev && h.ho == ho) return off + nap - 1;
        off += h.hossz;
    }
    return -1;
}

// A sorszámhoz tartozó hét napja: 0 = hétfő, ..., 6 = vasárnap
int hetNapja(int s) {
    return (elsoNapHet + s) % 7;
}

// Kiírás „E.H.N.” formában
void kiir(int s) {
    for (const Honap &h : honapok) {
        if (s < h.hossz) {
            cout << h.ev << '.' << h.ho << '.' << s + 1 << ".\n";
            return;
        }
        s -= h.hossz;
    }
}

int main() {
    int ev, elsoNap, husvetHo, husvetNap;
    cin >> ev >> elsoNap >> husvetHo >> husvetNap;
    elsoNapHet = elsoNap - 1;

    bool szokoev = ((ev + 1) % 4 == 0 && (ev + 1) % 100 != 0) || (ev + 1) % 400 == 0;
    honapok = {
        {ev, 9, 30}, {ev, 10, 31}, {ev, 11, 30}, {ev, 12, 31},
        {ev + 1, 1, 31}, {ev + 1, 2, szokoev ? 29 : 28}, {ev + 1, 3, 31},
        {ev + 1, 4, 30}, {ev + 1, 5, 31}, {ev + 1, 6, 30}
    };

    // Tanévkezdés: szeptember első hétfője
    int kezdes = (7 - elsoNapHet) % 7;

    // Őszi szünet: az október 23-át tartalmazó hét hétfője
    int okt23 = sorszam(ev, 10, 23);
    int oszHet = okt23 - hetNapja(okt23);

    // Téli szünet: a december 25-öt tartalmazó hét hétfője, kétheti szünet
    int karacsony = sorszam(ev, 12, 25);
    int telHet = karacsony - hetNapja(karacsony);

    // Tavaszi szünet: a húsvétvasárnapot tartalmazó hét hétfője
    int husvet = sorszam(ev + 1, husvetHo, husvetNap);
    int husHet = husvet - hetNapja(husvet);

    // Tanév vége: június második péntekje
    int junius1 = sorszam(ev + 1, 6, 1);
    int elsoPentek = junius1 + (4 - hetNapja(junius1) + 7) % 7;
    int vege = elsoPentek + 7;

    kiir(kezdes);
    kiir(oszHet - 3);
    kiir(oszHet + 7);
    kiir(telHet - 3);
    kiir(telHet + 14);
    kiir(husHet - 3);
    kiir(husvet + 2);
    kiir(vege);
    return 0;
}
