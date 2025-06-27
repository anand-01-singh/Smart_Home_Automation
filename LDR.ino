#define BLYNK_TEMPLATE_ID "TMPL3qLPJ_LVA"
#define BLYNK_TEMPLATE_NAME "MY HOME"
#define BLYNK_AUTH_TOKEN "XYk4idbGW3_eluP1Yudd7M3k68CaiXdd"

// Reduce debug output to save memory
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

// Pin Definitions
#define FAN_PIN 3
#define ROOM_LIGHT_PIN 4
#define HALL_LIGHT_PIN 5
#define GARDEN_LIGHT_PIN 6
#define W5500_RST_PIN 9
#define W5500_CS_PIN 10

// Network Configuration
byte mac[] = { 0x02, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE };

// Reduced connection check interval to save memory
unsigned long lastConnectionCheck = 0;
const unsigned long CONNECTION_CHECK_INTERVAL = 60000; // 60 seconds
bool networkInitialized = false;

void setup() {
  Serial.begin(9600);
  Serial.println(F("HOME AUTOMATION v2.0"));
  
  // Initialize pins
  pinMode(FAN_PIN, OUTPUT);
  pinMode(ROOM_LIGHT_PIN, OUTPUT);
  pinMode(HALL_LIGHT_PIN, OUTPUT);
  pinMode(GARDEN_LIGHT_PIN, OUTPUT);
  pinMode(W5500_CS_PIN, OUTPUT);
  pinMode(W5500_RST_PIN, OUTPUT);
  
  // Set initial states
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(ROOM_LIGHT_PIN, LOW);
  digitalWrite(HALL_LIGHT_PIN, LOW);
  digitalWrite(GARDEN_LIGHT_PIN, LOW);
  digitalWrite(W5500_CS_PIN, HIGH);
  
  Serial.println(F("Devices initialized"));
  
  initializeNetwork();
  connectToBlynk();
  
  Serial.println(F("System ready!"));
}

void loop() {
  Blynk.run();
  Ethernet.maintain();
  
  if (millis() - lastConnectionCheck > CONNECTION_CHECK_INTERVAL) {
    checkConnections();
    lastConnectionCheck = millis();
  }
  
  delay(10);
}

void initializeNetwork() {
  Serial.println(F("Initializing network..."));
  
  // Reset W5500
  digitalWrite(W5500_RST_PIN, LOW);
  delay(50);
  digitalWrite(W5500_RST_PIN, HIGH);
  delay(200);
  
  Ethernet.init(W5500_CS_PIN);
  
  // Try DHCP, fallback to static IP if needed
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("DHCP failed, using static IP"));
    IPAddress ip(192, 168, 1, 100);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    IPAddress dns(8, 8, 8, 8);
    Ethernet.begin(mac, ip, dns, gateway, subnet);
  } else {
    Serial.println(F("DHCP OK"));
  }
  
  delay(2000);
  printNetworkInfo();
  networkInitialized = true;
}

void connectToBlynk() {
  Serial.println(F("Connecting to Blynk..."));
  Blynk.begin(BLYNK_AUTH_TOKEN, "blynk.cloud", 80);
  
  int attempts = 0;
  while (!Blynk.connected() && attempts < 10) {
    Serial.print(F("Attempt: "));
    Serial.println(attempts + 1);
    Blynk.run();
    delay(1000);
    attempts++;
  }
  
  if (Blynk.connected()) {
    Serial.println(F("Blynk connected!"));
  } else {
    Serial.println(F("Blynk connection failed"));
  }
}

void printNetworkInfo() {
  Serial.print(F("IP: "));
  Serial.println(Ethernet.localIP());
  Serial.print(F("Gateway: "));
  Serial.println(Ethernet.gatewayIP());
}

void checkConnections() {
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println(F("Ethernet disconnected"));
    return;
  }
  
  if (!Blynk.connected()) {
    Serial.println(F("Blynk reconnecting..."));
  }
}

// Device Control Functions
BLYNK_WRITE(V0) {
  int state = param.asInt();
  digitalWrite(FAN_PIN, state);
  Serial.print(F("Fan: "));
  Serial.println(state ? F("ON") : F("OFF"));
  Blynk.virtualWrite(V0, state);
}

BLYNK_WRITE(V1) {
  int state = param.asInt();
  digitalWrite(ROOM_LIGHT_PIN, state);
  Serial.print(F("Room: "));
  Serial.println(state ? F("ON") : F("OFF"));
  Blynk.virtualWrite(V1, state);
}

BLYNK_WRITE(V2) {
  int state = param.asInt();
  digitalWrite(HALL_LIGHT_PIN, state);
  Serial.print(F("Hall: "));
  Serial.println(state ? F("ON") : F("OFF"));
  Blynk.virtualWrite(V2, state);
}

BLYNK_WRITE(V3) {
  int state = param.asInt();
  digitalWrite(GARDEN_LIGHT_PIN, state);
  Serial.print(F("Garden: "));
  Serial.println(state ? F("ON") : F("OFF"));
  Blynk.virtualWrite(V3, state);
}

BLYNK_CONNECTED() {
  Serial.println(F("Blynk connected!"));
  
  // Sync device states
  Blynk.virtualWrite(V0, digitalRead(FAN_PIN));
  Blynk.virtualWrite(V1, digitalRead(ROOM_LIGHT_PIN));
  Blynk.virtualWrite(V2, digitalRead(HALL_LIGHT_PIN));
  Blynk.virtualWrite(V3, digitalRead(GARDEN_LIGHT_PIN));
  
  Serial.println(F("States synced"));
}

BLYNK_DISCONNECTED() {
  Serial.println(F("Blynk disconnected"));
}