#include <LiquidCrystal.h>

#define rockButton 9
#define paperButton 8
#define scissorsButton 7

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int player1Score = 0;
int player1Final = 0;
int player2Score = 0;
int player2Final = 0;
int state = 0;



void setup()
{
  Serial.begin(9600);
  pinMode(rockButton, INPUT);
  pinMode(paperButton, INPUT);
  pinMode(scissorsButton, INPUT);
  lcd.begin(16, 2);
}



// game functions
void player1Wins(void)
{
  lcd.clear();
  player1Score += 1;
  lcd.setCursor(0,0);
  lcd.print("Player 1 Wins!");
  lcd.setCursor(0,1);
  lcd.print("POGGERS");
}

void player2Wins(void)
{
  lcd.clear();
  player2Score += 1;
  lcd.setCursor(0,0);
  lcd.print("Player 2 Wins!");
  lcd.setCursor(0,1);
  lcd.print("POGGERS");
}

void playersTied(void)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("You tied!");
  lcd.setCursor(0,1);
  lcd.print("No winners LMAOO");
}

void displayScores(void)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(player1Score);
  lcd.setCursor(0,1);
  lcd.print(player2Score);
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
	
    
    while (player1Final == 0 && player2Final == 0) 
    {
      if (digitalRead(rockButton) == HIGH)
      {
        player1Final = 1;
      }
      
      else if (digitalRead(paperButton) == HIGH)
      {
        player1Final = 2;
      }
      
      else if (digitalRead(scissorsButton) == HIGH)
      {
      	player1Final = 3;
      }
    }
    
    Serial.print(rockButton);
    delay(100);
    state = 1;
  }

  if (state == 1) // Player 2 makes a choice
  {
    lcd.setCursor(0,0);
    lcd.print("pick your poison");
    lcd.setCursor(0,1);
    lcd.print("guzzo 2");
    
    // finalChoice button stores answer to variable player2Final once pressed  
	
    while (player2Final == 0) 
    {
      if (digitalRead(rockButton) == HIGH)
      {
        player2Final = 1;
      }
      
      else if (digitalRead(paperButton) == HIGH)
      {
        player2Final = 2;
      }
      
      else if (digitalRead(scissorsButton) == HIGH)
      {
      	player2Final = 3;
      }
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

    
    
    // Player 1 chose Rock and Player 2 chose Paper
    if (player1Final == 1 && player2Final == 2) {
      player2Wins();
    }
     
    // Playe 1 chose Rock and Player 2 chose Scissors
    else if (player1Final == 1 && player2Final == 3) {
      player1Wins();
    }
      
    // Player 1 chose Paper and Player 2 chose rock
    else if (player1Final == 2 && player2Final == 1) {
      player1Wins();
    }
      
    // Player 1 chose Paper and Player 2 chose Scissors
    else if (player1Final == 2 && player2Final == 3) {
      player2Wins();
    }
      
    //Player 1 chose Scissors and Player 2 chose Rock
    else if (player1Final == 3 && player2Final == 1) {
      player2Wins();
    }
      
    //Player 1 chose Scissors and Player 2 chose Paper
    else if (player1Final == 3 && player2Final == 2) {
      player1Wins();
    }
      
    else { //Player 1 and 2 made the same choice
      playersTied();
    }
      
    delay(5000);
    displayScores();
    delay(5000);  // After 5 seconds, the game starts again
    lcd.clear();
    player1Final = 0;
    player2Final = 0;
    state = 0;  // This loops back to the beginning
  }
}
