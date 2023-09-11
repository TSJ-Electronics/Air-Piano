// Dedicated to the tiktok user who asked for a simple project to build with his kid for school
// Distance Sensor Project By: TSJ Electronics, code structure and some comments from Howtomechatronics

/*For a detailed writeup of how these sensors work and other
  useful information please check out:
  https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/#google_vignette
*/

 /*
 For more projects check out TSJelectronics.com
 */
 
const int trigPin = 13;
const int echoPin = 12;

const int buzzer = 11; //Must use a passive buzzer for clearest sound. Active buzzers ring at a set frequency and wont work well.

const int greenLED = 10;
const int yellowLED  = 9;
const int redLED = 8;

long duration;
double distance;

double maxDistanceInches = 12; // this is how far we want our sensor to read, ignore everything farther than 12 inches.

int baseFrequency = 10;
int maxFrequency = 1200;
int currentFrequency = 500;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(buzzer, LOW); // set all outputs low
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance in cm
  distance = duration * 0.034 / 2;
  
  //to convert cm to inches
  distance = distance / 2.54;

  //Light up light depending on distance!
  if(distance < maxDistanceInches){
     digitalWrite(greenLED, HIGH);
     currentFrequency = (distance/maxDistanceInches)*(maxFrequency - baseFrequency) + baseFrequency;
     tone(buzzer, currentFrequency,100);
     
     Serial.print("Distance: ");
     Serial.println(distance);

     Serial.print("Frequency: ");
     Serial.println(currentFrequency);
     delay(96);
  }
  else{
     digitalWrite(greenLED, LOW);
     noTone(buzzer); //turn off buzzer if hand is too far away
  }
     
  if(distance < (maxDistanceInches* 0.66))
    digitalWrite(yellowLED, HIGH);
  else
    digitalWrite(yellowLED, LOW);
  
   if(distance < (maxDistanceInches * 0.33)){
    digitalWrite(redLED, HIGH);
    //digitalWrite(buzzer, HIGH); // if too close to sensor sound the alarm!!
   }
   else{
   digitalWrite(redLED, LOW);
   //digitalWrite(buzzer,LOW); // if not close turn off alaram
   }
}
