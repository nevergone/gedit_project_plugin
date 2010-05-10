"gedit-project-plugin" leírás


1.) Mi ez?

Egy kiegészitő modul (másnéven plugin) a gedit fájlszerkesztő programhoz, amely segítségével projectek kezelésére nyílik mód.


2.) Mi az a project?

Projectnek neveztem el, amikor több állományt egyszerre szeretnénk kezelni. Így, ha több fájl szeretnénk megnyitni egyszerre, nem kell egyenként megnyitni őket, még akkor sem, ha nem egy könyvtárban találhatóak. Az URI (Uniform Resource Identifier) segítségével pedig ezek az állományok lehetnek hálózaton, vagy bármely más, a rendszer által kezelt virtuális fájlrendszeren.
Persze egy project több, mint állományok egyszerű halmaza, egy project lehet "csak olvasható", még akkor is, ha a benne szereplő állományok nem azok. Sőt, egy projecten belül külön-külön is lehet rendelkezni kiválasztott állományok csak olvashatóságáról.
Sőt, egy project még ennél is több lehet, de ezek megvalósítása még kidolgozás alatt áll, mint ahogy a fentebb felsorolt lehetőségek közül sincs még mindegyik kidolgozva. A geditben a projectek egységesen egy állományban vannak összefogva, ennek az állománynak a kiterjesztése "gedit-prj".


3.) Mennyire stabil?

Mielött használatba veszed, felhívom a figyelmed arra, hogy ez még csak egy próbaváltozat, bemutatási és előzetes hibakeresési célzattal, nem utolsó sorban pedig azért, hogy felhívja a figyelmet a modul továbbfejlesztési lehetőségeire, esetleg hiányosságaira.
Szóval, még ne használd élesben, már csak azért is, mert valószínűleg a project-állomány szerkezete is változni fog. A modul használatából eredő károkért és adatvesztésért nem vállalhatok felelőséget, mindezáltal azért törekedtem a minél átláthatóbb és hibamentesebb programozásra.


4.) Mi kell hozzá?

A bővítőmodult én GNOME 2.8 alatt fejlesztettem, és jelen állapotában nem fog működni régebbi változatokkal, mert használok olyan programozástechnikai eszközöket, melyek a GTK+ 2.4 -es változatában jelentek meg. Nem is tervezem a régebbi rendszerekre való portolhatóságát, ha csak valami igazán nyomós indokot nem találok.
Természetesen szükséged lesz egy megfelelően beállított C fordítóra (amely általában valamelyik gcc változat) a szükséges linkerrel együtt.


5.) Hogyan használhatom?

Először is, le kell fordítanod. Mivel ezen változat még nem az autoconf/automake rendszerre épül, ezért a közismert "./configure && make && make install" most még nem használható. D
Először is telepítsd a gépedre a GNOME rendszert a szükséges fejlesztői csomagokkal együtt, ezeket a legtöbb esetben olyan állományokban találod, melyek neve "-dev" -re végződik.
Ha ez megtörtént, akkor jöhet a fordítás. Csomagold ki az állományt (ha ezt olvasod, valószínűleg már megtörtént), majd add ki a ./compile-plugin parancsot, amely lefordítja a modult. Ha fordítás közben hibaüzenetet találsz, akkor valószínűleg nem telepítettél fel minden szükséges függőséget és fejlesztői csomagot. Valószínűleg jópár sort látsz majd megjelenni ilyen végződéssel: "linker input file unused because linking not done" Ezzel ne törődj, a fordító és a linker finomhangolása még visszavan, esetleg küldhetsz rá javaslatot. Minden üzenetnek, amely más ezektől, kérlek járj utána, és ha a hiba nem a "te készülékedben van", vagyis én rontottam el valamit, jelezz vissza a lentebb írt módon.
Ha a fordítás sikeres volt, a ./install-plugin telepíti azt a home könyvtárad megfelelő részébe, ha ennek a pluginnak volt ott előző változata (mert mondjuk teszteled a plugint), akkor felírja azt. A sikeres telepítés után a gedit -et elindítva lépj a főmenű "Szerkesztés" (Edit) menűpontjának "Beállítások" (Preferences) menűpontjára, majd a megjelenő ablakban válaszd a "Bővítmények" (Plugins) oldalt. Az itt megjelent listában megtalálod a "Projectkezelő" (Project manager) modult. Az elöbb felsorolt nevek után zárójelben megadott szövegek angol nyelvűre állított rendszer esetén használhatóak.
Szóval, az elöbbi ablakban a név elötti jelölődobozt bekapcsolva a modul betöltődik, és itt ugyanígy kérheted az eltávolítását is. Ha sikeres voltál (márpedig miért ne lettél volna az), akkor a "Fájl" (File) menűben megjelent egy "Projectek" menűpont, további választható elemekkel. A modulhoz mellékeltem egy minta-projectet is, amelyen tesztelheted a modul működését. Mivel a project-állományban egyelőre nem lehet még relatív fájl-elérési útvonalat használnod, ezért a project-állományt kézzel szerkesztened, hogy megadd az állományok abszolút elérési útvonalát. De ennek a megoldása folyamatban van.
Ha modul bármi problémát okozna a gedit indulásában vagy működésében, akkor a kibontott plugin könyvtárában kiadott ./remove-plugin eltávolítja azt a rendszeredről.

6.) Mi az, ami nem működik?

Nos, a project-állomány módosítása még kézzel történik, de ennek módja a minta-állomány megnézése után nem lehet kétséges. A menűben nem lehet még használni a "Project tulajdonsagok" menűpontot, mert kidolgozás alatt áll. Tudom, hogy a használt szövegek mindenképpen magyarul és ékezet nélkül jelennek meg, ez ügyben ne is jelezz vissza, legfeljebb ha vállalod a lokalizációban való segítséget. Hiányosság még, hogy a kivételkezelés terén több hibalehetőség még nincs lekezelve.


7.) Hova küldhetek visszajelzéseket és hibajavításokat?

Ha segíteni szeretnél, a gedit -et terminálablakból indítsd. Ugyanis a legtöbb hasznos hibaüzenet oda íródik ki. Ha hibát találsz hibaüzenettel egyetemben, akkor ezeket küldd el emailben, a kiváltó körülmény leírásával együtt.
Leveledet a never@delfin.unideb.hu címre küldd. Kérlek ne küldj spam -et, vírusokat, körleveleket, és egyéb felesleges dolgokat.

U.i.: Valaki írhatna egy közérthető és használható magyar nyelvű HOWTO -t arról, hogyan kell egy Subversion (vagy más, hasonló kvalítású és minőségű verziókezelő rendszert) rendszert elkészíteni és használni...



Tisztelettel:
Kurucz "The NeverGone" István :)

Debrecen, 2006.01.23
