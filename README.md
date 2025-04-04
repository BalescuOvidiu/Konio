# Konio - Joc de strategie 2D

## Cuprins

1. [Descriere](https://github.com/BalescuOvidiu/Konio#descriere)<br>
3. [Nave](https://github.com/BalescuOvidiu/Konio#nave)<br>
2. [Tactici și formatii](https://github.com/BalescuOvidiu/Konio#tactici-și-formatii)<br>
5. [Sistem economic](https://github.com/BalescuOvidiu/Konio#circuit-electric)<br>
5. [Resurse](https://github.com/BalescuOvidiu/Konio#software)<br>
6. [Cost producție navă](https://github.com/BalescuOvidiu/Konio#viitoare-îmbunătățiri)<br>
7. [Tehnologii folosite](https://github.com/BalescuOvidiu/Konio#versiuni)<br>
8. [Muzică și efecte audio](https://github.com/BalescuOvidiu/Konio#unități)<br>
9. [Bibliografie](https://github.com/BalescuOvidiu/Konio#teste)<br>
10. [Rezultate](https://github.com/BalescuOvidiu/Submarine#rezultate)<br>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-menu.png)

## Descriere

<p align=justify>Konio este un joc 2D de strategie în timp real, singleplayer, militar și economic. Actiunea acestui joc se desfășoară în secolul 6 i.Hr, în peninsula Greaca. Jucatorul isi alege un oraș-stat din cele 12 și trebuie sa se foloseasca de resursele economice, flota, orașele aliate și chiar de dușmani pentru a pastra supremația navală. Momentan jocul este în dezvoltare și disponibil direct pe Linux. Pentru alte sisteme de operare, trebuie compilat separat.</p>

<p align=justify>In contextul istoric al jocului (550 i.Hr), orașele-stat grecesti nu au avut de intampinat un rival care sa le fi pus libertatea în pericol. Venitul în bani al orașului consta din taxele populației și comerț. Fiecare oraș-stat are o resursa pe care o produce și o exportă într-un oraș-stat aliat, la randul sau importă o anumită resursă dintr-un oraș stat grecesc.</p>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-campaign.png)

## Nave

<p align=justify>Flotele sunt unități militare ce au în componenta lor mai multe nave. Navele unei flote pot fi asezate în trei formatii, acestea stabilind tactica inamicului. Fiecare flota are o anumita cantitate de provizii iar atunci Când aceasta ajunge la zero, flota este pierduta. Când doua flote inamice se intalnesc incepe o bătălie. în bătălie, o nava poate fi doborata daca e lovita de una inamica cu partea frontala(berbecul de bronz) în lateral, în spate sau în fata(cea mai puternică și rapidă o scufunda pe cea mai lentă și mai mică). Când jucătorul se retrage din bătălie pierde întreaga flota. Batălia se termină Când una dintre tabere rămâne fără nave.</p>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-battle-0.png)

## Tactici și formatii

1. Periplous: navele sunt asezate într-o singură linie, înaintează în formatie până ce flota inamica e aproape și sparg linia, navele ataCând individual.<br/>
2. Diekplous: navele sunt asezate în linii perpediculare fata de linia frontului. Inamicul încearcă sa patrunda printre nave.<br/>
3. Kyklos: navele sunt asezate în cerc. Navele se miscă în cerc până ce se apropie suficient inamicu atunci flota contra-atacă.<br/>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-battle-1.png)

## Sistem economic

<p align=justify>Sistemul economic al jocului este simplist. Fiecare jucător(sau inamicul) are un oraș cu deschidere la mare ce produce o anumita resursa. Fiecare oraș exporta aceea resursa catre un oraș aliat și importa o alta resursa de la un aliat. Venitul în bani pentru fiecare jucător consta în taxe și comerț. Taxele constau într-o monedă la fiecare 1000 de locuitori al orașelor pe care îl deține. Un oraș este cucerit daca se află o flota inamică lângă malul său. De asemenea, orașul poate fi recucerit de aliati, orașul devenind proprietatea vechiului jucător.</p>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-settlement.png)

## Resurse

1. Piatra (6 monezi): Crește capacitatea populației a orașului cu 40% și venitul din taxe cu 10%. Capacitatea populației este în jur de 60000-70000.<br/>
2. Lemn (6 monezi): Permite construirea urmatoarelor nave: Pentekonter, Bireme și Trireme.<br/>
   Fara lemn, orașul poate recruta nave mercenare, dar la un pret mai mare: Hemiolia și Trihemiolia.<br/>
3. Metale (8 monezi): Cresc venitul în oraș din comerț cu 20%.<br/>
4. Masline (4 monezi): Crește capacitatea populației orașului cu 10% și sporul natural cu 10%.<br/>
5. Grau (4 monezi): Crește capacitatea populației a orașului cu 20%.<br/>
6. Capre (6 monezi): Crește capacitatea populației orașului cu 10% mai mare și venitul din comerț cu 10%.<br>
7. Peste (4 monezi): Sporul natural este cu 20% mai mare.<br/>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-formation.png)

## Cost producție navă

1. Pentekonter (6 monezi): Navă usoară cu 50 de vâslași(un rând cu 25 pe ambele părți), 17km/h.<br/>
2. Bireme (8 monezi): Navă media cu 120 de vâslași(2 rânduri cu 30 pe ambele părți), 17km/h.<br/>
3. Trireme (10 monezi): Navă grea cu 180 de vâslași(3 rânduri cu 30 pe ambele părți), 17km/h.<br/>
4. Hemiolia (15 monezi): Navă medie cu 60 de vâslași(un rând 20 și unu de 10), 20km/h.<br/>
5. Trihemiolia (17 monezi): navă medie cu 120 de vâslași(2 rânduri de 40 și unu de 20), 20km/h.<br/>

![](https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/img/screenshoot-diplomacy.png)

## Tehnologii folosite

1. Limbajul de programare C++.<br/>
2. Framework-ul SFML pentru limbajul C++.<br/>
3. Photopea pentru creearea elementelor grafice.<br/>

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