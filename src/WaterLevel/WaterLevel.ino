#define ECHO 2
#define TRIG 0
#define LED 4

long d;
int cm;

void setup() {
  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  /*  s = v * t
   *  v = 346 m/s (speed of sound)
   *  t = time when ultrasonic wave back to echo (µs)
   *  divided by 2 it mean found object and reflexed back
   */
  d = pulseIn(ECHO, HIGH); 
  cm = d * 0.034 / 2; 

  digitalWrite(LED, cm <= 10);
  
  Serial.print("Distance: "); // Prints string "Distance" on the LCD
  Serial.print(cm); // Prints the distance value from the sensor
  Serial.println(" cm");
  delay(500);
}
