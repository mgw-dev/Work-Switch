#define RELAY_OFF HIGH
#define RELAY_ON LOW
#define RELAY1_PIN 2
#define RELAY2_PIN 3
#define RELAY3_PIN 4
#define RELAY4_PIN 5
#define SWITCH_PIN 6
#define debounce 1

bool current_toggle_status = LOW;

void setup() {
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);
  pinMode(RELAY4_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(SWITCH_PIN, INPUT_PULLUP);

  digitalWrite(RELAY1_PIN, RELAY_OFF);
  digitalWrite(RELAY2_PIN, RELAY_OFF);
  digitalWrite(RELAY3_PIN, RELAY_OFF);
  digitalWrite(RELAY4_PIN, RELAY_OFF);

}

void loop() {
  if(readToggleSwitch()){
    digitalWrite(LED_BUILTIN, HIGH);
    onSequence();
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
    offSequence();
    
  }
}
  

void onSequence(){
  digitalWrite(RELAY1_PIN, RELAY_ON);
  delay(1000);
  digitalWrite(RELAY2_PIN, RELAY_ON);
  digitalWrite(RELAY3_PIN, RELAY_ON);
  digitalWrite(RELAY4_PIN, RELAY_ON);
}

void offSequence(){
  digitalWrite(RELAY4_PIN, RELAY_OFF);
  digitalWrite(RELAY3_PIN, RELAY_OFF);
  digitalWrite(RELAY2_PIN, RELAY_OFF);
  delay(1000);
  digitalWrite(RELAY1_PIN, RELAY_OFF);
}

bool readToggleSwitch() {

  return !digitalRead(SWITCH_PIN); //Bypass debouncing. seems to not be needed.

  static long int elapse_time = 0;
  static bool transition_started = false;
  if (!digitalRead(SWITCH_PIN) != current_toggle_status && !transition_started) {
     // switch change detected  so start debounce cycle
     transition_started = true;
     elapse_time = millis();  // set start of debounce timer
  } else {
    if (transition_started) {
       // we are in the switch transition cycle so check if debounce period has elapsed
       if (millis() - elapse_time >= debounce) {
         // debounce period elapse  so assume switch has settled down after transition
         current_toggle_status  = !current_toggle_status;  // flip status
         transition_started = false;  // cease transition cycle
       }
     }
  }
  return current_toggle_status;
}