// Drives 8 laser diodes using GPIO
// to create different visual patterns
// 22/04/2023


const unsigned int num_chans = 8;

bool lasers[num_chans] = {0};

unsigned int time_diff = 0;
unsigned int time_prev = 0;

unsigned int period = 100;

unsigned int chan0 = 2;

unsigned int mode = 0;

void setup() {
  Serial.begin(115200);

  // set all digi pins to output
  initDigiOut();  

  // init lasers[0]
  lasers[0] = 1;

  // turn all on for testing
  Serial.print("Testing...");  

  time_prev = millis();
}

void loop() {

time_diff = millis() - time_prev;
if (time_diff > period) {
  Serial.println("here");
  time_prev = millis();

  // set all the pins
  setPins();

  switch(mode){
    case 0: // shift through
      shiftLasers();
      break;

    default:
      break;

  
  }
  
  
  
}// time check
  
}// loop

void initDigiOut(){
  for(int ii = 0; ii < num_chans; ii++){
    pinMode(chan0 + ii,OUTPUT);
  }
}

void setPins(){
  Serial.print("lasers = ");
  for(int ii = 0; ii < num_chans; ii++){
    digitalWrite(chan0 + ii,lasers[ii]);
    Serial.print(lasers[ii]);
    Serial.print(" ");
  }
  Serial.println();
}

void shiftLasers(){
  bool next_laser = 0;
  for(int ii = 0; ii < num_chans; ii++){
    // check if next laser should be turned on
    if(next_laser){
      lasers[ii] = 1;
      next_laser = 0; // turn off next laser
      break;
    }

    // check if current laser is on
    if(lasers[ii]==1){
      next_laser = 1;
      lasers[ii] = 0;
    }

    // if you make it to the end of the list turn on laser 0
    if(ii == num_chans-1 && next_laser){
      lasers[0] = 1;
    }
  }
}
