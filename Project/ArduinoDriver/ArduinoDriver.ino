/* Prototypes */

String retrieveCommands (const char* url);
void executeAction(char command, char* parameter);

char* concatenate(const char * char1, const char * char2);
int extractNextParam(String commands);
long* parseLong(char* string);

/* BUTTONS DECLARATIONS */

const int BTN_UP = 2;
const int BTN_DOWN = 3;
const int BTN_LEFT = 4;
const int BTN_RIGHT = 5;
const int BTN_X = 6;
const int BTN_O = 7;
const int BTN_H = 8;

const int BTN_POWER = 9;

/************ CONSTANTES ************/

const unsigned long PRESS_BTN_DURATION_MILLIS = 500;
const unsigned long PAUSE_DURATION_AFTER_BTN_PRESS_MILLIS = 500;
const char * URL_COMMANDS = "http://localhost:8083/getCommands?token=test&contentType=I" ;
const unsigned long SLEEP_WORK_FINISHED = 3600000;

/************************/
typedef struct Command Command;
struct Command {
  char character;
  int* parameter;
};

/* Global variables */
bool isFirstLoopTurn;
int i = 0; //index of character in command sequence

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(BTN_UP, OUTPUT);
  pinMode(BTN_DOWN, OUTPUT);
  pinMode(BTN_LEFT, OUTPUT);
  pinMode(BTN_RIGHT, OUTPUT);
  pinMode(BTN_X, OUTPUT);
  pinMode(BTN_O, OUTPUT);
  pinMode(BTN_H, OUTPUT);
  pinMode(BTN_POWER, OUTPUT);

  Serial.begin(9600); 
  
  isFirstLoopTurn = true;
}

// the loop function runs over and over again forever
void loop() {

  if(!isFirstLoopTurn) {
    Serial.print("Work finished, sleep ");
    Serial.print(SLEEP_WORK_FINISHED / 1000);
    Serial.println(" seconds");
    delay(SLEEP_WORK_FINISHED);
    return;
  }
  isFirstLoopTurn = false;

  // Retrieve all the commands from the driver WS
  String commands = retrieveCommands(URL_COMMANDS);


  // Escape all the characters until detecting '{' char
  while(i < commands.length() && commands.charAt(i) != '{') {
    i++;
  }

  // Check if commands sequence is well received
  if(++i >= commands.length()) {
    Serial.println("The command sequence has not been found");
    return;
  }

  Command * command;
    
  // Main command processing
  bool doProcessCharacterCommand = true;
  for(; i < commands.length(); i++) {

    char character = commands.charAt(i);
    Serial.println("");
    if(doProcessCharacterCommand) { // A character
      if(command != NULL)
        free(command);
      command = (Command*) malloc(sizeof(Command));
      command->character = character;
      command->parameter = NULL;
      
    }else { // a separator, a parameter or the end of the sequence

      if((character == ',')) {
        int param = extractNextParam(commands);
        command->parameter = (int*) malloc(sizeof(int));
        *command->parameter = param;

        character = commands.charAt(i);
      }

      //Execution of the command
      executeAction(command);

      // Test ending character
      if(character != '-') { // End of reading
        if(character == '}') {
          Serial.println("The end of the sequence has been well reached");
        }else {
          Serial.println("An incorrect character has been reached");
        }
        Serial.println("End of sequence reading");
        break;
      }
    }
    Serial.println("");
    doProcessCharacterCommand = !doProcessCharacterCommand;
  }

  Serial.println("Loop finished");
}


// Private functions
/*
char* getParameter(char * commands, int currentIndex, int lengthString) {
  if(currentIndex + 1 >= lengthString){
    return NULL;
  }

  if()
}
*/

char* concatenate(const char * char1, const char * char2) {
  int totalLength = strlen(char1) + strlen(char2);
  char* result = (char*) malloc(totalLength * sizeof(char));
  return result;
}
