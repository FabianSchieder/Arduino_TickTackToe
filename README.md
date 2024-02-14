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


Hier habe ich die Variablen für das Projekt erstellt.


```c++
const int pitchWhitePins[3][3] = {  {22, 28, 34},        // Dieses Array ist für die Pins des weißen Teil des Spielfeldes.
                                    {24, 30, 36},
                                    {26, 32, 38}, };                              

const int pitchBluePins[3][3] = {  {23, 29, 35},         // Dieses für den Blauen Teil.
                                   {25, 31, 37},
                                   {27, 33, 39}, }; 

int pitchWhite[3][3] = {  {false, false, false},         // Das Array ist da, um einstellen zu können welche LEDs leuchten und welche nicht.
                          {false, false, false},         // true = LED an  |  false = LED aus
                          {false, false, false}, };  

int pitchBlue[3][3] = {  {false, false, false},
                         {false, false, false},
                         {false, false, false}, };                                

const int buttons[3][3] = { {40, 41, 42},                 // Hier sind alle Pins für die Eingabeknöpfe.
                            {43, 44, 45},
                            {46, 47, 48}  };                                                              

const int playerWhite = 51;                               // Pins für die LEDs für den aktuellen Spieler.
const int playerBlue = 50;

int x;
int y;

char currPlayer = 'B';

const int reset = 11;                                     // Dieser Pin ist mit dem Reset Pin verbunden.

```


Als nächstes wird in der "void loop();" Funktion angegeben welche Pins INPUTs und welche OUTPUTs sind

```c++

void setup() 
{
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      pinMode(pitchBluePins[i][j], OUTPUT);
    }
  }

  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      pinMode(pitchWhitePins[i][j], OUTPUT);
    }
  }

  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      pinMode(buttons[i][j], INPUT);
    }
  }

  pinMode(playerWhite, OUTPUT);
  pinMode(playerBlue, OUTPUT);
}

```


Die "void loop();" Funktion ist hier sozusagen der "Leitfaden" des Programms. Auf die Funktionalität werde ich nicht näher eingehen.

```c++

void loop() 
{
  if(currPlayer == 'B')
  {
    digitalWrite(playerBlue, HIGH);
    digitalWrite(playerWhite, LOW);
  }
  else if(currPlayer == 'W')
  {
    digitalWrite(playerWhite, HIGH);
    digitalWrite(playerBlue, LOW);
  }
  
  printPitch();
  input();
  printPitch(); 
  delay(200);
  verify();
}

void printPitch()
{
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      if(pitchWhite[i][j] == true)
      {
        digitalWrite(pitchWhitePins[i][j], HIGH);

        if(currPlayer == 'B')
        {
          digitalWrite(playerBlue, HIGH);
          digitalWrite(playerWhite, LOW);
        }
        else if(currPlayer == 'W')
        {
          digitalWrite(playerWhite, HIGH);
          digitalWrite(playerBlue, LOW);
        }
      }
    }
  }

```

Die "void printPitch();" Funktion ist dafür da, die richtigen LEDs am Spielfeld anzusteuern.

```c++

void printPitch()
{
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      if(pitchWhite[i][j] == true)
      {
        digitalWrite(pitchWhitePins[i][j], HIGH);

        if(currPlayer == 'B')
        {
          digitalWrite(playerBlue, HIGH);
          digitalWrite(playerWhite, LOW);
        }
        else if(currPlayer == 'W')
        {
          digitalWrite(playerWhite, HIGH);
          digitalWrite(playerBlue, LOW);
        }
      }
    }
  }

  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      if(pitchBlue[i][j] == true)
      {
        digitalWrite(pitchBluePins[i][j], HIGH);
      }
    }
  }
}

```

Die "void input();" Funktion kümmert sich um die Eingabe durch die Buttons.

```c++

void input()
{
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      if(digitalRead(buttons[i][j]) == HIGH)
      {
        x = i;
        y = j;

        if(currPlayer == 'B')
        {
          pitchBlue[x][y] = true;
          currPlayer = 'W';
          break;
        }
        else if(currPlayer == 'W')
        {
          pitchWhite[x][y] = true;
          currPlayer = 'B';
          break;
        }

        break;
      }
    }
  }
}

```

