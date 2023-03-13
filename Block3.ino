#include <LiquidCrystal.h>

#define rockButton 9
#define paperButton 8
#define scissorsButton 7
#define finalChoice 6

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int player1Score = 0;
unsigned int player1Final = 0;
int player2Score = 0;
unsigned int player2Final = 0;
int state = 0;



//add delay after pressing the finalChoice button
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool buttonState;
bool lastButtonState = LOW;



const int win_matrix[3][3] = {
  // Column = Player1 choose rock, paper or scissors
  // Row = Player2 choose rock paper or scissors
  { 0,                  1,                  -1 },
  { -1,                 0,                   1 }, 
  { 1,                  -1,                  0 }
};



void setup()
{
  Serial.begin(9600);
  pinMode(rockButton, INPUT);
  pinMode(paperButton, INPUT);
  pinMode(scissorsButton, INPUT);
  pinMode(finalChoice, INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
}



// game functions
void player1Wins(void)
{
  player1Score += 1;
  lcd.setCursor(0,0);
  lcd.print("Player 1 Wins!");
  lcd.setCursor(0,1);
  lcd.print("POGGERS");
}

void player2Wins(void)
{
  player2Score += 1;
  lcd.setCursor(0,0);
  lcd.print("Player 2 Wins!");
  lcd.setCursor(0,1);
  lcd.print("POGGERS");
}

void playersTied(void)
{
  lcd.setCursor(0,0);
  lcd.print("You tied!");
  lcd.setCursor(0,1);
  lcd.print("No winners LMAOO");
}

void displayScores(void)
{
  lcd.setCursor(0,0);
  lcd.print(player1Score);
  lcd.setCursor(0,1);
  lcd.print(player2Score);
}



// add debounce button function here

int readPlayerFinalChoice(void)
{
  
}

//game loop
void loop()
{
  
  
  
  if (state == 0) // Player 1 makes a choice
  {
    lcd.setCursor(0,0);
    lcd.print("pick your poison");
    lcd.setCursor(0,1);
    lcd.print("guzzo 1");
	
    // finalChoice button stores answer to variable player1Final 
    while (digitalRead(finalChoice) == LOW) 
    {
      player1Final = (digitalRead(rockButton) == HIGH) ? 0 : (digitalRead(paperButton) == HIGH) ? 1 : -1; // Map button press to choice (0 for rock, 1 for paper, -1 for scissors)
    }
    
    state = 1;
  }

  if (state == 1) // Player 2 makes a choice
  {
    lcd.setCursor(0,0);
    lcd.print("pick your poison");
    lcd.setCursor(0,1);
    lcd.print("guzzo 2");
    
    // finalChoice button stores answer to variable player2Final  
	
    while (!digitalRead(finalChoice)) 
    {
      player2Final = (digitalRead(rockButton) == HIGH) ? 0 : (digitalRead(paperButton) == HIGH) ? 1 : -1;
    }

    state = 2;
  }

  if (state == 2) // Check who the winner is
  {
    // if check player1 Win == True
    // player1Wins();

    // else if check player2 wins == True
    // player2Wins();

    // else
    // playersTied();

    int outcome = win_matrix[player1Final][player2Final];  // Determines the winner using the matrix
    if (outcome == -1) 
      player1Wins();
    else if (outcome == 1) 
      player2Wins();
    else // (outcome == 0)
      playersTied();
    


    displayScores();
    delay(5000);  // After 5 seconds, the game starts again
    state = 0;  // This loops back to the beginning
  }
}
