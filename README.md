# Ruokinta-automaatti
Mikrokontrolleri ohjattu ruokinta-automaatti pieneläimille, jonka tein yhdessä parini Henry Hongiston kanssa Savonian Iot kurssin kunnianhimoiseksi lopputyöksi. Hoidin suurimman osan koodauksesta, Henryn keskittyessä ohjelmointi esimerkkien lisäksi kopan ja avaus mekanismin, 3d mallintamiseen tulostamiseen ja kasaamiseen.

Loppuraportti jossa on tarkka dokumentaatio laitteesta löytyy dokumentaatio kansiosta.


Idea ja toteutuksesta:
Eläimen ruokinta-automaatin tarkoitus on mahdollistaa kotieläinten omistajien eläinten ruokinta, kun he ovat poissa. Esim jos kissojen omistaja haluaa lähteä viikonlopuksi pois, ja hän ei halua vaivata tai hän ei saa ketään läheistään ruokkimaan kissoja, laite tulee pelastukseen!
Laitteen käyttö olisi seuraavanlainen, laita laite seinään (Luukut avautuu automaattisesti), laita ruuat lokeroihin, aseta hälytykset lokeroille ja sulje luukut. Nyt kun esim luukun 1 hälytys soi, luukku 1 aukeaa ja aktiivinen hälytys siirtyy luukku 2:seen. Kun 2 hälytys soi, luukku 2 aukeaa jne. Kissa saa ruokaa tasaisesti viikonlopun aikana.
Arduino Leonardolla ohjattavassa laitteessa on 4, servolla hallittavaa luukkua, encoderi, RTC piiri ja näyttö. Näytöstä voi sulkea luukut ja asettaa luukuille hälytysajan.