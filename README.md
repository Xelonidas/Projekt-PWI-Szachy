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
* Zaznajomienie się ze Gitem oraz platformą Github
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

Wpisanie w pola kolejno ```ex``` oraz ```it``` przerywa grę.

## Licencje
The codes and the pretrained model in this repository are under the MIT license as specified by the LICENSE file.
