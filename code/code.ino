#include "Arduino.h"
#include "NewPing.h"
#include "Switchable.h"
#include "VibrationMotor.h"

#define lecho  2
#define ltrig  3
#define mecho  4
#define mtrig  5
#define recho  6
#define rtrig  7

#define wlvsig  A3

#define lhaptic  10
#define mhaptic  9
#define rhaptic  11
NewPing leftmon(lecho, ltrig);
NewPing midmon(mecho, mtrig);
NewPing rightmon(recho, rtrig);

VibrationMotor leftout(lhaptic);
VibrationMotor midout(mhaptic);
VibrationMotor rightout(rhaptic);

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
  Serial.begin(9600);

  pinMode(ltrig, OUTPUT);
  pinMode(lecho, INPUT);
  pinMode(mtrig, OUTPUT);
  pinMode(mecho, INPUT);
  pinMode(rtrig, OUTPUT);
  pinMode(recho, INPUT);
  pinMode(wlvsig , INPUT);
  pinMode(lhaptic, OUTPUT);
  pinMode(mhaptic, OUTPUT);
  pinMode(rhaptic, OUTPUT);
}

int findDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  int distance = duration * 0.034 / 2;
  Serial.println(distance);
  return distance;
}

int lpoll()
{
  int flag;
  int dist = findDistance(ltrig, lecho);
  delay(10);
  if (dist < 50 && dist > 5) {
    int distS = map(dist, 5, 50, 255, 50);
    Serial.print(dist);
    Serial.print(" LEFT ");
    Serial.println(distS);
    analogWrite(lhaptic, distS);
    delay(500);
    analogWrite(lhaptic, 0);
    flag = '1';
  }
  else {
    flag = '0';
  }
  return flag;
}

int mpoll()
{
  int flag;
  int dist = findDistance(mtrig, mecho);
  delay(10);
  if (dist < 100) {
    int distS = map(dist, 5, 50, 255, 50);
    Serial.print(dist);
    Serial.print(" MIDDLE ");
    Serial.println(distS);
    analogWrite(mhaptic, distS);
    flag = '1';
  }
  return flag;
}

int rpoll()
{
  int flag;
  int dist = findDistance(rtrig, recho);
  delay(10);
  if (dist < 100) {
    int distS = map(dist, 5, 50, 255, 50);
    Serial.print(dist);
    Serial.print(" RIGHT ");
    Serial.println(distS);
    analogWrite(rhaptic, distS);
    flag = '1';
  }
  return flag;
}

int wpoll()
{
  int flag;
  int val = analogRead(wlvsig);

  if (val > 0) {
    flag = '1';
  }
  else {
    flag = '0';
  }
  return flag;
}
void lvib()
{
  leftout.on();
  delay(500);
  leftout.off();
  delay(500);
}
void mvib()
{
  midout.on();
  delay(500);
  midout.off();
  delay(500);
}

void rvib()
{
  rightout.on();
  delay(500);
  rightout.off();
  delay(500);
}

void wvib()
{
  leftout.on();
  midout.on();
  rightout.on();
  delay(500);
  leftout.off();
  midout.off();
  rightout.off();
  delay(500);
}
void loop()
{
  int lflag, mflag, rflag, wflag;

  lflag = lpoll();
  mflag = mpoll();
  rflag = rpoll();
  wflag = wpoll();
}
