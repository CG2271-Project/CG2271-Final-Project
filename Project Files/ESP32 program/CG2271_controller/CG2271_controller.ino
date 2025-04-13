#include <Bluepad32.h>

GamepadPtr myGamepad;
int currentSpeed = 2; // Global speed level (0 to 3). Default is 2.
unsigned long lastReconnectAttempt = 0; // For reconnect timing

// Toggle flag for bit 7 when button 0x0002 is pressed
bool toggleFlag = false;
bool toggleFlag2 = false;
unsigned int lastButtons = 0;

// Debounce state for d-pad
byte lastDpad = 0;

// Variables for speed limiting after a sharp turn
bool limitSpeedDueToTurn = false;
unsigned long speedLimitStartTime = 0;
const unsigned long speedLimitDuration = 0;

// Track if the previous turning input was at maximum (sharp turn)
bool lastWasMaxTurn = false;

byte encodeAxis(int val) {
  val = constrain(val, -512, 512);
  int magnitude = abs(val);
  byte level;
  if (magnitude < 50) level = 0;
  else if (magnitude < 155) level = 1;
  else if (magnitude < 490) level = 2;
  else level = 3;

  return (val > 0) ? (0x04 | (level & 0x03)) : (level & 0x03);
}

byte encodeSpeed(int val) {
  val = constrain(val, -3, 3);
  return (val < 0) ? (0x04 | ((uint8_t)(-val) & 0x03)) : ((uint8_t)val & 0x03);
}

void onGamepadConnected(GamepadPtr gp) {
  ControllerProperties properties = gp->getProperties();
  char macStr[18];
  sprintf(macStr, "%02x:%02x:%02x:%02x:%02x:%02x",
          properties.btaddr[0], properties.btaddr[1], properties.btaddr[2],
          properties.btaddr[3], properties.btaddr[4], properties.btaddr[5]);

  const char* allowedMac1 = "bc:c7:46:78:07:67";
  const char* allowedMac2 = "5c:01:3b:72:f6:82";
  //5C:01:3B:72:F6:82


  if (strcasecmp(macStr, allowedMac1) != 0 && strcasecmp(macStr, allowedMac2) != 0) {
    return;
  }

  myGamepad = gp;
}

void onGamepadDisconnected(GamepadPtr gp) {
  myGamepad = nullptr;
}

void setup() {
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  BP32.setup(onGamepadConnected, onGamepadDisconnected);
}

void loop() {
  BP32.update();

  if (!myGamepad || !myGamepad->isConnected()) {
    if (millis() - lastReconnectAttempt > 250) {
      BP32.setup(onGamepadConnected, onGamepadDisconnected);
      lastReconnectAttempt = millis();
    }
    Serial2.write((byte)0);
    delay(1);
    return;
  }

  // Adjust speed level using the d-pad (assumes bit 0 = UP, bit 2 = DOWN).
  byte dpad = myGamepad->dpad();
  if ((dpad & 0x01) && !(lastDpad & 0x01)) {
    if (currentSpeed < 3) currentSpeed++;
  }
  if ((dpad & 0x02) && !(lastDpad & 0x02)) {
    if (currentSpeed > 1) currentSpeed--;
  }
  lastDpad = dpad;

  // Determine movement direction using triggers.
  int speedVal = 0;
  if (myGamepad->throttle() > 800) speedVal = -currentSpeed;
  else if (myGamepad->throttle() > 300) speedVal = -1;
  else if (myGamepad->brake() > 300) speedVal = 1;
  else speedVal = 0;

  // Get turning value from right stick's X axis.
  int rx = myGamepad->axisRX();

  // Determine if the current turning input is maximum.
  bool currentMaxTurn = (abs(rx) >= 490);

  // If we were previously at maximum and now we switched to a lower turn,
  // and the speed command is full (±3), then impose the speed limit.
  if (lastWasMaxTurn && !currentMaxTurn && abs(speedVal) == 3) {
    limitSpeedDueToTurn = true;
    speedLimitStartTime = millis();
  }
  // Update for the next iteration.
  lastWasMaxTurn = currentMaxTurn;

  // While the speed limit flag is active for 0.5 seconds, override speedVal.
  if (limitSpeedDueToTurn) {
    if (millis() - speedLimitStartTime < speedLimitDuration) {
      if (speedVal >= 2) speedVal = 1;
      else if (speedVal <= -3) speedVal = -1;
    } else {
      limitSpeedDueToTurn = false;
    }
  }

  // Encode the speed and turning values.
  byte encodedSpeed = encodeSpeed(speedVal);
  byte encodedTurn = encodeAxis(rx);
  byte combined = (encodedSpeed << 3) | encodedTurn;

  // Toggle bit 7 based on button press.
  unsigned int currentButtons = myGamepad->buttons();
  if ((currentButtons & 0x0002) && !(lastButtons & 0x0002)) {
    toggleFlag = !toggleFlag;
  }
  if ((currentButtons & 0x0004) && !(lastButtons & 0x0004)) {
    toggleFlag2 = !toggleFlag2;
  }
  lastButtons = currentButtons;

  if (toggleFlag) combined |= 0x80;
  else combined &= 0x7F;
  if (toggleFlag2) combined |= 0x40;
  else combined &= 0xBF;

  // Send the combined byte over UART.
  Serial2.write(combined);
}
