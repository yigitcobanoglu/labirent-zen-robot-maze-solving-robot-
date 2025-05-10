// Sensör pinleri
const int trigPin1 = 11; // orta
const int echoPin1 = 10;

const int trigPin2 = A3; // sağ
const int echoPin2 = A4;

const int trigPin3 = A2; // sol
const int echoPin3 = A5;

// Motor pinleri
const int in1 = 9;
const int in2 = 8;
const int in3 = 4;
const int in4 = 3;
const int enA = 5;
const int enB = 6;

#define PWM 150      // Motor hızı
#define DIS 6        // Engel algılama mesafesi (cm)

void setup() {
  // Sensör pinleri
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  // Motor pinleri
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
}

void loop() {
  long front = FrontSensor();
  long right = RightSensor();
  long left  = LeftSensor();

  if (front < DIS && right < DIS && left < DIS) {
    reverse();
    delay(500);
    turn_right();
    delay(600);
  }
  else if (front < DIS && right < DIS && left > DIS) {
    turn_left();
    delay(600);
  }
  else if (front < DIS && right > DIS && left < DIS) {
    turn_right();
    delay(600);
  }
  else if (front < DIS && right > DIS && left > DIS) {
    turn_right();
    delay(600);
  }
  else if (front > DIS && right > DIS && left < DIS) {
    forward();
  }
  else if (front > DIS && right < DIS && left > DIS) {
    forward();
  }
  else {
    forward();
  }
}

// Motor fonksiyonları
void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, PWM);
  analogWrite(enB, PWM);
}

void reverse() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, PWM);
  analogWrite(enB, PWM);
}

void turn_left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, PWM);
  analogWrite(enB, PWM);
}

void turn_right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, PWM);
  analogWrite(enB, PWM);
}

// Sensör fonksiyonları
long FrontSensor() {
  return getDistance(trigPin1, echoPin1);
}

long RightSensor() {
  return getDistance(trigPin2, echoPin2);
}

long LeftSensor() {
  return getDistance(trigPin3, echoPin3);
}

long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // zaman aşımı
  if (duration == 0) return 100; // eğer sensör okumazsa 100 cm varsay
  return duration / 58;
}