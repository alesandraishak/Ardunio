/**
 * @file PWM-motor-control.ino
 * @author Joshua Marshall (joshua.marshall@queensu.ca)
 * @brief Arduino program to drive wheel motors through a motor controller.
 * @version 1.0
 * @date 2021-07-04
 *
 * @copyright Copyright (c) 2021
 *
 */

int E1 = 6; // Left wheel PWM pin (must be a PWM pin)
int M1 = 7; // Left wheel direction digital pin
int E2 = 5; // Right wheel PWM pin (must be a PWM pin)
int M2 = 4; // Right wheel direction digital pin

void setup()
{
    pinMode(M1, OUTPUT); // Configure pin M1 for output
    pinMode(M2, OUTPUT); // Configure pin M2 for output
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
}

void loop()
{
    int u; // A variable for the motor PWM command [0-255
        u = 255;
        // Tell the motor driver board what to do
        digitalWrite(M1, LOW);  // Drive forward (left wheels)
        digitalWrite(M2, HIGH); // Drive forward (right wheels)
        analogWrite(E1, u);     // PWM speed command (left wheels)
        analogWrite(E2, u);     // PWM speed command (right wheels)
        
        delay(1000);

        digitalWrite(M1, HIGH);  // Drive forward (left wheels)
        digitalWrite(M2, LOW); // Drive forward (right wheels)
        analogWrite(E1, u);     // PWM speed command (left wheels)
        analogWrite(E2, u);

        delay(1000);
        u = 150;
        digitalWrite(M1, LOW);  // Drive forward (left wheels)
        digitalWrite(M2, HIGH); // Drive forward (right wheels)
        analogWrite(E1, u);     // PWM speed command (left wheels)
        analogWrite(E2, u);     // PWM speed command (right wheels)
        
        delay(1000);

        digitalWrite(M1, HIGH);  // Drive forward (left wheels)
        digitalWrite(M2, LOW); // Drive forward (right wheels)
        analogWrite(E1, u);     // PWM speed command (left wheels)
        analogWrite(E2, u);

        delay(1000);

        u=255;

        digitalWrite(M1, HIGH);  
        digitalWrite(M2, HIGH); 
        analogWrite(E1, u);     
        analogWrite(E2, u);     
        
        delay(1000);

        digitalWrite(M1, LOW);  
        digitalWrite(M2, HIGH); 
        analogWrite(E1, u);     
        analogWrite(E2, u);

        delay(1000);

        digitalWrite(M1, LOW);  // Drive forward (left wheels)
        digitalWrite(M2, LOW); // Drive forward (right wheels)
        analogWrite(E1, u);     // PWM speed command (left wheels)
        analogWrite(E2, u);

        delay(1000);

        int i;
        i=100;
        digitalWrite(M1, LOW);  
        digitalWrite(M2, LOW); 
        analogWrite(E1, u);     
        analogWrite(E2, i);

        delay(5000);

        

    
}
