# Szachy - implementacja komputerowa
<p align="center">
  <img src="https://i.imgur.com/tEQbD6K.png">
</p>

## Spis treści
* [Zarys projektu](#zarys-projektu)
* [Technologie](#technologie)
* [Instrukcja instalacji i uruchomienia](#instrukcja-instalacji-i-uruchomienia)
* [Jak grać?](#jak-grać)
* [Licencje](#licencje)

## Zarys projektu
Projekt jest implementacją komputerową znanej gry planszowej - szachy w języku programistycznym C. Powstał on w ramach projektu programistycznego na przedmiot - Podstawowy warsztat informatyka realizowany w ramach I semestru studiów Informatycznych I stopnia na Instytucie Informatycznym Uniwersytetu Wrocławskiego w roku 2020/2021. Autorom projektu zależało na jak najdokładniejszego odwzorowania uczucia gry w szachy. </br>

### Cele: 
* Dokładne odwzorowanie mechanik i reguł gry w szachy
* Zaznajomienie się ze Gitem oraz platformom Github
* Nauka pracy zespołowej i efektywnego działania w zespole

## Technologie
Projekt tworzony jest w języku programistycznym C z użyciem biblioteki ncurses.

## Instrukcja instalacji i uruchomienia
* Do uruchomienia gry wymagane są pakiety:
```
ncuses
make
gcc
```
* Sklonuj repozytorium
* Wejdż do repozytorium i wykonaj polecenie:
```
make
```
* Następnie otwórz skompilowany projekt poleceniem:
```
./szachy.out
```
## Jak grać?
Do wyboru są 3 tryby rozgrywki:
W głównym menu wybierz opcję ```zwykła gra```, ```horda``` lub ```rewolucja```. <br>
Ruchy wykonuj podając najpierw koordynaty bierka, który chcesz wybrać, a następnie koordynaty, na które chcesz go przestawić.<br>
Po wprowadzeniu litery i cyfry koordynatów (np. ```e4```) zatwierdź je przyciskiem enter.

<p align="center">
  <img src="https://i.imgur.com/mvX3uA8.png" width="450" height="300"/>
  <img src="https://i.imgur.com/NH3HRmV.png" width="450" height="300"/> 
</p>

## Licencje
MIT License

Copyright (c) 2021 Xelonidas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
