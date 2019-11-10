//Libs & Defs
#include <LiquidCrystal.h>

//LCD Section 
  #define RS 2    //Define Register Select
  #define E  3    //Define Enable
  #define D4 4    //Define Data Bit 4
  #define D5 5    //Define Data Bit 5
  #define D6 6    //Define Data Bit 5
  #define D7 7    //Define Data Bit 5

LiquidCrystal LCD(RS, E, D4, D5, D6, D7);   //Initialize LCD Attributes as previously defined

//Bluetooth Module Section
  #define BluetoothBaudRate 38400
  char BluetoothState = 0;        //a Variable to catch the State of the Bluetooth Module

//ACS712 Current Sensor0 Section
  #define SensorPin A0        //Define Sensor's Pin
  #define Sensitivity 185     //Sensitivity Values are "185 for 5A Sensor, 100 for 20A Sensor and 66 for 5A Sensor"
  #define OffsetVoltage 2500  //Define Offset Voltage Value as 2.5V
  int SensorReading = 0;      //a Variable to catch the State of the ACS712
  double Voltage = 0;         //a Variable to store the Value of the Voltage in mV
  double Result = 0;          //a Variable to store the Final Result
  double Time = 0;            //a Variable to catch the Time taken since the Arduino started running
  double Power= 0;            //a Variable to store the Power Result
  double Energy= 0;           //a Variable to store the Energy Result
  
void setup()
{
//Put the LCD Dimensions in Here
  LCD.begin(16, 2);
//Initialize the Serial Monitor as the Bluetooth Baud Rate (38400) to get a Reading from the Module  
  Serial.begin(BluetoothBaudRate);
}

void loop() 
{
  /*
  A- Get the Current Reading from the Sensor.
  
  B- Divide this Voltage Over 1024 to get
  the Value of the Actual Value, then multiply
  it by 5000 to get the current voltage in milliVolt.

  C- After that Subtract the Voltage from the Offset
  Voltage (given in Datasheet) and Divide that Voltage
  by the Sensitivity of the Sensor (given in Datasheet) 
  */ 
  SensorReading = analogRead(SensorPin);  //A
  Voltage = (SensorReading / 1024.0) * 5000;  //B
  Result = ((Voltage - OffsetVoltage) / Sensitivity); //C

  //Getting Other Values
  Power= Voltage * SensorReading; //Power = Voltage * Ampere
  Time = millis(); //Get The Time since the Arduino Started Running  
  Energy= Time * Power;

  //Getting Current Values for:
    //Current
  Serial.print("Current Reading of the Sensor = ");
  Serial.println(SensorReading);
    //Voltage
  Serial.print("Current Voltage = ");
  Serial.println(Voltage);
    //Power
  Serial.print("Current Power = ");
  Serial.println(Power);
    //Energy
  Serial.print("Current Energy = ");
  Serial.println(Energy);
      
  //Display the Results on LCD
    //Get Current Intensity
  LCD.print("I=");
  LCD.print(SensorReading);
  LCD.setCursor(7, 0);  //Change Cursor
  
    //Get Voltage
  LCD.print("V=");
  LCD.print(Voltage * 0.001);
  LCD.setCursor(0, 1);  //Change Cursor
  
    //Get Power    
  LCD.print("P=");
  LCD.print(Power);
  LCD.setCursor(7, 1);  //Change Cursor
  
    //Get Energy
  LCD.print("E=");
  LCD.print(Energy);

  
}
