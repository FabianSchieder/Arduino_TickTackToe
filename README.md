# Arduino_TickTackToe

In diesem Projekt geht es um TickTackToe auf dem Arduino mit einer 3x3 zweifarbigen LED Matrix.
Wichtig zu beachten ist, dass dieses Projekt einen Arduino Mega benötigt, da der Arduino Uno nicht genug digitale Pins besitzt.

Stückliste:

- 10 Leds (beliebige Farbe)
- 10 Leds (andere beliebige Farbe)
- 9 Buttons
- 9 Wiederstände (hier 330Ohm)
- verschieden lange Jumper Cables
- Steckbrett/er


![](https://github.com/FabianSchieder/Arduino_TickTackToe/blob/main/Gesamt.jpg "Gesamte Schaltung")


Zuerst einmal habe ich mit dem LED Spielfeld angefangen.
Hierzu sind jeweis eine weiße und eine blau LED nebeneinander und bilden gemeinsam sozusagen ein Feld.
Die Kathoden sind alle miteinander verbunden. Die Anoden der jeweiligen LEDs sind mit den Pins des Arduinos verbunden.
Die genaue Pin-Belegung sieht man im Code in den 2-Dimensionalen-Arrays.


![](https://github.com/FabianSchieder/Arduino_TickTackToe/blob/main/LED%20Feld.jpg "LED Spielfeld")


Als Nächstes habe ich mit um die Eingabe gekümmert. Eigendlich wollte ich ein 3x3 Feld machen, dafür hatte ich aber nicht genügend Platz.
Hier stellen die ersten drei Knöpfe die erste Reihe, die zweiten drei die Zweite usw... .
Um zu vermeiden, dass ohne dem Drücken eines Knopfes der Eingang als HIGH erkannt wird habe ich zwischen Eingang bzw. Ausgang des Knopfes einen
Pull-Down-Wiederstand. In diesem Fall haben sie 330Ohm, da ich diese im Moment parat hatte.

Die beiden LEDs unten rechts sind dafür da, anzuzeigen welcher Spieler gerade an der Reihe ist.


![](https://github.com/FabianSchieder/Arduino_TickTackToe/blob/main/Buttons.jpg "Eingabe")


Nun zum Code:




