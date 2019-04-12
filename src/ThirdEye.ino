#include <DHT.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define RX 2
#define TX 3

String AP = "NAZMUL";       // CHANGE ME
String PASS = "3068073675"; // CHANGE ME
String HOST = "3217.000webhostapp.com";
String PORT = "80";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
SoftwareSerial esp8266(RX,TX); 

// constants won't change. They're used here to set pin numbers:
const int ldrPin = A0;  // the number of LDR probe pin
const int dhtPin = 6;  // the number of DHT11 humidity sensor pin
const int buttonPin = 4;  // the number of alarm stop button pin
const int piezoPin = 5; // the number of piezo buzzer pin
const int trigPin = A2;
const int echoPin = A3;
bool snoozeStatus=false;  // variable for storing the status of current snooze status
int buttonState = 0;  // variable for reading the pushbutton status
const int flamePin = A1; // the number of flame sensor
int intensityThreshold = 65;  // variable for light intensity threshold
int minIntensity = 1023;  // minimum LDR value
int maxIntensity = 0; // maximum LDR value
int lightIntensity = 0; // variable for reading light intensity
int flameValue = 0; //variable for reading flame sensor value
int temperaturePostValue=0;
int humidityPostValue=0;
int flamePostValue=0;
int alarmPostValue=0;
int lightPostValue=0;
int motionPostValue=0;
long duration,inches, cm;;
int distance;

#define DHTTYPE DHT11   // DHT 11 Type selection to use library
// Initialize DHT sensor.
DHT dht(dhtPin, DHTTYPE);
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void initWifi()
{
  esp8266.begin(115200);
   // Print a message to the LCD.

  sendCommand("AT+RST",5,"OK");
  sendCommand("AT+CWMODE=3",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
 
  }

// sensor calibration function
void sensorCalibrarion()
{
  // Calibrate LDR value for 5 seconds to get more accuracy
  while (millis() < 5000) {
    lightIntensity = analogRead(ldrPin);
    // record the maximum LDR value
    if (lightIntensity > maxIntensity) {
      maxIntensity = lightIntensity;
    }
    // record the minimum LDR value
    if (lightIntensity < minIntensity) {
      minIntensity = lightIntensity;
    }
  }
}

void postToServer()
{
  
 //String params=(String)temperaturePostValue + ":" + (String)lightPostValue + ":" ;
   String getData= "GET /postData.php?t="+ (String)temperaturePostValue; 
   getData=getData+"&l=" + (String)lightPostValue + "&f=" + (String)flamePostValue ; 
   getData=getData+"&a=" + (String)alarmPostValue + "&m=" + (String)motionPostValue + "&h=" + (String)humidityPostValue;   
   getData=getData+" HTTP/1.1\r\n";   
   getData=getData+"Host: 3217.000webhostapp.com\r\n";  

sendCommand("AT+CIPMUX=1",2,"OK");
// printResponse();  
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,3,"OK");

 
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),6,">"); 
 getData= "GET /postData.php?t="+ (String)temperaturePostValue; 
   getData=getData+"&l=" + (String)lightPostValue + "&f=" + (String)flamePostValue ; 
   getData=getData+"&a=" + (String)alarmPostValue + "&m=" + (String)motionPostValue + "&h=" + (String)humidityPostValue;   
   getData=getData+" HTTP/1.1\r\n";   
   getData=getData+"Host: 3217.000webhostapp.com\r\n";    
 esp8266.println(getData);
 //printResponse();
 countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");  
  
  }

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.println(" ");
  
  
  while(countTimeCommand < (maxTime*1))
  {
    //buttonState = digitalRead(buttonPin);
  //if (buttonState == HIGH) {
   // snoozeStatus=true;
    //digitalWrite(piezoPin,LOW);
    // alarmPostValue=0;
     
 // }
    esp8266.println(command);//at+cipsend
 //delay(100);
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("YES");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("NO");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
  
 }
void setup() {
  // Begin the serial output
  Serial.begin(9600); 
  // initialize the LDR pin as an input:
  pinMode(ldrPin, INPUT);
  // initialize the piezzo Buzzer pin as an output:
  pinMode(piezoPin,OUTPUT);  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    dht.begin();
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
   // Print a message to the LCD.
    lcd.print("Init ThirdEye...");
    sensorCalibrarion();
 lcd.clear();
  initWifi();
  lcd.clear();
  lcd.print("TEMP:   HUMID:   ");
  
}

void loop() {
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  lightIntensity = analogRead(ldrPin);
   flameValue = analogRead(flamePin);
  //map LDR value to keep in range 0-255
  lightIntensity = map(lightIntensity, minIntensity, maxIntensity, 0, 255);
  // if the LDR value is beyond the range 0-1023, keep it to 0-255
  lightIntensity = constrain(lightIntensity, 0, 255);
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidityPostValue = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temperaturePostValue = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  int f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidityPostValue) || isnan(temperaturePostValue) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
/*
 Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.println("");
  Serial.print("Flame :");

*/
// (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print(temperaturePostValue);
  lcd.print("C");
  lcd.setCursor(5,1);
  lcd.print("      ");
   lcd.setCursor(8,1);
  lcd.print(humidityPostValue);
   lcd.print("%");  
  //lcd.setCursor(10,1);
  //lcd.print("      ");
   //lcd.setCursor(10,1);
  //lcd.print(flameValue); 
   // check if the pushbutton is pressed. If so, set the snooze status to True

 // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(2);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
 motionPostValue=0;

if(inches < 200)
{
  motionPostValue=1;
  }
  Serial.println(motionPostValue); 
    alarmPostValue=0;
   
  if(lightIntensity>intensityThreshold)
  {
    lightPostValue=1;
    }
    else
    {
      lightPostValue=0;
      }
     alarmPostValue=0;
  if(flameValue > 400) {
    // check if snooze status is set

    flamePostValue=1;
          
     triggerAlarm();
    if (buttonState == HIGH) {
    alarmPostValue=1;
  }
    
    }
    else {
      flamePostValue=0;
     
      // else false
      snoozeStatus=false;
      digitalWrite(piezoPin,LOW);
    }  
postToServer();    
delay(1000);  
  
}

long microsecondsToInches(long microseconds) {
 
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {

  return microseconds / 29 / 2;
}

void triggerAlarm()
{
  
  digitalWrite(piezoPin,HIGH);
  /*
  // Turn ON the buzzer.Three notes are used in regular interval for smooth tone.
      tone(piezoPin, 400, 500); //the buzzer emit sound at 400 MHz for 500 millis
      delay(100); //wait 500 millis
      tone(piezoPin, 650, 500); //the buzzer emit sound at 650 MHz for 500 millis
      delay(100); //wait 500 millis 
      */
  }
