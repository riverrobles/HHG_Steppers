// Set analog inputs of positive limit switches 

int xplim = 0 ; 
int yplim = 1 ;
int zplim = 2 ; 

// Set analog inputs of negative limit switches (zeros) 

int xnlim = 3 ;
int ynlim = 4 ;
int znlim = 5 ; 

// Set digital pins for stp function 

int xstp = 2 ; 
int ystp = 3 ; 
int zstp = 4 ; 

// Set digital pins for dir function 

int xdir = 5 ; 
int ydir = 6 ; 
int zdir = 7 ; 

int PosLims[] = {
  xplim, yplim, zplim
} ; 

int NegLims[] = {
  xnlim, ynlim, znlim
} ; 

int StpPins[] = {
  xstp, ystp, zstp
} ; 

int DirPins[] = {
  xdir, ydir, zdir 
} ; 

void resetPins() ; 
void Pulse() ; 
bool posStep() ; 
bool negStep() ; 

void setup() {
  Serial.begin(9600) ; 

  for (int i=0 ; i < 3 ; i++) {
    Serial.println(i) ; 
    Serial.println(PosLims[i]) ; 
    Serial.println(StpPins[i]) ; 
    pinMode(PosLims[i],INPUT_PULLUP) ; 
    pinMode(NegLims[i],INPUT_PULLUP) ; 
    pinMode(StpPins[i],OUTPUT) ; 
    pinMode(DirPins[i],OUTPUT) ; 
  }

  resetPins() ; 
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil("\n") ; 
    float stps = input.toFloat() ; 

    Serial.println(input) ; 
    Serial.println(stps) ; 
    Serial.println(Serial.available()) ; 

    while (Serial.available() == 0) {} ; 
    input = Serial.readStringUntil("\n") ; 
    int board = input.toInt() ; 

    Serial.println(input) ;
    Serial.println(board) ; 

    if (stps > 0) {
      Serial.println("positive") ; 
      if (posStep(stps,board)) { Serial.println("Normal \n") ; }
      else { Serial.println("Hit positive switch \n") ; } // define board 
    }
    else if (stps < 0) {
      if (negStep(-stps,board)) {Serial.println("Normal \n") ; }
      else {Serial.println("Hit negative switch \n") ; } 
    }
  }
}

bool posStep(float stps, int board) {
  digitalWrite(DirPins[board],LOW) ; 
  Serial.println("positive") ; 
  Serial.println(analogRead(PosLims[board])) ;
  Serial.println(analogRead(NegLims[board])) ; 
  for (long x=0 ; x < stps ; x++) {
    if (analogRead(PosLims[board]) > 300) {
      Serial.println("Pulsing") ; 
      Pulse(board) ; 
    }

    else {
      digitalWrite(DirPins[board],HIGH) ;
       
      while (analogRead(PosLims[board]) < 300) {
        Pulse(board) ; 
      }
      
      return false ; 
    }
  }
  return true ; 
}

bool negStep(float stps, int board) {
  digitalWrite(DirPins[board],HIGH) ; 

  for (long x=0 ; x < stps ; x++) {
    if (analogRead(NegLims[board]) > 300) {
      Pulse(board) ; 
    }

    else {
      digitalWrite(DirPins[board],LOW) ; 

      while (analogRead(NegLims[board]) < 300) {
        Pulse(board) ;
      } 
      
      return false ; 
    }
  }
  return true ; 
}

void Pulse(int board) {
  digitalWrite(StpPins[board],HIGH) ;
  delay(10) ; 
  digitalWrite(StpPins[board],LOW) ; 
  delay(10) ; 
}

void resetPins() {
  for (int i=0 ; i<3 ; i++) {
    digitalWrite(StpPins[i],LOW) ; 
  }
}
