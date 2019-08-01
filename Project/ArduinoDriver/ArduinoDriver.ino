/* Prototypes */

String retrieveCommands (const char* url);
void executeAction(char command, char* parameter);

int* extractNextParam(String commands);
long* parseLong(char* string);
void blinkLED(int pin, int countSwitchOn, double frequency);

void Log(String text, int valueToInsert);
void Log(String text, char* valueToInsert);
void Log(String text, String valueToInsert);

bool processCommandsExecution(String commands);
void shutdownArduino();

/* PIN (buttons) DECLARATIONS */

const int BTN_UP = 2;
const int BTN_DOWN = 3;
const int BTN_LEFT = 4;
const int BTN_RIGHT = 5;
const int BTN_X = 6;
const int BTN_O = 7;
const int BTN_H = 8;

const int BTN_POWER = 9;

const int LED_RED_PIN = 10;
const int SHUTDOWN_ARDUINO_PIN = 11;

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
unsigned int i = 0; //index of character in command sequence

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

  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(SHUTDOWN_ARDUINO_PIN, OUTPUT);

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

  // Process the commands execution
  if(!processCommandsExecution(commands)) {
    blinkLED(LED_RED_PIN, 5, 6);
    Serial.println("An error occured during the processing of 'processCommandsExecution' function");
    return;
  }

  // Disable the current providing the Arduino
  shutdownArduino();

  Serial.println("Loop finished");
}


// Private functions

// Returns false if the execution has thrown an error
bool processCommandsExecution(String commands) {
  
  // Escape all the characters until detecting '{' char
  while(i < commands.length() && commands.charAt(i) != '{') {
    i++;
  }

  // Check if commands sequence is well received
  if(++i >= commands.length()) {
    Serial.println("The command sequence has not been found");
    return false;
  }
  
  Command * command = NULL;
    
  // Main command processing
  bool doProcessCharacterCommand = true;
  for(; i < commands.length(); i++) {

    char character = commands.charAt(i);
    
    if(doProcessCharacterCommand) { // A character
      if(command != NULL)
        free(command);
      command = (Command*) malloc(sizeof(Command));
      command->character = character;
      command->parameter = NULL;
      
    }else { // a separator, a parameter or the end of the sequence

      if((character == ',')) {
        int* param = extractNextParam(commands);
        if(param == NULL) {
          Serial.println("The 'extractNextParam' function returned a NULL int address");
          return false;
        }
        command->parameter = (int*) malloc(sizeof(int));
        command->parameter = param;

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
    doProcessCharacterCommand = !doProcessCharacterCommand;
  }
  
  return true;
}


void shutdownArduino() {
  digitalWrite(SHUTDOWN_ARDUINO_PIN, HIGH);
}
