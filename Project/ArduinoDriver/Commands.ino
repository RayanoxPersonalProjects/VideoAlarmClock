void pressButton(int pinCommand) {
  Serial.print("Press PIN ");
  Serial.println(pinCommand);
  
  digitalWrite(pinCommand, HIGH);
  delay(PRESS_BTN_DURATION_MILLIS);
  digitalWrite(pinCommand, LOW);

  Serial.print("Release PIN ");
  Serial.println(pinCommand);

  delay(PAUSE_DURATION_AFTER_BTN_PRESS_MILLIS);
}

void executeAction(Command * command) {
  
  switch(command->character){
    case 'U':
      pressButton(BTN_UP);
      break;
    case 'D':
      pressButton(BTN_DOWN);
      break;
    case 'L':
      pressButton(BTN_LEFT);
      break;
    case 'R':
      pressButton(BTN_RIGHT);
      break;
    case 'X':
      pressButton(BTN_X);
      break;
    case 'O':
      pressButton(BTN_O);
      break;
    case 'H':
      pressButton(BTN_H);
      break;
    case 'P':
      pressButton(BTN_POWER);
      break;
      
    case 'S':
      if(command->parameter == NULL) {
        Serial.println("Parameter could not be null with this command");
        exit;
      }
      unsigned long delayTimeSeconds = parseLong(*command->parameter);
      delay(delayTimeSeconds * 1000);
      break;
    case 'K':
      Serial.println("Command not implemented yet");
      exit;
    case 'G':
      Serial.println("Command not implemented yet");
      exit;
      
    default:
      Serial.println("The command received is unknown");
      exit;
  }
}

long* parseLong(char* string) {
  long* i;
  sscanf(string, "%l", i);
  return i;
}

int extractNextParam(String commands) {
  int result = NULL;
  String parameterString = "";

  i++; // Go to next char
  
  while(i < commands.length()) {
    if(commands.charAt(i) >= 48 && commands.charAt(i) <= 57){ // A numerical character
      parameterString += commands.charAt(i);
      i++;
    }else {
      break;
    }
  }

  if(parameterString != "") {
    //conversion to result
    result = parameterString.toInt();
  }

  return result;
}
