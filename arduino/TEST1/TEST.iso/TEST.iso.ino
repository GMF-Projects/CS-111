const int stepPin  = 10;
const int dirPin   = 9;
const int btnCW    = 2;
const int btnCCW   = 3;

const unsigned long STEP_DELAY_US = 3000;
const unsigned long DEBOUNCE_MS   = 50;

unsigned long lastStepTime   = 0;
bool          stepState      = LOW;
bool          motorActive    = false;
bool          stepInProgress = false;  // buffer: finish current step before stopping

unsigned long lastDebounceTimeCW  = 0;
unsigned long lastDebounceTimeCCW = 0;
int  lastCWState  = HIGH;
int  lastCCWState = HIGH;
bool cwHeld       = false;
bool ccwHeld      = false;

// track direction so we only write dirPin on actual changes
bool currentDirCW = true;
bool dirSet       = false;   // false until first button press

void setDir(bool cw) {
  if (!dirSet || cw != currentDirCW) {   // only write on change
    motorActive = false;                  // pause stepping
    stepState   = LOW;
    digitalWrite(stepPin, LOW);           // finish cleanly
    digitalWrite(dirPin, cw ? HIGH : LOW);
    delayMicroseconds(5);                 // DIR settle time
    currentDirCW = cw;
    dirSet       = true;
    lastStepTime = micros();              // reset timing after dir change
  }
}

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin,  OUTPUT);
  pinMode(btnCW,   INPUT);
  pinMode(btnCCW,  INPUT);
  digitalWrite(stepPin, LOW);
  Serial.begin(9600);
}

void loop() {
  unsigned long now = micros();

  // ── Read + debounce CW ─────────────────────────────────────
  int rawCW = digitalRead(btnCW);
  if (rawCW != lastCWState) lastDebounceTimeCW = millis();
  if ((millis() - lastDebounceTimeCW) > DEBOUNCE_MS) {
    cwHeld = (rawCW == LOW);
  }
  lastCWState = rawCW;

  // ── Read + debounce CCW ────────────────────────────────────
  int rawCCW = digitalRead(btnCCW);
  if (rawCCW != lastCCWState) lastDebounceTimeCCW = millis();
  if ((millis() - lastDebounceTimeCCW) > DEBOUNCE_MS) {
    ccwHeld = (rawCCW == LOW);
  }
  lastCCWState = rawCCW;

  // ── Direction — only writes dirPin when direction changes ──
  if (cwHeld && !ccwHeld) {
    setDir(true);
    motorActive = true;
  } else if (ccwHeld && !cwHeld) {
    setDir(false);
    motorActive = true;
  } else {
    // neither or both pressed
    // stepInProgress lets the current half-cycle finish before stopping
    if (!stepInProgress) {
      motorActive = false;
      stepState   = LOW;
      digitalWrite(stepPin, LOW);
    }
  }

  // ── Non-blocking step pulse ────────────────────────────────
  if (motorActive && (now - lastStepTime >= STEP_DELAY_US)) {
    lastStepTime    = now;
    stepState       = !stepState;
    stepInProgress  = stepState;   // HIGH = mid-step, LOW = step complete
    digitalWrite(stepPin, stepState);
  }

  // ── Serial monitor (throttled) ─────────────────────────────
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 200) {
    lastPrint = millis();
    Serial.print("CW: "); Serial.print(cwHeld);
    Serial.print(" | CCW: "); Serial.print(ccwHeld);
    Serial.print(" | Dir: "); Serial.print(currentDirCW ? "CW" : "CCW");
    Serial.print(" | Active: "); Serial.println(motorActive);
  }
}