Die funktion "void verify();" ist die kniffligste Stelle des Codes. Hier werden zuerst die Blauen und dann die Roten LEDs überprüft, ob
ein Spieler gewonnen hat oder nicht.

```c++

void verify()
{
  for (int i = 0; i < 3; i++)
  {
  	if (pitchBlue[i][0] != false && pitchBlue[i][0] == pitchBlue[i][1] && pitchBlue[i][1] == pitchBlue[i][2])
  	{
  		winningScreen();
  	}
  }

  for (int i = 0; i < 3; i++)
  {
  	if (pitchBlue[0][i] != false && pitchBlue[0][i] == pitchBlue[1][i] && pitchBlue[1][i] == pitchBlue[2][i])
  	{
  		winningScreen();
  	}
  }

  if (pitchBlue[0][0] != false && pitchBlue[0][0] == pitchBlue[1][1] && pitchBlue[1][1] == pitchBlue[2][2])
  {
  	winningScreen();
  }

  if (pitchBlue[0][2] != false && pitchBlue[0][2] == pitchBlue[1][1] && pitchBlue[1][1] == pitchBlue[2][0])
  {
  	winningScreen();
  }



  for (int i = 0; i < 3; i++)
  {
  	if (pitchWhite[i][0] != false && pitchWhite[i][0] == pitchWhite[i][1] && pitchWhite[i][1] == pitchWhite[i][2])
  	{
  		winningScreen();
  	}
  }

  for (int i = 0; i < 3; i++)
  {
  	if (pitchWhite[0][i] != false && pitchWhite[0][i] == pitchWhite[1][i] && pitchWhite[1][i] == pitchWhite[2][i])
  	{
  		winningScreen();
  	}
  }

  if (pitchWhite[0][0] != false && pitchWhite[0][0] == pitchWhite[1][1] && pitchWhite[1][1] == pitchWhite[2][2])
  {
  	winningScreen();
  }

  if (pitchWhite[0][2] != false && pitchWhite[0][2] == pitchWhite[1][1] && pitchWhite[1][1] == pitchWhite[2][0])
  {
  	winningScreen();
  }
}

```

Die Funktion "void winningScreen();" wird aufgerufen, wenn ein Spieler gewonnen hat. Am Ende der Funktion wird der Reset Pin angesteuert
und das ganze Programm fängt wieder von vorne an.

```c++

void winningScreen()
{
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      pitchBlue[i][j] = true;
      pitchWhite[i][j] = true;
    }
  }

  printPitch();
  delay(200);
  printPitch();

  for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3; j++)
      {
        pitchBlue[i][j] = false;
        pitchWhite[i][j] = false;
      }
    }

  delay(200);
  printPitch();

    for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      pitchBlue[i][j] = true;
      pitchWhite[i][j] = true;
    }
  }

  printPitch();
  delay(200);
  analogWrite(reset, -255);
}

```


Hier der ganze Code:

