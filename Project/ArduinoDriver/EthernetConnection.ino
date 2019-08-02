char urlTarget[] = "rayaneServer"; // To work, must be added in DNS (local)
char ipTarget[] = "51.77.146.48";

uint8_t Ethernet::buffer[400]; // configure buffer size to 400 octets
static uint8_t mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 }; // define (unique on LAN) hardware (MAC) address


// The char** will probably be changed to an other type
String retrieveCommands (const char* url) {
  /*char commandSeq [] = "test {R-R-L-X-S,5-H-L-X-X}";
  char * commands = malloc(strlen(commandSeq) * sizeof(char));
  strcpy(commands, commandSeq);
  return commands;*/
  
  return "test {R-R-L-X-S,5-H-L-X-X}";
}


/***** SETUP *****/
bool initNetwork() {

  /***************************/
  /* Arduino network config */
  /***************************/
  
  if (ether.begin(sizeof Ethernet::buffer, mymac, ETHERNET_CS_PIN) == 0) {
    Serial.println(F("Failed to access Ethernet controller"));
    return false;
  }

  Serial.println("DHCP setting up..");
  if (!ether.dhcpSetup()) {
    Serial.println(F("DHCP failed"));
    return false;
  }
  
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);

  /***************************/
  /* Server targetted config */
  /***************************/

  if(strlen(urlTarget) != 0) {
    if (ether.dnsLookup(urlTarget)) {
      Serial.println("DNS failed");
      return true;
    }
  }

  if(strlen(ipTarget) == 0) {
    Serial.println("The IP is empty, or it must be filled if no domain name is correct.");
    return false;
  }

  ether.parseIp(ether.hisip, ipTarget);
  ether.printIp("IP WS: ", ether.hisip);

  return true;
}
