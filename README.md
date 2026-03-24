# Jezikovne tehnologije - Klasifikacija jezika dokumentov

Pri tej nalogi sem po vzgledu z članka [N-Gram-Based Text Categorization](https://dsacl3-2019.github.io/materials/CavnarTrenkle.pdf) implementiral preprost
klasifikator dokumentov glede na njihov jezik. Princip deluje na izdelavi profilov za iskane jezike, v mojem primeru so to: 
- Slovenščina,
- Angleščina, 
- Španščina, 
- Nemščina, 
- Italjanščina.

Princip delovanja klasifikatorja je dvoplasten, vsebuje fazo učenja in fazo klasifikacije.

## Faza učanja
V fazi učenja za izbrane jezike naložimo ***učni material***, ter izdelamo profile za vsak posamezen jezik. 

Jaz sem za material sem zbral besedila o posameznih država z wikipedije (npr. za material profile za slovenščino sem uporabil besedilo na https://en.wikipedia.org/wiki/Slovenia)
, ter jih shranil v mapo [data/corpora](https://github.com/IgorPolajzer/JT_Language_detection/tree/master/data/corpora).

## Faza klasifikacije
V tej fazi v program vnesemo poljuben tekstovni dokument (v moji implementaciji so ti prisotni v https://github.com/IgorPolajzer/JT_Language_detection/tree/master/data/test_files), on pa ga klasificira glede na izvorni jetik.

Sam potek klasifikacije poteka tako, da za vnešen dokument ustvari profil, ter med njim in vsemi kalsifikacijskimi profili programa izmeri razdaljo.

Samo morejenje razdalje je zelo preprosto, program zgolj izmeri razliko med mestom uvrstitve token med profiloma, na koncu pa vse te razlike sešteje.
Klasifikacijski profil ki ima najmanjšo razdaljo med profilom podanega dokumenta klasificira dokument.

## Rezultati
Za testiranje sem posikal tekst iz novinarskih spletnih mest posameznih jezikov (nor. za Slovenščino sem izbral https://www.rtvslo.si/).

Program je uspešno klasificiral vse jezike


## Ugotovitve

Ugotovil sem, da program klasificira tekst dokaj zanseljivo, pomembno pa je da so  materiali za posamezne jezike enako dolgi, drugače pride do overfittinga
in so lahko podobni jeziki narobe klasifiirani. To se mi je zgodilo ko sem klasificiral Hrvaški jezik kjer sem imel material za slovenski profil enkrat krajši od hrvaškega,
kar je privedlo do napačne klasifikacije hrvaškega jezika v slovenskega.