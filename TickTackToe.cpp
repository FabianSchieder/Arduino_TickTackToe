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
