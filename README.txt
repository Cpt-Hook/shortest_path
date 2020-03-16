Kompilace:
    Pro kompilaci staci napsat v konzoli prikaz: 'make all',
    pokud by kompilace nebyla uspesna, nejspis je treba nainstalovat knihovnu ncurses (debian: sudo apt-get install libncurses5-dev).

Spusteni programu:
    ./main.out soubor_s_bludistem algoritmus [noprint]

    algoritmy: dfs, bfs, astar, greedy, random a dijkstra
    (noprint je nepovinny a slouzi k vypnuti animace - dojde pouze k vypsani vyreseneho bludiste)

    napr: 
    ./main.out dataset/36.txt astar
    ./main.out dataset/72.txt greedy
    ./main.out dataset/84.txt random noprint

Ovladani:
    Animace se preskakuje tlacitkem 'q' a rovnou se zobrazi vyresene bludiste, pote tlacitko 'q' ukonci program. Stisk jakehokoliv jineho tlacitka animaci posune o jeden krok vpred.
    V pripade pouzite moznosti noprint program pouze vypise bludiste a ukonci se.

Poznamka:
    Testovaci data jsou pro animaci celkem velka - bludiste se nevleze do terminalu. Bud pouzijte moznost noprint, nebo staci nastavit mensi font.
    Prvni 2 soubory z prikladu spusteni programu se k animaci celkem hodi.
    'o' - cesta, '-' - uzavrene policko, '#' - otevrene policko, 'S' - zacatek, 'E' - konec
