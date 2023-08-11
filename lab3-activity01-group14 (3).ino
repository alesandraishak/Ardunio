/**
 * @file motor-angular-rate.ino
 * @author Joshua Marshall (joshua.marshall@queensu.ca)
 * @brief Arduino program to estimate motor speed from encoder.
 * @version 1.0
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */

// Motor driver PWM pin
const byte E1 = 6;

const byte E2 = 5;
const byte M2 = 4;
// Motor driver direction pin
const byte M1 = 7;

// Motor PWM command variable [0-255]
byte u = 0;
//L constant 
const double ELL = 0.2775;
// Left wheel encoder digital pins
const byte SIGNAL_A = 8;
const byte SIGNAL_B = 9;
//Right 
const byte SIGNAL_C = 10;
const byte SIGNAL_D = 11;

// Encoder ticks per (motor) revolution (TPR)
const int TPR = 3000;

// Wheel radius [m]
const double RHO = 0.0625;

// Counter to keep track of encoder ticks [integer]
volatile long encoder_ticks = 0;
volatile long encoder_ticks_right = 0;

// Variable to store estimated angular rate of left and right wheel [rad/s]
double omega_L = 0.0;
double omega_R = 0.0;

// Initialize variable to store linear speed left and right
double linearSpeed = 0.0;
double linearSpeedR = 0.0;
// Sampling interval for measurements in milliseconds
const int T = 200;

// Counters for milliseconds during interval
long t_now = 0;
long t_last = 0;

// This function is called when SIGNAL_A goes HIGH
void decodeEncoderTicks()
{
    if (digitalRead(SIGNAL_B) == LOW)
    {
        // SIGNAL_A leads SIGNAL_B, so count one way
        encoder_ticks--;
    }
    else
    {
        // SIGNAL_B leads SIGNAL_A, so count the other way
        encoder_ticks++;
    }
}
void decodeEncoderTicksR()
{
    if (digitalRead(SIGNAL_D) == LOW)
    {
        encoder_ticks_right--;
    }
    else
    {
        encoder_ticks_right++;
    }
}


void setup()
{
    // Open the serial port at 9600 bps
    Serial.begin(9600);

    // Set the pin modes for the motor driver
    pinMode(M1, OUTPUT);
    pinMode(M2, OUTPUT);

    // Set the pin modes for the encoders
    pinMode(SIGNAL_A, INPUT);
    pinMode(SIGNAL_B, INPUT);
    pinMode(SIGNAL_C, INPUT);
    pinMode(SIGNAL_D, INPUT);

    // Every time the pin goes high, this is a pulse
    attachInterrupt(digitalPinToInterrupt(SIGNAL_A), decodeEncoderTicks, RISING);
    attachInterrupt(digitalPinToInterrupt(SIGNAL_C), decodeEncoderTicksR, RISING);

    // Print a message
    Serial.print("Program initialized.");
    Serial.print("\n");
}

void loop()
{
    // Get the elapsed time [ms]
    t_now = millis();

    if (t_now - t_last >= T)
    {
        // Estimate the rotational speed [rad/s]
        omega_L = 2.0 * PI * ((double)encoder_ticks / (double)TPR) * 1000.0 / (double)(t_now - t_last);
        omega_R = 2.0 * PI * ((double)encoder_ticks_right / (double)TPR) * 1000.0 / (double)(t_now - t_last);
        
        // Equation for linear speed estimation
        linearSpeed = 0.0625 * (omega_L);
        linearSpeedR = -0.0625 * (omega_R);


       /*   // Print some stuff to the serial monitor
          Serial.print("Encoder left ticks: ");
          Serial.print(encoder_ticks);
          Serial.print("\n");
          Serial.print("Encoder right ticks: ");
          Serial.print(encoder_ticks_right);
          Serial.print("\n");
          Serial.print("Estimated left wheel speed: ");
          // Display the linear speed
          Serial.print(linearSpeed);
          Serial.print(" m/s");
          Serial.print("\n");
          Serial.print("Estimated right wheel speed: ");
          // Display the linear speed
          Serial.print(linearSpeedR);
          Serial.print(" m/s");
          Serial.print("\n"); */

        // Record the current time [ms]
        t_last = t_now;

        // Reset the encoder ticks counter
        encoder_ticks = 0;
        encoder_ticks_right = 0;

        double computervehicleSpeed = 0.5*(linearSpeed + linearSpeedR); 
        double computerVehicleRate = (1.0/ELL)*(linearSpeedR - linearSpeed); 

        Serial.print(computervehicleSpeed); 
        Serial.print(" m/s");
        Serial.print("\n");

        Serial.print(computerVehicleRate); 
        Serial.print(" r/s");
        Serial.print("\n");

        Serial.print("\n");
    }

    // Set the wheel motor PWM command [0-255]
    u = 140;

    // Write to the output pins
    digitalWrite(M1, LOW); // Drive forward (left wheels)
    analogWrite(E1, u);    // Write left motors command
    digitalWrite(M2, HIGH); // Drive forward (right wheels)
    analogWrite(E2, u);    // Write right motors command
}
