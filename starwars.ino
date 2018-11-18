int button=2; // button is connected to pin 2
int buttonstatus=0; //variable to save the status of button

int ledPin1 = 10; //first set of LEDs
int ledPin2 = 11; //second set of LEDs



#define  c3    7634
#define  d3    6803
#define  e3    6061
#define  f3    5714
#define  g3    5102
#define  a3    4545
#define  b3    4049
#define  c4    3816    // 261 Hz 
#define  d4    3401    // 294 Hz 
#define  e4    3030    // 329 Hz 
#define  f4    2865    // 349 Hz 
#define  g4    2551    // 392 Hz 
#define  a4    2272    // 440 Hz 
#define  a4s   2146
#define  b4    2028    // 493 Hz 
#define  c5    1912    // 523 Hz
#define  d5    1706
#define  d5s   1608
#define  e5    1517
#define  f5    1433
#define  g5    1276
#define  a5    1136
#define  a5s   1073
#define  b5    1012
#define  c6    955

// Define a special note, 'R', to represent a rest
#define  R     0

// SETUP 

// Set up speaker on a PWM pin 
int speakerOut = 9;


void setup() { 
  pinMode(button, INPUT); //button is an input
  pinMode(speakerOut, OUTPUT); //speaker is an input
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

   Serial.begin(9600); 

}


//  melody[] is an array of notes, accompanied by beats[], 
//  which sets each note's relative length (higher #, longer note) 

// star wars theme
int melody[] = {  f4,  f4, f4,  a4s,   f5,  d5s,  d5,  c5, a5s, f5, d5s,  d5,  c5, a5s, f5, d5s, d5, d5s,   c5};//
int beats[]  = {  21,  21, 21,  100,  60,   21,  21,  21, 100, 64,  21,  21,  21, 100, 64,  21, 21,  21, 128 }; 

//imperial march
//int melody[] = {  a4, R,  a4, R,  a4, R,  f4, R, c5, R,  a4, R,  f4, R, c5, R, a4, R,  e5, R,  e5, R,  e5, R,  f5, R, c5, R,  g5, R,  f5, R,  c5, R, a4, R};
//int beats[]  = {   50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5, 20, 5, 60, 80, 50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5,  20, 5, 60, 40 }; 

int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.

// Set overall tempo
long tempo = 10000;
// Set length of pause between notes
int pause = 1000;
// Loop variable to increase Rest length
int rest_count = 50; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
int toneM = 0;
int beat = 0;
long duration  = 0;

// PLAY TONE  

// Pulse the speaker to play a tone for a particular duration
void playTone() {
  long elapsed_time = 0;
  if (toneM > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(toneM / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(toneM / 2);

      // Keep track of how long we pulsed
      elapsed_time += (toneM);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                 
}

void loop() {
  
buttonstatus = digitalRead(button); //get status from button1 (HIGH or LOW)

if (buttonstatus == HIGH) //If button1 gets pushed..
{
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, HIGH);

 // Set up a counter to pull from melody[] and beats[]
  for (int i=0; i<MAX_COUNT; i++) {
    toneM = melody[i];
    beat = beats[i];

    duration = beat * tempo; // Set up timing

    playTone(); 
    // A pause between notes...
    delayMicroseconds(pause);
    buttonstatus = digitalRead(button); // force for loop to check for button status
     if (buttonstatus == LOW){
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
      return;

  };
 
}
if (buttonstatus == LOW){
 noTone(speakerOut);
  digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
 
}
else{
  noTone(speakerOut);
   digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
  }
 
}}
