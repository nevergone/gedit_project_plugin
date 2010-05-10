"gedit-project-plugin" le�r�s


1.) Mi ez?

Egy kieg�szit� modul (m�sn�ven plugin) a gedit f�jlszerkeszt� programhoz, amely seg�ts�g�vel projectek kezel�s�re ny�lik m�d.


2.) Mi az a project?

Projectnek neveztem el, amikor t�bb �llom�nyt egyszerre szeretn�nk kezelni. �gy, ha t�bb f�jl szeretn�nk megnyitni egyszerre, nem kell egyenk�nt megnyitni �ket, m�g akkor sem, ha nem egy k�nyvt�rban tal�lhat�ak. Az URI (Uniform Resource Identifier) seg�ts�g�vel pedig ezek az �llom�nyok lehetnek h�l�zaton, vagy b�rmely m�s, a rendszer �ltal kezelt virtu�lis f�jlrendszeren.
Persze egy project t�bb, mint �llom�nyok egyszer� halmaza, egy project lehet "csak olvashat�", m�g akkor is, ha a benne szerepl� �llom�nyok nem azok. S�t, egy projecten bel�l k�l�n-k�l�n is lehet rendelkezni kiv�lasztott �llom�nyok csak olvashat�s�g�r�l.
S�t, egy project m�g enn�l is t�bb lehet, de ezek megval�s�t�sa m�g kidolgoz�s alatt �ll, mint ahogy a fentebb felsorolt lehet�s�gek k�z�l sincs m�g mindegyik kidolgozva. A geditben a projectek egys�gesen egy �llom�nyban vannak �sszefogva, ennek az �llom�nynak a kiterjeszt�se "gedit-prj".


3.) Mennyire stabil?

Miel�tt haszn�latba veszed, felh�vom a figyelmed arra, hogy ez m�g csak egy pr�bav�ltozat, bemutat�si �s el�zetes hibakeres�si c�lzattal, nem utols� sorban pedig az�rt, hogy felh�vja a figyelmet a modul tov�bbfejleszt�si lehet�s�geire, esetleg hi�nyoss�gaira.
Sz�val, m�g ne haszn�ld �lesben, m�r csak az�rt is, mert val�sz�n�leg a project-�llom�ny szerkezete is v�ltozni fog. A modul haszn�lat�b�l ered� k�rok�rt �s adatveszt�s�rt nem v�llalhatok felel�s�get, mindez�ltal az�rt t�rekedtem a min�l �tl�that�bb �s hibamentesebb programoz�sra.


4.) Mi kell hozz�?

A b�v�t�modult �n GNOME 2.8 alatt fejlesztettem, �s jelen �llapot�ban nem fog m�k�dni r�gebbi v�ltozatokkal, mert haszn�lok olyan programoz�stechnikai eszk�z�ket, melyek a GTK+ 2.4 -es v�ltozat�ban jelentek meg. Nem is tervezem a r�gebbi rendszerekre val� portolhat�s�g�t, ha csak valami igaz�n nyom�s indokot nem tal�lok.
Term�szetesen sz�ks�ged lesz egy megfelel�en be�ll�tott C ford�t�ra (amely �ltal�ban valamelyik gcc v�ltozat) a sz�ks�ges linkerrel egy�tt.


5.) Hogyan haszn�lhatom?

