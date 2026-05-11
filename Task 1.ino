/*
 * -----------------------------------------------------
 * Repository: IE410_Robotics_Project
 * Module: Task 1 - Blind Pick and Place
 * Description: Open-loop control sequence for the Braccio manipulator.
 * -----------------------------------------------------
 */

#include <Braccio.h>
#include <Servo.h>

// Initialize Servo Motors
Servo m_base, m_shoulder, m_elbow, m_wrist_rot, m_wrist_pitch, m_gripper;

void setup() {
    // Hardware Init
    Braccio.begin();
    
    // Serial Comms
    Serial.begin(9600);
    Serial.println("--- Task 1: Initialization ---");
    delay(2000);

    // Reset arm to starting position
    moveToDefault();
    delay(2000);

    // Execute pickup routine
    acquireTarget();
    delay(1000);

    // Execute drop-off routine
    deliverTarget();
    delay(1000);

    // Reset
    moveToDefault();
    Serial.println("--- Task 1: Sequence Finished ---");
}

void loop() {
    // Empty loop for pre-programmed sequence
}

/* * DEFAULT IDLE POSITION
 */
void moveToDefault() {
    // Parameters: Speed, Base, Shoulder, Elbow, Wrist_Rot, Wrist_Pitch, Gripper
    Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 10);
    delay(1000);
}

/* * TARGET ACQUISITION (POINT A)
 */
void acquireTarget() {
    Serial.println("Navigating to Pickup Zone...");
    
    // Hover above target
    Braccio.ServoMovement(20, 90, 60, 120, 90, 90, 10);
    delay(1000);

    // Lower payload
    Braccio.ServoMovement(20, 90, 75, 135, 90, 90, 10);
    delay(1000);

    // Secure payload
    Serial.println("Engaging Gripper...");
    Braccio.ServoMovement(20, 90, 75, 135, 90, 90, 65);
    delay(1500);

    // Ascend
    Braccio.ServoMovement(20, 90, 60, 120, 90, 90, 65);
    delay(1000);
}

/* * TARGET DELIVERY (POINT B)
 */
void deliverTarget() {
    Serial.println("Navigating to Drop Zone...");
    
    // Pan to drop zone
    Braccio.ServoMovement(20, 150, 60, 120, 90, 90, 65);
    delay(1000);

    // Descend
    Braccio.ServoMovement(20, 150, 75, 135, 90, 90, 65);
    delay(1000);

    // Release payload
    Serial.println("Disengaging Gripper...");
    Braccio.ServoMovement(20, 150, 75, 135, 90, 90, 10);
    delay(1500);

    // Ascend
    Braccio.ServoMovement(20, 150, 60, 120, 90, 90, 10);
    delay(1000);
}
