const int GAS_SENSOR_PIN = A0;
const int LED_PIN = A1;
const int BUZZER_PIN = 10;

const float ALERT_THRESHOLD_PERCENT = 25.0;  // Major gas leak
const float SLIGHT_THRESHOLD_PERCENT = 10.0; // Slight gas leak

const int N_SAMPLES = 50;
const int CALIBRATION_DELAY = 1000;           // 1 second per sample
const int MONITORING_INTERVAL = 1000;         // 1 second monitoring

float air_ref = 0.0;

// Function to read average value from sensor
int readGasAverage(int samples = 5) {
  long sum = 0;

  for (int i = 0; i < samples; i++) {
    sum += analogRead(GAS_SENSOR_PIN);
    delay(10);
  }

  return sum / samples;
}

void setup() {
  Serial.begin(9600);

  Serial.println("---- High-Sensitivity Gas Leak Detector Initializing ----");

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("STEP 1: Starting Calibration. Keep environment clean...");

  long total_sum = 0;

  for (int i = 0; i < N_SAMPLES; i++) {
    int current_reading = analogRead(GAS_SENSOR_PIN);
    total_sum += current_reading;
    delay(CALIBRATION_DELAY);
  }

  air_ref = (float)total_sum / N_SAMPLES;

  Serial.println("Calibration Complete.");
  Serial.print("Baseline air value (air_ref): ");
  Serial.println(air_ref);

  Serial.println("--------------------------------------------------------");
  Serial.println("STEP 2: Entering Monitoring Mode");
  Serial.println("");
}

void loop() {
  int current_val = readGasAverage(5);

  float diff = abs(current_val - air_ref);
  float percent_change = (diff / air_ref) * 100.0;

  // ---------------------- MAJOR GAS LEAK ------------------------
  if (percent_change > ALERT_THRESHOLD_PERCENT) {

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    Serial.println("GAS LEAK DETECTED! (HIGH LEVEL)");

    Serial.print("Current Value: ");
    Serial.println(current_val);

    Serial.print("Deviation: ");
    Serial.print(percent_change);
    Serial.println("%");

    Serial.println("------------------------------------------------------");
  }

  // ---------------------- SLIGHT GAS LEAK ------------------------
  else if (percent_change > SLIGHT_THRESHOLD_PERCENT) {

    // LED BLINK
    digitalWrite(LED_PIN, HIGH);
    delay(150);

    digitalWrite(LED_PIN, LOW);
    delay(150);

    // Buzzer BEEP
    digitalWrite(BUZZER_PIN, HIGH);
    delay(80);

    digitalWrite(BUZZER_PIN, LOW);
    delay(80);

    Serial.println("Slight Gas Leak Detected!");

    Serial.print("Current Value: ");
    Serial.println(current_val);

    Serial.print("Deviation: ");
    Serial.print(percent_change);
    Serial.println("%");

    Serial.println("------------------------------------------------------");
  }

  // ---------------------- NORMAL AIR -----------------------------
  else {

    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    Serial.println("Status: Air Normal");

    Serial.print("Current Value: ");
    Serial.println(current_val);

    Serial.print("Deviation: ");
    Serial.print(percent_change);
    Serial.println("%");

    Serial.println("------------------------------------------------------");
  }

  delay(MONITORING_INTERVAL);
}
