# Jezikovne tehnologije - Klasifikacija jezika dokumentov

Pri tej nalogi sem po vzoru članka [N-Gram-Based Text Categorization](https://dsacl3-2019.github.io/materials/CavnarTrenkle.pdf) implementiral preprost
klasifikator dokumentov glede na njihov jezik. Princip temelji na izdelavi profilov za izbrane jezike, v mojem primeru so to:
- slovenščina,
- angleščina,
- španščina,
- nemščina,
- hrvaščina.

Delovanje klasifikatorja je dvoplastno, vsebuje fazo učenja in fazo klasifikacije.

## Faza učenja
V fazi učenja za izbrane jezike naložimo ***učni material*** ter izdelamo profile za vsak posamezen jezik.

Za učni material sem zbral besedila o posameznih državah z Wikipedije (npr. za profil slovenščine sem uporabil besedilo na https://en.wikipedia.org/wiki/Slovenia)
ter jih shranil v mapo [data/corpora](https://github.com/IgorPolajzer/JT_Language_detection/tree/master/data/corpora).

## Faza klasifikacije
V tej fazi v program vnesemo poljuben tekstovni dokument (v moji implementaciji so ti prisotni v https://github.com/IgorPolajzer/JT_Language_detection/tree/master/data/test_files), program pa ga klasificira glede na izvorni jezik.

Sam potek klasifikacije poteka tako, da za vneseni dokument ustvari profil ter med njim in vsemi klasifikacijskimi profili programa izmeri razdaljo.

Samo merjenje razdalje je zelo preprosto, program zgolj izmeri razliko med mestom uvrstitve tokenov med profiloma, na koncu pa vse te razlike sešteje.
Klasifikacijski profil, ki ima najmanjšo razdaljo glede na profil podanega dokumenta, klasificira dokument.

## Rezultati
Za testiranje sem poiskal besedila z novinarskih spletnih mest posameznih jezikov (npr. za slovenščino sem izbral https://www.rtvslo.si/).

Program je uspešno klasificiral vse jezike.


## Ugotovitve

Ugotovil sem, da klasifikator deluje precej zanesljivo, vendar je zelo pomembno, da so učni materiali za posamezne jezike približno enako obsežni. V nasprotnem primeru pride do pristranskosti zaradi neuravnoteženih podatkov, kar lahko vodi do napačnih klasifikacij pri podobnih jezikih.

To sem opazil pri klasifikaciji hrvaščine, kjer je bil učni material za slovenščino približno dvakrat krajši kot za hrvaščino. Posledično je sistem hrvaški jezik napačno klasificiral kot slovenščino. Ko sem  dolžino materiala prilagodil je zadeva delovala kot pričakovano.