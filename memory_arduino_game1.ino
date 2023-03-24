/* Name: Nikhil Sinclair
 * Date: 12/04/22
 * Purpose: To create a game to test the users memory with which lights are being turned on
 */


//defined constants
#define LED_LOSE 13
#define LEDR 12
#define LEDY 11
#define LEDB 10
#define LEDG 9
#define LED_WIN 8

#define pb_red 7
#define pb_yellow 6
#define pb_blue 5
#define pb_green 4

#define TRUE 1
#define FALSE 0

#define inactive_time 10000

//global variables
int roundCount = 0; // variable used to keep track of the round of the game
int lightSequence[5]; // array which is used to store the random light pin values

//function prototypes
void lightsOn(void);
void lightsOff(void);
void blinkGreen(void);
int lightHistory(void);
int randomLight(void);
int buttonCheck(void);
int lightCheck(void);


//initialization
void setup()
{
  //setting up the buttons for the LED's as input devices 
  pinMode(pb_red, INPUT);
  pinMode(pb_yellow, INPUT);
  pinMode(pb_blue, INPUT);
  pinMode(pb_red, INPUT);
  
  //setting up each LED as output devices 
  pinMode(LED_WIN, OUTPUT);
  pinMode(LED_LOSE, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDY, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDG, OUTPUT);

  randomSeed(analogRead(A0)); // used to initalize random number generation
}


/*
 * Purpose: Turns on the four colour LED's to indicate the game has started
 */

void lightsOn(void) 
{
 	digitalWrite(LEDR, HIGH);
  	digitalWrite(LEDY, HIGH);
  	digitalWrite(LEDB, HIGH);
  	digitalWrite(LEDG, HIGH);
  	delay(2000);
}


/*
 * Purpose: Turns off the four coloured LED's after it has been indicated that the game has started
 */

void lightsOff(void) 
{
  	digitalWrite(LEDR, LOW);
  	digitalWrite(LEDY, LOW);
  	digitalWrite(LEDB, LOW);
  	digitalWrite(LEDG, LOW);
  	delay(2000);
}


/*
 * Purpose: This function picks a random light out of the four coloured LED's 
 * Returns: The pin of the random light 
 */

int randomLight(void)
{
  	int light; // variable used to store the random light that is picked
  	light = random(9, 13);
  	
  	return light; 
  
}


/*
 * Purpose: This function checks to see if the user has interacted with any of the buttons
 * Returns: True if a button is clicked by the user and False if the user has not clicked a button
 */

int buttonClicked(void) {

  // the boolean expression below is used to see if any of the buttons have been pressed
  if(digitalRead(pb_green) == LOW && digitalRead(pb_blue) == LOW && digitalRead(pb_yellow) == LOW && digitalRead(pb_red) == LOW) {
    return FALSE;
  }
  
  else {
    return TRUE;
  }
  
}


/*
 * Purpose: This function stores the pins of the randoms lights in an array, whos idex corresponds to the round of the game
 * Returns: True if a button is clicked during the light flashing sequence and flase if no buttons are clicked during the light flashing sequence
 */

int lightHistory(void)
{
 
  lightSequence[roundCount] = randomLight(); // stores the randomly generated light in the array lightSequence
  
  // the loop below is used to flash the randoms lights for every round
  for(int count = 0; count <= roundCount; count++) {
    
      unsigned long originalTime = millis(); // here we introduce variable "orginalTime" which stores the time the light flashing sequence started it 
    
      delay(500); // small delay before the rounds light sequence starts happening
      digitalWrite(lightSequence[count], HIGH); // turns on the random light for 2 seconds
    
      // the loop below another way of writing a delay for 2000ms, but allows us to also have a condition within it, since it is a loop 
      while(millis() - originalTime < 2000) {
     	
        // the boolean expression below checks to see if the user clicked any buttons during the flashing lights sequence
    	if(lightCheck() == TRUE && buttonClicked() == TRUE) {
     
          while(buttonClicked() == TRUE) {
          	digitalWrite(clickedButton() + 5, HIGH); // turns on the led which was clicked by the user if the user pushed a button during the light sequence
          	digitalWrite(clickedButton() + 5, LOW); // turns of the led the user turned on
          }
          
          	digitalWrite(lightSequence[count], LOW); // turns off the random light which is apart of the sequence
          
      		return TRUE; // returns true if buttons are clicked during light sequence
          
    	}
        
      }
      
      digitalWrite(lightSequence[count], LOW); // turns off the random light
      delay(200);
      
  }
  
  roundCount++; // increases the round of the game
  return FALSE; // returns false if the user did not click any push buttons during the flashing light sequence
  
}

/*
 * Purpose: Checks if any of the 4 LED lights are on and displaying the sequence 
 * Return: True if the lights are flashing the sequence and false if the sequence of flashing lights is done
 */

int lightCheck(void) {
	
  if(digitalRead(9) == HIGH || digitalRead(10) == HIGH || digitalRead(11) == HIGH || digitalRead(12) == HIGH) {
    return TRUE;
  }
  
  else {
    return FALSE;
  }
  
}

/*
 * Purpose: This function flashes the green light 3 times if the user wins the game 
 */

