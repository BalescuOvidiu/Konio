# Konio - Joc de strategie 2D

## Cuprins

1. [Descriere](https://github.com/BalescuOvidiu/Konio#descriere)<br>
3. [Flote](https://github.com/BalescuOvidiu/Konio#flote)<br>
2. [Tactici și formatii](https://github.com/BalescuOvidiu/Konio#tactici-și-formașii)<br>
5. [Sistem economic](https://github.com/BalescuOvidiu/Konio#sistem-economic)<br>
5. [Resurse](https://github.com/BalescuOvidiu/Konio#resurse)<br>
6. [Nave](https://github.com/BalescuOvidiu/Konio#nava)<br>
7. [Tehnologii folosite](https://github.com/BalescuOvidiu/Konio#tehnologii-folosite)<br>
8. [Muzică și efecte audio](https://github.com/BalescuOvidiu/Konio#muzică-și-efecte-audio)<br>
9. [Bibliografie](https://github.com/BalescuOvidiu/Konio#bibliografie)<br>
10. [Rezultate](https://github.com/BalescuOvidiu/Submarine#rezultate)<br>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-menu.png)

## Descriere

<p align=justify>Konio este un joc 2D de strategie în timp real, singleplayer, militar și economic. Acțiunea acestui joc se desfășoară în secolul 6 i.Hr, în peninsula Greacă. Jucătorul conduce un oraș-stat din cele 12 și trebuie să se folosească de resursele economice, flotă, orașele aliate și chiar de dușmani, pentru a păstra supremația navală. Momentan jocul este în dezvoltare și disponibil direct pe Linux. Pentru alte sisteme de operare, trebuie compilat separat.</p>

<p align=justify>In contextul istoric al jocului (550 i.Hr), orașele-stat grecesti nu au avut de intampinat un rival care sa le fi pus libertatea în pericol, iar asta le-a permis să fie în conflict mult timp. Venitul în bani al orașului constă din taxele populației și comerț. Fiecare oraș-stat are o resursă pe care o produce și o exportă într-un oraș-stat aliat. La rândul său importă o anumită resursă dintr-un oraș stat aliat.</p>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-campaign.png)

## Flote

<p align=justify>Flotele sunt unități militare ce au în componența lor mai multe nave. Navele unei flote pot fi asezate în trei formatii, acestea stabilind tactica inamicului. Fiecare flotă are o anumită cantitate de provizii iar atunci Când aceasta ajunge la zero, flota este pierdută. O bătălie începe când două flote adversare se întâlnesc. în timpul luptei, o navă poate fi distrusă dacă e lovită de una inamică cu partea frontală(berbecul de bronz) în lateral, în spate sau în fată(cea mai puternică și rapidă o scufunda pe cea mai lentă și mai mică). Când jucătorul se retrage din bătălie pierde întreaga flotă. Batălia se termină Când una dintre tabere rămâne fără nave. Într-o luptă pot fi mai mult de 2 jucători, cu cel puțin o flotă, dacă sunt în apropriere.</p>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-battle-0.png)

## Tactici și formații

1. Periplous: navele sunt asezate într-o singură linie, înaintează în formatie până ce flota inamica e aproape și sparg linia, navele ataCând individual.<br/>
2. Diekplous: formația navelor are formă de triunghi. Inamicul încearcă sa pătrundă prin centru.<br/>
3. Kyklos: navele sunt asezate în cerc. Intră în contra-atac când inamicul este foarte aproape.<br/>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-battle-1.png)

## Sistem economic

<p align=justify>Sistemul economic al jocului este simplist. Fiecare jucător(sau inamic) are un oraș cu deschidere la mare care produce o anumită resursă. Fiecare oraș exporta aceea resursă către un oraș aliat și importă altă resursă de la un aliat. Venitul în bani pentru fiecare jucător constă în taxe și comerț. Taxele depind de numărul de locuitori al orașelor pe care îl deține. Un oraș este cucerit daca se află o flotă inamică lângă malul său. De asemenea, orașul poate fi recucerit de aliati, orașul fiind recăpătat de jucătorul care-l deținea la începutul jocului.</p>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-settlement.png)

## Resurse

1. Piatră (6 monezi): Crește capacitatea populației a orașului cu 40% și venitul din taxe cu 10%. Capacitatea populației este în jur de 60000-70000.<br/>
2. Lemn (6 monezi): Permite construirea urmatoarelor nave: Pentekonter, Bireme și Trireme.<br/>
   Fără lemn, orașul poate recruta nave mercenare, dar la un preț mai mare: Hemiolia și Trihemiolia.<br/>
3. Metale (8 monezi): Cresc venitul în oraș din comerț cu 20%.<br/>
4. Măsline (4 monezi): Crește capacitatea populației orașului cu 10% și sporul natural cu 10%.<br/>
5. Grâu (4 monezi): Crește capacitatea populației a orașului cu 20%.<br/>
6. Capre (6 monezi): Crește capacitatea populației orașului cu 10% mai mare și venitul din comerț cu 10%.<br>
7. Pește (4 monezi): Sporul natural este cu 20% mai mare.<br/>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-formation.png)

## Nave

1. Pentekonter (6 monezi): Navă usoară cu 50 de vâslași(un rând cu 25 pe ambele părți), 17km/h.<br/>
2. Bireme (8 monezi): Navă media cu 120 de vâslași(2 rânduri cu 30 pe ambele părți), 17km/h.<br/>
3. Trireme (10 monezi): Navă grea cu 180 de vâslași(3 rânduri cu 30 pe ambele părți), 17km/h.<br/>
4. Hemiolia (15 monezi): Navă medie cu 60 de vâslași(un rând 20 și unu de 10), 20km/h.<br/>
5. Trihemiolia (17 monezi): navă medie cu 120 de vâslași(2 rânduri de 40 și unu de 20), 20km/h.<br/>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-diplomacy.png)

## Tehnologii folosite

1. Limbajul de programare <a href='https://cplusplus.com/doc/tutorial/'>C++</a>.<br/>
2. Framework-ul <a href='https://www.sfml-dev.org/documentation/3.0.0/'>SFML</a> pentru limbajul C++.<br/>
3. <a href='https://www.photopea.com/'>Photopea</a> pentru creearea elementelor grafice.<br/>

## Muzică și efecte audio

1. <a href='https://www.youtube.com/watch?v=Eh51m6glEHo'>Winds of Ithaca - Antti Martikainen</a><br/>
2. <a href='https://www.youtube.com/watch?v=L-xEJxmxY_w'>Athena - Derek & Brandon Fiechter</a><br/>
3. <a href='www.soundbible.com'>soundbible.com</a><br/>

## Bibliografie

1. <a href='www.wikipedia.en'>wikipedia.en</a><br/>
2. <a href='www.ancientgreece.com'>ancientgreece.com</a><br/>
3. <a href='http://www.piticipecreier.ro/carte/52338-Grecia-antica.html'>"Grecia antica" - Editura Litera International - Louise Schofield</a><br/>

## Rezultate

<p align=justify>InfoEducație 2017 - Etapa județeană - Premiul III</p>
<p align=justify>GREPIT 2017 - Calificat la etapa națională</p>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-battle-3.png)