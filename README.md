# Konio

<p align=justify>Konio este un joc 2D de strategie in timp real, singleplayer, militar si economic. Actiunea acestui joc se situeaza in secolul 6 i.Hr, in peninsula Greaca. Jucatorul isi alege un oras-stat din cele 12 si trebuie sa se foloseasca de resursele economice, flota, orasele aliate si chiar de dusmani pentru a pastra suprematia navala. Momentan proiectul este in dezvoltare.</p>

<p align=justify>In contextul istoric al jocului (550 i.Hr), orasele-stat grecesti nu au avut de intampinat un rival care sa le fi pus libertatea in pericol. Venitul in bani al orasului consta din taxele populatiei si comert. Fiecare oras-stat are o resursa pe care o produce si o exporta intr-un oras-stat aliat, la randul sau importa o anumita resursa dintr-un oras stat grecesc.</p>

<p align=justify>Dezvoltarea proiectului a durat aproximativ 4 luni. Tot codul este scris si gandit de la zero. Imi asum raspunderea pentru orice bug sau eroare de rulare ce tine de codul sursa. Momentan jocul este disponibil doar pentru Linux. Fiecare element grafic este facut personal, fiind folosite anumite resurse externe.</p>

<p align=justify>Scopul jocului este sa dezvolte creativitatea, gandirea analitica, rabdarea si concentrarea jucatorului. De asemenea contextul acestui joc este unu educativ.</p>

<p align=justify>Grafica jocului este simplista ce imita anumite elemente din realitate(scuturi, picturi, apa, terenuri, corabii) si pune in valoare tema acestui joc. Textul este alb, pe fundal inchis, fiind foarte vizibil pentru jucator.</p>

<img height=250 align=left src='https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/Gallery/0.png'/>
<img height=250 align=left src='https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/Gallery/1.png'/>

<p align=justify>Flotele sunt unitati militare ce au in componenta lor mai multe nave. Navele unei flote pot fi asezate in trei formatii, acestea stabilind tactica AI-ului. Fiecare flota are o anumita cantitate de provizii iar atunci cand aceasta ajunge la zero, flota este pierduta. Cand doua flote inamice se intalnesc incepe o batalie. In batalie, o nava poate fi doborata daca e lovita de una inamica cu partea frontala(berbecul de bronz) in lateral, in spate sau in fata(cea mai puternica si rapida o scufunda pe cea mai lenta si mai mica). Cand jucatorul se retrage din batalie pierde intreaga flota. Batalia se termina cand una dintre tabere ramane fara nave.</p>

<img height=260 align=left src='https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/Gallery/7.png'/>
<img height=260 align=left src='https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/Gallery/8.png'/>

Tactici si formatii:<br/>
1. Periplous: navele sunt asezate intr-o singura linie, inainteaza in formatie pana ce flota inamica e aproape si sparg linia, navele atacand individual.<br/>
2. Diekplous: navele sunt asezate in linii perpediculare fata de linia frontului. AI-ul  incearca sa patrunda printre nave.<br/>
3. Kyklos: navele sunt asezate in cerc. Navele se misca in cerc pana ce se apropie suficient inamicul, atunci flota trece in contra-atac.<br/>

<img height=260 align=left src='https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/Gallery/10.png'/>
<img height=260 align=left src='https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/Gallery/6.png'/>

<p align=justify>Sistemul economic al jocului este simplist. Fiecare jucator(sau AI) are un oras cu deschidere la mare ce produce o anumita resursa. Fiecare oras exporta aceea resursa catre un oras aliat si importa o alta resursa de la un aliat. Venitul in bani pentru fiecare jucator consta in taxe si comert. Taxele constau intr-o moneda la fiecare 1000 de locuitori al oraselor pe care il detine. Un oras este cucerit daca se afla o flota inamica in aproprierea sa. De asemenea orasul poate fi recucerit de aliati, orasul devenind proprietatea vechiului jucator.</p>

Resurse:<br/>
1. Piatra (6 monezi): Creste capacitatea populatiei a orasului cu 40% si venitul din taxe cu 10%. Capacitatea populatiei este in jur de 60000-70000.<br/>
2. Lemn (6 monezi): Permite construirea urmatoarelor nave: Pentekonter, Bireme si Trireme.<br/>
   Fara lemn, orasul poate recruta nave mercenare, dar la un pret mai mare: Hemiolia si Trihemiolia.<br/>
3. Metale (8 monezi): Cresc venitul in oras din comert cu 20%.<br/>
4. Masline (4 monezi): Creste capacitatea populatiei orasului cu 10% si sporul natural cu 10%.<br/>
5. Grau (4 monezi): Creste capacitatea populatiei a orasului cu 20%.<br/>
6. Capre (6 monezi): Creste capacitatea populatiei orasului cu 10% mai mare si venitul din comert cu 10%.<br>
7. Peste (4 monezi): Sporul natural este cu 20% mai mare.<br/>

<img src='https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/Gallery/5.png'/>

Nave:<br/>
1. Pentekonter (6 monezi): Nava usoara cu 50 de vaslasi(un rand cu 25 pe ambele parti), 17km/h.<br/>
2. Bireme (8 monezi): Nava media cu 120 de vaslasi(2 randuri cu 30 pe ambele parti), 17km/h.<br/>
3. Trireme (10 monezi): Nava grea cu 180 de vaslasi(3 randuri cu 30 pe ambele parti), 17km/h.<br/>
4. Hemiolia (15 monezi): Nava medie cu 60 de vaslasi(un rand 20 si unu de 10), 20km/h.<br/>
5. Trihemiolia (17 monezi): Nava medie cu 120 de vaslasi(2 randuri de 40 si unu de 20), 20km/h.<br/>

<img src='https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/Gallery/4.png'/>

Tehnologii folosite:<br/>
1. Photoshop CS5 pentru creearea elementelor grafice.<br/>
2. Biblioteca grafica SFML pentru limbajul C++.<br/>
3. Limbajul C++.<br/>
4. cmake, g++ pentru compilarea codului sursa, pe Linux.<br/>
5. IDE Sublime Text pentru editarea codului sursa.<br/>

<img src='https://raw.githubusercontent.com/BalescuOvidiu/Konio/master/Gallery/2.png'/>

Muzica si sunet:<br/>
1. <a href='https://www.youtube.com/watch?v=Eh51m6glEHo'>Winds of Ithaca - Antti Martikainen</a><br/>
2. <a href='https://www.youtube.com/watch?v=L-xEJxmxY_w'>Athena - Derek & Brandon Fiechter</a><br/>
3. <a href='www.soundbible.com'>soundbible.com</a><br/>

Bibliografie:<br/>
1. <a href='www.wikipedia.en'>wikipedia.en</a><br/>
2. <a href='www.ancientgreece.com'>ancientgreece.com</a><br/>
3. <a href='http://www.piticipecreier.ro/carte/52338-Grecia-antica.html'>"Grecia antica" - Editura Litera International - Louise Schofield</a><br/>