void blinkWin(void)
{
  	digitalWrite(LED_WIN, HIGH);
  	delay(1000);
  
  	digitalWrite(LED_WIN, LOW);
  	delay(1000);
  
  	digitalWrite(LED_WIN, HIGH);
  	delay(1000);
  
  	digitalWrite(LED_WIN, LOW);
  	delay(1000);
  
  	digitalWrite(LED_WIN, HIGH);
  	delay(1000);

  	digitalWrite(LED_WIN, LOW);
  	delay(1000);
  
}


/*
 * Purpose: This function flashes the red light 3 times if the user loses the game
 */

void blinkLoss(void)
{
	digitalWrite(LED_LOSE, HIGH);
  	delay(1000);
  
  	digitalWrite(LED_LOSE, LOW);
  	delay(1000);
  
  	digitalWrite(LED_LOSE, HIGH);
  	delay(1000);
  
  	digitalWrite(LED_LOSE, LOW);
  	delay(1000);
  
  	digitalWrite(LED_LOSE, HIGH);
  	delay(1000);
  
  	digitalWrite(LED_LOSE, LOW);
  	delay(1000);
}

/*
 * Purpose: This function is used to detect which button has been clicked by the user 
 * Returns: The button which the user has clicked 
 */

int clickedButton(void) {
  
  int button; // this variable is used to store the button which has been clicked by the user
  
  // the loop below is used to check the status of all of the buttons 
  for(int count = pb_green; count <= pb_red; count++) {
    if(digitalRead(count) == HIGH) {
    	button = count;
    }
  }
  
  return button;
}


/*
 * Purpose: This function checks if the right button/buttons has been clicked and also keeps track of the time for which no button has been clicked 
 * Returns: The return is False if the user either clicks the wrong buttons or has over 10 seconds of inactivity. The function returns True if the user succesfully clicks the right buttons under 10 seconds
 */

int buttonCheck(void) {
  
  int buttonNum; // Variable used to store the button which the user must click, given the light that blinks 
  int lightCount = 0; // Variable used to refer to the randomLights which are stored in the array
  unsigned long timeElapsed = millis(); // this variable is used to store the time at which the randoms lights have stopped blinking (in other words the time when the user starts to be timed)
  
  // blow is a loop which allows the sequence to occur to the right amount times (for exmaple in round 3, 3 lights will blink and 3 buttons will be checked)
  while(lightCount < roundCount) {
    
    // below is an infinite while loop which is breaked or early returned if the user interacts with the buttons or the time limit is exceeded
  	while(TRUE) {
 
      buttonNum = lightSequence[lightCount] - 5; // Computes which button needs to be clicked by the user based on the random light stored in the array
         
      // the boolean expression below is used to check if the user has clicked a button
      if(buttonClicked() == TRUE) {
      
        // the boolean expression below is used to check if the user has clicked the right button 
        if(digitalRead(buttonNum) == HIGH) {
          
          // the loop below excecutes if the user holds the button down
          while(digitalRead(buttonNum)==HIGH){
            digitalWrite(lightSequence[lightCount], HIGH); // Turns on the LED which corresponds to the button the user has clicked 
          }
          
          	digitalWrite(lightSequence[lightCount], LOW); // turns the LED which corresponds to the button clicked off after button is let go of
          	lightCount++; // increased light count so the same process can be repeated for the second random light in the sequence
          	break; // ends the infinite while loop if the user has clicked the correct buttons
      	}
    
      	else {
          
          while(digitalRead(clickedButton()) == HIGH){
            digitalWrite(clickedButton() + 5, HIGH); // Turns on the LED which corresponds to the button the user has clicked 
            digitalWrite(clickedButton() + 5, LOW); // Turns off the LED which corresponds to the button the user clicked after it has been on
            }
         
          
      		roundCount = 0; // Here maxLight is set to 0, if the user clicks the wrong button, so the loop does not execute anymore and the game will reset 
      		return FALSE; // returns False if user clicks the wrong buttons 
      	}
        
      }
      
       else if(millis() - timeElapsed > inactive_time) {
        	roundCount = 0; // Here maxLight is set to 0, if the user clicks the wrong button, so the loop does not execute anymore and the game will reset 
      		return FALSE; // returns False if user fails to meet 10 second time limit
        }
     
  	}
  
  
  }
  
  return TRUE; // returns TRUE if user has entered the right buttons under 10 second time limit
 
}



//main program loop
void loop()
{
  
  if(roundCount == 0) {
  	lightsOn(); // Turns all four LED's on if it is the start of the game 
  	lightsOff(); // Turns the four LED's off because it is time to start the game
  }
  
  
  if(lightHistory() == TRUE) {
    blinkLoss(); // if the user clicks a button during the blinking sequence the function blinkLoss() will be called to indicate they lost
  }
  
  if(buttonCheck() == FALSE) {
  	blinkLoss(); // On a loss the red light will blink 3 times if the user enters the wrong buttons or exceeds the time limit of 10 sec
  }
  
  
  if(roundCount == 5) {
  	blinkWin(); // On a win the green light will blink 3 times if the buttons are entered correctly under the 10 second time limit for 5 consecutive round
    roundCount = 0; // sets roundCount to 0 so the game will restart
  } 
 
  
}