El�sz�r is, le kell ford�tanod. Mivel ezen v�ltozat m�g nem az autoconf/automake rendszerre �p�l, ez�rt a k�zismert "./configure && make && make install" most m�g nem haszn�lhat�. D
El�sz�r is telep�tsd a g�pedre a GNOME rendszert a sz�ks�ges fejleszt�i csomagokkal egy�tt, ezeket a legt�bb esetben olyan �llom�nyokban tal�lod, melyek neve "-dev" -re v�gz�dik.
Ha ez megt�rt�nt, akkor j�het a ford�t�s. Csomagold ki az �llom�nyt (ha ezt olvasod, val�sz�n�leg m�r megt�rt�nt), majd add ki a ./compile-plugin parancsot, amely leford�tja a modult. Ha ford�t�s k�zben hiba�zenetet tal�lsz, akkor val�sz�n�leg nem telep�tett�l fel minden sz�ks�ges f�gg�s�get �s fejleszt�i csomagot. Val�sz�n�leg j�p�r sort l�tsz majd megjelenni ilyen v�gz�d�ssel: "linker input file unused because linking not done" Ezzel ne t�r�dj, a ford�t� �s a linker finomhangol�sa m�g visszavan, esetleg k�ldhetsz r� javaslatot. Minden �zenetnek, amely m�s ezekt�l, k�rlek j�rj ut�na, �s ha a hiba nem a "te k�sz�l�kedben van", vagyis �n rontottam el valamit, jelezz vissza a lentebb �rt m�don.
Ha a ford�t�s sikeres volt, a ./install-plugin telep�ti azt a home k�nyvt�rad megfelel� r�sz�be, ha ennek a pluginnak volt ott el�z� v�ltozata (mert mondjuk teszteled a plugint), akkor fel�rja azt. A sikeres telep�t�s ut�n a gedit -et elind�tva l�pj a f�men� "Szerkeszt�s" (Edit) men�pontj�nak "Be�ll�t�sok" (Preferences) men�pontj�ra, majd a megjelen� ablakban v�laszd a "B�v�tm�nyek" (Plugins) oldalt. Az itt megjelent list�ban megtal�lod a "Projectkezel�" (Project manager) modult. Az el�bb felsorolt nevek ut�n z�r�jelben megadott sz�vegek angol nyelv�re �ll�tott rendszer eset�n haszn�lhat�ak.
Sz�val, az el�bbi ablakban a n�v el�tti jel�l�dobozt bekapcsolva a modul bet�lt�dik, �s itt ugyan�gy k�rheted az elt�vol�t�s�t is. Ha sikeres volt�l (m�rpedig mi�rt ne lett�l volna az), akkor a "F�jl" (File) men�ben megjelent egy "Projectek" men�pont, tov�bbi v�laszthat� elemekkel. A modulhoz mell�keltem egy minta-projectet is, amelyen tesztelheted a modul m�k�d�s�t. Mivel a project-�llom�nyban egyel�re nem lehet m�g relat�v f�jl-el�r�si �tvonalat haszn�lnod, ez�rt a project-�llom�nyt k�zzel szerkesztened, hogy megadd az �llom�nyok abszol�t el�r�si �tvonal�t. De ennek a megold�sa folyamatban van.
Ha modul b�rmi probl�m�t okozna a gedit indul�s�ban vagy m�k�d�s�ben, akkor a kibontott plugin k�nyvt�r�ban kiadott ./remove-plugin elt�vol�tja azt a rendszeredr�l.

6.) Mi az, ami nem m�k�dik?

Nos, a project-�llom�ny m�dos�t�sa m�g k�zzel t�rt�nik, de ennek m�dja a minta-�llom�ny megn�z�se ut�n nem lehet k�ts�ges. A men�ben nem lehet m�g haszn�lni a "Project tulajdonsagok" men�pontot, mert kidolgoz�s alatt �ll. Tudom, hogy a haszn�lt sz�vegek mindenk�ppen magyarul �s �kezet n�lk�l jelennek meg, ez �gyben ne is jelezz vissza, legfeljebb ha v�llalod a lokaliz�ci�ban val� seg�ts�get. Hi�nyoss�g m�g, hogy a kiv�telkezel�s ter�n t�bb hibalehet�s�g m�g nincs lekezelve.


7.) Hova k�ldhetek visszajelz�seket �s hibajav�t�sokat?

Ha seg�teni szeretn�l, a gedit -et termin�lablakb�l ind�tsd. Ugyanis a legt�bb hasznos hiba�zenet oda �r�dik ki. Ha hib�t tal�lsz hiba�zenettel egyetemben, akkor ezeket k�ldd el emailben, a kiv�lt� k�r�lm�ny le�r�s�val egy�tt.
Leveledet a never@delfin.unideb.hu c�mre k�ldd. K�rlek ne k�ldj spam -et, v�rusokat, k�rleveleket, �s egy�b felesleges dolgokat.

U.i.: Valaki �rhatna egy k�z�rthet� �s haszn�lhat� magyar nyelv� HOWTO -t arr�l, hogyan kell egy Subversion (vagy m�s, hasonl� kval�t�s� �s min�s�g� verzi�kezel� rendszert) rendszert elk�sz�teni �s haszn�lni...



Tisztelettel:
Kurucz "The NeverGone" Istv�n :)

Debrecen, 2006.01.23