```c++

const int pitchWhitePins[3][3] = {  {22, 28, 34},
                                    {24, 30, 36},
                                    {26, 32, 38}, };                              

const int pitchBluePins[3][3] = {  {23, 29, 35},
                                   {25, 31, 37},
                                   {27, 33, 39}, }; 

int pitchWhite[3][3] = {  {false, false, false},
                          {false, false, false},
                          {false, false, false}, };  

int pitchBlue[3][3] = {  {false, false, false},
                         {false, false, false},
                         {false, false, false}, };                                

const int buttons[3][3] = { {40, 41, 42},
                            {43, 44, 45},
                            {46, 47, 48}  };                                                              

const int playerWhite = 51;
const int playerBlue = 50;

int x;
int y;

char currPlayer = 'B';

const int reset = 11;

void printPitch();
void input();
void verify();
void winningScreen();

void setup() 
{
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      pinMode(pitchBluePins[i][j], OUTPUT);
    }
  }

  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      pinMode(pitchWhitePins[i][j], OUTPUT);
    }
  }

  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      pinMode(buttons[i][j], INPUT);
    }
  }

  pinMode(playerWhite, OUTPUT);
  pinMode(playerBlue, OUTPUT);
}

void loop() 
{
  if(currPlayer == 'B')
  {
    digitalWrite(playerBlue, HIGH);
    digitalWrite(playerWhite, LOW);
  }
  else if(currPlayer == 'W')
  {
    digitalWrite(playerWhite, HIGH);
    digitalWrite(playerBlue, LOW);
  }
  
  printPitch();
  input();
  printPitch(); 
  delay(200);
  verify();
}

void printPitch()
{
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      if(pitchWhite[i][j] == true)
      {
        digitalWrite(pitchWhitePins[i][j], HIGH);

        if(currPlayer == 'B')
        {
          digitalWrite(playerBlue, HIGH);
          digitalWrite(playerWhite, LOW);
        }
        else if(currPlayer == 'W')
        {
          digitalWrite(playerWhite, HIGH);
          digitalWrite(playerBlue, LOW);
        }
      }
    }
  }

  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      if(pitchBlue[i][j] == true)
      {
        digitalWrite(pitchBluePins[i][j], HIGH);
      }
    }
  }
}

void input()
{
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      if(digitalRead(buttons[i][j]) == HIGH)
      {
        x = i;
        y = j;

        if(currPlayer == 'B')
        {
          pitchBlue[x][y] = true;
          currPlayer = 'W';
          break;
        }
        else if(currPlayer == 'W')
        {
          pitchWhite[x][y] = true;
          currPlayer = 'B';
          break;
        }

        break;
      }
    }
  }
}

void verify()
{
  for (int i = 0; i < 3; i++)
  {
  	if (pitchBlue[i][0] != false && pitchBlue[i][0] == pitchBlue[i][1] && pitchBlue[i][1] == pitchBlue[i][2])
  	{
  		winningScreen();
  	}
  }

  for (int i = 0; i < 3; i++)
  {
  	if (pitchBlue[0][i] != false && pitchBlue[0][i] == pitchBlue[1][i] && pitchBlue[1][i] == pitchBlue[2][i])
  	{
  		winningScreen();
  	}
  }

  if (pitchBlue[0][0] != false && pitchBlue[0][0] == pitchBlue[1][1] && pitchBlue[1][1] == pitchBlue[2][2])
  {
  	winningScreen();
  }

  if (pitchBlue[0][2] != false && pitchBlue[0][2] == pitchBlue[1][1] && pitchBlue[1][1] == pitchBlue[2][0])
  {
  	winningScreen();
  }



  for (int i = 0; i < 3; i++)
  {
  	if (pitchWhite[i][0] != false && pitchWhite[i][0] == pitchWhite[i][1] && pitchWhite[i][1] == pitchWhite[i][2])
  	{
  		winningScreen();
  	}
  }

  for (int i = 0; i < 3; i++)
  {
  	if (pitchWhite[0][i] != false && pitchWhite[0][i] == pitchWhite[1][i] && pitchWhite[1][i] == pitchWhite[2][i])
  	{
  		winningScreen();
  	}
  }

  if (pitchWhite[0][0] != false && pitchWhite[0][0] == pitchWhite[1][1] && pitchWhite[1][1] == pitchWhite[2][2])
  {
  	winningScreen();
  }

  if (pitchWhite[0][2] != false && pitchWhite[0][2] == pitchWhite[1][1] && pitchWhite[1][1] == pitchWhite[2][0])
  {
  	winningScreen();
  }
}

void winningScreen()
{
  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      pitchBlue[i][j] = true;
      pitchWhite[i][j] = true;
    }
  }

  printPitch();
  delay(200);
  printPitch();

  for(int i = 0; i < 3; i++)
    {
      for(int j = 0; j < 3; j++)
      {
        pitchBlue[i][j] = false;
        pitchWhite[i][j] = false;
      }
    }

  delay(200);
  printPitch();

    for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      pitchBlue[i][j] = true;
      pitchWhite[i][j] = true;
    }
  }

  printPitch();
  delay(200);
  analogWrite(reset, -255);
}

```
