/*
 * -----------------------------------------------------
 * Repository: IE410_Robotics_Project
 * Module: Task 3 - Bimanual Object Transfer
 * Description: Coordinated movement between two manipulators.
 * -----------------------------------------------------
 */

#include <Braccio.h>
#include <Servo.h>

// Motor objects
Servo m_base, m_shoulder, m_elbow, m_wrist_rot, m_wrist_pitch, m_gripper;

void setup() {
    Braccio.begin();
    
    Serial.begin(9600);
    Serial.println("--- Task 3: Dual Arm Synchronization ---");
    delay(2000);

    resetArm();
    delay(2000);

    primaryArmGrab();
    delay(1000);

    goToExchangeZone();
    delay(1000);

    // Handover coordination
    secondaryArmEngage();
    delay(1000);

    primaryArmDrop();
    delay(1000);

    secondaryArmStore();
    delay(1000);

    resetArm();
    Serial.println("--- Transfer Cycle Complete ---");
}

void loop() {
    // Main loop intentionally left blank
}

/* * CALIBRATION STANCE 
 */
void resetArm() {
    Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 10);
    delay(1000);
}

/* * ARM 1: PICKUP ROUTINE 
 */
void primaryArmGrab() {
    Serial.println("Primary Arm: Initiating sequence");
    
    Braccio.ServoMovement(20, 80, 60, 120, 90, 90, 10);
    delay(1000);

    Braccio.ServoMovement(20, 80, 75, 135, 90, 90, 10);
    delay(1000);

    Braccio.ServoMovement(20, 80, 75, 135, 90, 90, 65);
    delay(1500);

    Braccio.ServoMovement(20, 80, 60, 120, 90, 90, 65);
    delay(1000);
}

/* * ARM 1: MOVE TO HANDOVER COORDINATES
 */
void goToExchangeZone() {
    Serial.println("Primary Arm: Moving to common workspace");
    Braccio.ServoMovement(20, 110, 70, 110, 90, 90, 65);
    delay(2000);
}

/* * ARM 2: APPROACH AND SECURE (Theoretical Simulation)
 */
void secondaryArmEngage() {
    Serial.println("Secondary Arm: Entering exchange zone");
    Serial.println("Secondary Arm: Adjusting pitch/yaw");
    delay(1000);
    Serial.println("Secondary Arm: Closing effector");
    delay(1500);
}

/* * ARM 1: RELEASE PAYLOAD
 */
void primaryArmDrop() {
    Serial.println("Primary Arm: Releasing payload");
    Braccio.ServoMovement(20, 110, 70, 110, 90, 90, 10);
    delay(1500);
}

/* * ARM 2: FINAL PLACEMENT (Theoretical Simulation)
 */
void secondaryArmStore() {
    Serial.println("Secondary Arm: Retreating to safe zone");
    delay(1000);
    Serial.println("Secondary Arm: Payload secured");
    delay(1000);
    Serial.println("Sync Complete.");
}
