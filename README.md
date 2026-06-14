# MonkeyTyper

MonkeyTyper to prosta gra napisana w C++ z użyciem biblioteki SFML. Celem gry jest wpisywanie słów pojawiających się na ekranie, zanim dotrą do góry. Za każde poprawnie wpisane słowo gracz otrzymuje punkt, a za pominięte słowo traci życie.

## Funkcje programu

* menu główne gry,
* wybór poziomu trudności,
* wybór czcionki i rozmiaru tekstu,
* wybór prędkości gry,
* wpisywanie nazwy gracza,
* licznik punktów i żyć,
* ranking Top 5 zapisywany do pliku,
* ekran końcowy z opcją restartu lub powrotu do menu.

## Wymagania

* C++20
* CMake 3.30 lub nowszy
* SFML 3.0.0
* fmt 11.1.4

Biblioteki SFML i fmt są pobierane automatycznie przez CMake za pomocą `FetchContent`.

## Pliki zasobów

Program wymaga folderu `resources`, w którym powinny znajdować się:

* `font1.ttf`
* `font2.ttf`
* `font3.ttf`
* `font4.ttf`
* `menu_background.png`
* `game_background.png`
* `wordseasy.txt`
* `wordsmedium.txt`
* `wordshard.txt`
* `top5.txt`

Folder `resources` powinien znajdować się w katalogu roboczym programu.

## Uruchomienie

Projekt można uruchomić w CLionie albo z terminala:

```bash
cmake -S . -B build
cmake --build build
```

Następnie należy uruchomić plik wykonywalny projektu.

## Autor

https://github.com/vladosvvv
