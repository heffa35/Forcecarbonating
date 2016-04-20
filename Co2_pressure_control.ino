// Co2_pressure_control.ino
#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#define PRESSURE_READ A6
#define VALVE_OUTPUT 4
float pressure_real = 0.0;
float Temp = 0.0;
float pressure_set = 0.0;
float Co2Volum = 2.5;
bool valve = 0;
float deadband = 0.1;


float calc_pressure (float temp, float Co2Volum){
// Farenhight ,
// return -16.6999-(0.00116512*temp)+(0.00116512*(temp*temp))+(0.172254*(temp*setpoint))+(4.24267*setpoint)-(0.0684226*(setpoint*setpoint))*0.0689475729;

/* Celcius */ 
return -15.8302+(0.11603*temp)+(0.003775*(temp*temp))+(0.312037*(temp*Co2Volum))+(9.79*Co2Volum)-(0.068423*(Co2Volum*Co2Volum))*0.0689475729;
}
void setup() {
  Serial.begin(9600);
  sensors.begin();
  pinMode(VALVE_OUTPUT, OUTPUT);
  digitalWrite(VALVE_OUTPUT, LOW);
}

void loop() {
	sensors.requestTemperatures();
  /* TODO:
Adjust C02Volum with encoder
16x2 display


*/
	pressure_real = analogRead(PRESSURE_READ);// 0 - 1023
	pressure_real = map(pressure_real,0,1023,0,5000);
	Temp = sensors.getTempCByIndex(0);
	pressure_set =  calc_pressure(Temp, Co2Volum)*1000;

	if(pressure_real < pressure_set - deadband){
	    digitalWrite(VALVE_OUTPUT, HIGH);
	    valve=1;
	} else {
	    digitalWrite(VALVE_OUTPUT, LOW);
	    valve=0;
	}

	Serial.println(pressure_set);
	
	delay(1000);
}
