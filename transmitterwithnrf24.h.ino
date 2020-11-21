#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define CE_PIN   8
#define CSN_PIN 7

const byte slaveAddress[5] = {'R','x','A','A','A'};


RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

char dataToSend[] = "Hello Reciever!";
char txNum = '0';


unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000; // send once per second


void setup() {

    Serial.begin(9600);
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5); // delay, count
    radio.openWritingPipe(slaveAddress);
    radio.setPALevel(RF24_PA_MIN);
}

void loop() {
    currentMillis = millis();
    if (currentMillis - prevMillis >= txIntervalMillis) {
        send();
        prevMillis = millis();
    }
}


void send() {

    bool rslt;
    rslt = radio.write( &dataToSend, sizeof(dataToSend) );
    Serial.print("Data Sent ");
    Serial.print(dataToSend);
    if (rslt) {
        Serial.println("  Acknowledge received");
    }
    else {
        Serial.println("  Tx failed");
    }
}
