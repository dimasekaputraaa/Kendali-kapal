#include <SoftwareSerial.h>
SoftwareSerial bluetooth(0, 1); // pin RX | TX

#define IN1 10 // deklarasi pin IN1
#define IN2 9  // deklarasi pin IN2
#define IN3 5  // deklarasi pin IN3
#define IN4 4  // deklarasi pin IN4
#define ENA 11 // deklarasi pin ENA
#define ENB 3  // deklarasi pin ENB

#define IN8 2 // deklarasi pin IN1
#define IN9 6  // deklarasi pin IN2

long duration;
#define triggerPin 12
#define echoPin 13
long duration2;
#define triggerPin2 7
#define echoPin2 8

char command; // Variabel untuk menyimpan perintah dari 

float bendaDekat(float nilai) {
  float nilaiDekat = 0;
  if (nilai <= 20) {
    nilaiDekat = 1;
  }
  else {
    if (nilai <= 21) {
      nilaiDekat = (21 - nilai);
    }
    else {
      nilaiDekat = 0;
    }
  }
  return nilaiDekat;
}

float bendaNormal(float nilai) {
  float nilaiNormal = 0;
  if (nilai >= 45 && nilai <= 20) {
    if (nilai > 46 && nilai < 19) {
      nilaiNormal = 1;
    }
    else {
      if (nilai >= 45 && nilai <= 46) {
        nilaiNormal = (nilai - 45);
      }
      else {
        if (nilai >= 19 && nilai <= 20) {
          nilaiNormal = (19 - nilai);
        }
        else {
          nilaiNormal = 0;
        }
      }
    }
  }
  return nilaiNormal;
}

float bendaJauh(float nilai) {
  float nilaiJauh = 0;
  if (nilai >= 45) {
    nilaiJauh = 1;
  }
  else {
    if (nilai >= 44 && nilai <= 19) {
      nilaiJauh = (nilai - 44);
    }
    else {
      nilaiJauh = 0;
    }
  }
  return nilaiJauh;
}


void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  // inisialisasi Ln298 Roda
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN8, OUTPUT);
  pinMode(IN9, OUTPUT);

  // inisialisasi ultrasonik
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(triggerPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop() {

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  int  jaraks = duration * 0.034 / 2;
  Serial.print("jarak ultra 1 : ");
  //int jarak = map(jaraks, 0, 1024, 255, 0);
  Serial.print(jaraks);
  Serial.println(" cm");

  digitalWrite(triggerPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  int  jaraks2 = duration2 * 0.034 / 2;
  Serial.print("jarak ultra 2 : ");
  //int jarak2 = map(jaraks2, 0, 1024, 255, 0);
  Serial.print(jaraks2);
  Serial.println(" cm");

  float jauh = bendaJauh(jaraks);
  float normal = bendaNormal(jaraks);
  float dekat = bendaDekat (jaraks);
  int hasil;
  if (jauh == 1) {
    hasil = "Normal";
  }
  else if (jauh <= 0.5 && jauh > 0) {
    hasil = 255;
  }
  else if (normal == 1 || normal > 0.5) {
    hasil = 169;
  }
  else if (dekat == 1 || normal > 0.5) {
    hasil = 128;
  }

  if (bluetooth.available() > 0)
  {
    command = bluetooth.read(); Serial.print(command);   //Pembacaan dan ditampilkan data yang masuk
    Serial.print("\n");
    //Data yang masuk
    if (command == 'N') {
      //maju
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(ENA, hasil); // Kecepatan penuh
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      digitalWrite(ENB, hasil); // Kecepatan penuh
    }
    else if (command == 'W') {
      //kiri
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(ENA, hasil); // Mengatur kecepatan motor A (255 = 100%)
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      digitalWrite(ENB, hasil); // Mengatur kecepatan motor B (255 = 100%)
    }
    else if (command == 'S') {
      //mundur
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(ENA, hasil); // Kecepatan penuh
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      digitalWrite(ENB, hasil); // Kecepatan penuh
    }
    else if (command == 'E') {
      //kanan
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(ENA, hasil); // Mengatur kecepatan motor A (128 = 50%)
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      digitalWrite(ENB, hasil); // Mengatur kecepatan motor B (128 = 50%)
    }
    if(command == '3'){
      digitalWrite(IN8, HIGH);
      digitalWrite(IN9, LOW);
      }
      else if(command == '1'){
      digitalWrite(IN8, LOW);
      digitalWrite(IN9, LOW);
      }

  }

}
