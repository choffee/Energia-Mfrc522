/*
	Example file for communicating with the NFRC522. The program prints the card data.
	Created by Eelco Rouw - Originally adapted by Grant Gibson. 
*/

#include <Mfrc522.h>

// the sensor communicates using SPI, so include the library:
#include <SPI.h>

int chipSelectPin = 10;
int NRSTDP = 5;
Mfrc522 Mfrc522(chipSelectPin,NRSTDP);
unsigned char serNum[5];

void setup() 
{                
	Serial.begin(9600);                       // RFID reader SOUT pin connected to Serial RX pin at 2400bps 
	// Start the SPI library:
	SPI.begin();
	// Initialize the Card Reader
	digitalWrite(chipSelectPin, LOW);
	pinMode(RED_LED, OUTPUT);
	Mfrc522.Init();  
}

void loop()
{
	unsigned char i,tmp;
	unsigned char status;
	unsigned char str[MAX_LEN];
	unsigned char RC_size;
	unsigned char blockAddr;
	String mynum = "";
  	
	status = Mfrc522.Request(PICC_REQIDL, str);	
	if (status == MI_OK)
	{
		Serial.println("Card detected");
		Serial.print(str[0],BIN);
		Serial.print(" , ");
		Serial.print(str[1],BIN);
		Serial.println(" ");
	}

	status = Mfrc522.Anticoll(str);
	memcpy(serNum, str, 5);
	if (status == MI_OK)
	{
		Serial.println("The card's number is  : ");
		Serial.print(serNum[0]);
		Serial.print(" , ");
		Serial.print(serNum[1],BIN);
		Serial.print(" , ");
		Serial.print(serNum[2],BIN);
		Serial.print(" , ");
		Serial.print(serNum[3],BIN);
		Serial.print(" , ");
		Serial.print(serNum[4],BIN);
		Serial.println(" ");

		// Should really check all pairs, but for now we'll just use the first

		if(serNum[0] == 29) 
		{
			Serial.println("Hello Eelco");
			digitalWrite(RED_LED, HIGH);
			delay(1000);
			digitalWrite(RED_LED, LOW);
		}     
		delay(1000);	
	}
	//Serial.println(" ");
	Mfrc522.Halt();	                        
}
