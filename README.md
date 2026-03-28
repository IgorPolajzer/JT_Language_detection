# Jezikovne tehnologije - Klasifikacija jezika dokumentov

Pri tej nalogi sem po vzoru članka [N-Gram-Based Text Categorization](https://dsacl3-2019.github.io/materials/CavnarTrenkle.pdf) implementiral preprost
klasifikator dokumentov glede na njihov jezik. Princip temelji na izdelavi profilov za izbrane jezike, v mojem primeru so to: ***slovenščina, angleščina, španščina, nemščina, hrvaščina***.

Delovanje klasifikatorja je dvoplastno, vsebuje fazo učenja in fazo klasifikacije.

## Faza učenja
V fazi učenja za izbrane jezike naložimo ***učni material*** ter izdelamo profile za vsak posamezen jezik.

Za učni material sem zbral besedila o posameznih državah z Wikipedije (npr. za profil slovenščine sem uporabil besedilo na https://en.wikipedia.org/wiki/Slovenia),
ter jih shranil v mapo [test_files](https://github.com/IgorPolajzer/JT_Language_detection/tree/master/data/test_files).

## Faza klasifikacije
V tej fazi v program vnesemo poljuben tekstovni dokument,v moji implementaciji so ti prisotni v [test_files](https://github.com/IgorPolajzer/JT_Language_detection/tree/master/data/test_files), program pa ga klasificira glede na izvorni jezik.

Sam potek klasifikacije poteka tako, da za vneseni dokument ustvari profil ter med njim in vsemi klasifikacijskimi profili programa izmeri razdaljo.

Samo merjenje razdalje je zelo preprosto, program zgolj izmeri razliko med mestom uvrstitve tokenov med profiloma, na koncu pa vse te razlike sešteje.
Klasifikacijski profil, ki ima najmanjšo razdaljo glede na profil podanega dokumenta, klasificira dokument.

## Eksperimenti
Za testiranje sem poiskal besedila z novinarskih spletnih mest posameznih jezikov (npr. za slovenščino sem izbral https://www.rtvslo.si/).
Program je uspešnoklasificiral vse jezike.

### Klasifikacije glede na kombinacije N-gramov:
- 1 >= N <= 5 -> uspešna klasifikacija
- 1 >= N <= 3 -> uspešna klasifikacija
- 2 >= N <= 3 -> uspešna klasifikacija
- 1 >= N <= 2 -> neuspešna klasifikacija
  - Hrvaščina je bila klasificirana kot slovenščina
  - Španščina je bila klasificirana kot slovenščina

Ugotovimo da tovrstni klasifikatorji delujejo najbolje nad N-grami večjimi od 2.

### Klasifikacije glede na velikost profilov:
Pri tem eksperimentu sem testiral kako vpliva dolžina **materiala za profil** (besedilo glede na katerega je izgrajen profil) 
na klasifikacijo besedila. Pri tem eksperimentu sem imel interval N-ja nastavljen na 1 >= N <= 5.

Pravtko je potrebno omeniti da metrika "število vrstic teksta" ni njaboljša, saj se lahko vrstice razlikujejo v njihovem vsebovanju števila črk.

- dolžina materiala ≈ 500 vrstic -> uspešna klasifikacija
- dolžina materiala ≈ 250 vrstic -> uspešna klasifikacija
- dolžina materiala ≈ 100 vrstic -> uspešna klasifikacija
- dolžina materiala ≈ 50 vrstic -> neuspešna klasifikacija
    - Španščina je bila klasificirana kot angleščina
    - Nemščina je bila klasificirana kot angleščina

Ugotovimo, da dolžina materiala pravtako vpliva na učinkovitost klasifikacije. Pomembno je da so profili ustvarjeni iz dovolj dolgega materiala.

Ugotovil sem tudi da je zelo pomembno, da so učni materiali za posamezne jezike približno enako dolgi. V nasprotnem primeru pride do pristranskosti zaradi neuravnoteženih podatkov, kar lahko vodi do napačnih klasifikacij pri podobnih jezikih.
To sem opazil pri klasifikaciji hrvaščine, kjer je bil učni material za slovenščino približno dvakrat krajši kot za hrvaščino. Posledično je sistem hrvaški jezik napačno klasificiral kot slovenščino. Ko sem  dolžino materiala prilagodil je zadeva delovala kot pričakovano.

### Različen pribitek neujemanja
Pri tem eksperimentu sem testiral kako na klasifikacijo besedila vpliva **pribitek v primeru neujemanja** (out-of-place). 
Pri tem sem imel interval N-ja nastavljen na 1 >= N <= 5.

- out-of-place = dolžina profila -> uspešna klasifikacija
- out-of-place = dolžina profila / 2 -> uspešna klasifikacija
- out-of-place = dolžina profila / 5 -> uspešna klasifikacija
- out-of-place = dolžina profila / 10 -> uspešna klasifikacija
- out-of-place = dolžina profila / 10 -> uspešna klasifikacija
- out-of-place = dolžina profila / 25 -> uspešna klasifikacija 
- out-of-place = dolžina profila / 50 -> neuspešna klasifikacija
  - Hrvaščina je bila klasificirana kot slovenščina

Ugotovimo da je za zanseljivo klasifikacijo potreben dovolj velik **pribitek v primeru neujemanja** ki mora znašati manj kot dolžina profila / 25. 