# Ruokinta-automaatti
Mikrokontrolleri ohjattu ruokinta-automaatti pienel�imille, jonka tein yhdess� parini Henry Hongiston kanssa Savonian Iot kurssin kunnianhimoiseksi lopputy�ksi. Hoidin suurimman osan koodauksesta, Henryn keskittyess� ohjelmointi esimerkkien lis�ksi kopan ja avaus mekanismin, 3d mallintamiseen tulostamiseen ja kasaamiseen.

Loppuraportti jossa on tarkka dokumentaatio laitteesta l�ytyy dokumentaatio kansiosta.


Idea ja toteutuksesta:
El�imen ruokinta-automaatin tarkoitus on mahdollistaa kotiel�inten omistajien el�inten ruokinta, kun he ovat poissa. Esim jos kissojen omistaja haluaa l�hte� viikonlopuksi pois, ja h�n ei halua vaivata tai h�n ei saa ket��n l�heist��n ruokkimaan kissoja, laite tulee pelastukseen!
Laitteen k�ytt� olisi seuraavanlainen, laita laite sein��n (Luukut avautuu automaattisesti), laita ruuat lokeroihin, aseta h�lytykset lokeroille ja sulje luukut. Nyt kun esim luukun 1 h�lytys soi, luukku 1 aukeaa ja aktiivinen h�lytys siirtyy luukku 2:seen. Kun 2 h�lytys soi, luukku 2 aukeaa jne. Kissa saa ruokaa tasaisesti viikonlopun aikana.
Arduino Leonardolla ohjattavassa laitteessa on 4, servolla hallittavaa luukkua, encoderi, RTC piiri ja n�ytt�. N�yt�st� voi sulkea luukut ja asettaa luukuille h�lytysajan.