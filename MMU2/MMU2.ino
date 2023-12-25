#include <TMCStepper.h>

int loadDistance = 440;

//Change values here
const int Extruder_Feed_Wheels_Stepper_Current = 600;
const int Bearings_Stepper_Current = 800;
const int Selector_Stepper_Current = 600;

#define SELECTOR_STALL_VALUE                5                                                   // [-64..63]
#define BEARINGS_STALL_VALUE                6
#define EXTRUDER_FEED_WHEELS_STALL_VALUE    0


#define R_SENSE                   0.2f

#define Selector_Step_Pin         4                                                   // Step
#define Selector_Cs_Pin           6                                                   // Chip select
int selectorPosition;
TMC2130Stepper Selector_Stepper(Selector_Cs_Pin, R_SENSE);                            // Hardware SPI

#define Bearings_Step_Pin         12                                                   // Step
#define Bearings_Cs_Pin           11                                                   // Chip select
int bearingsPosition;
TMC2130Stepper Bearings_Stepper(Bearings_Cs_Pin, R_SENSE);                            // Hardware SPI

#define Extruder_Feed_Wheels_Step_Pin         8                                                   // Step
#define Extruder_Feed_Wheels_Cs_Pin           5                                                   // Chip select
int extruderFeedWheelsPosition;
TMC2130Stepper Extruder_Feed_Wheels_Stepper(Extruder_Feed_Wheels_Cs_Pin, R_SENSE);                            // Hardware SPI

using namespace TMC2130_n;

// Define Connections to 74HC595
const int STCP = 10;                                                                  // ST_CP pin D10
const int SHCP = 13;                                                                  // SH_CP pin D13
const int DS = 9;                                                                     // DS pin D9

bool selectorPositionKnown = 0;
bool bearingsPositionKnown = 0;
bool extruderFeedWheelsRotationDirection = 0;                                                                //if 1 extruder feed wheels will move forward, if 0 backward
#define filamentSensor A1

bool unloadingFilament = 0;                                                                                  //fi 1 unloading filament

String reading="";

void setup() {
  SPI.begin();
  Serial.begin(115200);
  //while(!Serial);

  pinMode(MISO, INPUT_PULLUP);
 
  pinMode(Selector_Step_Pin, OUTPUT);
  pinMode(Selector_Cs_Pin, OUTPUT);

  pinMode(Bearings_Step_Pin, OUTPUT);
  pinMode(Bearings_Cs_Pin, OUTPUT);

  pinMode(Extruder_Feed_Wheels_Step_Pin, OUTPUT);
  pinMode(Extruder_Feed_Wheels_Cs_Pin, OUTPUT);
  
  //Selector Stepstick SetUp
  Selector_Stepper.begin();
  Selector_Stepper.toff(4);
  Selector_Stepper.blank_time(24);
  Selector_Stepper.rms_current(Selector_Stepper_Current); // mA
  Selector_Stepper.microsteps(16);
  Selector_Stepper.en_pwm_mode(true);
  Selector_Stepper.pwm_autoscale(true);
  Selector_Stepper.TCOOLTHRS(0xFFFFF); // 20bit max
  Selector_Stepper.THIGH(0);
  Selector_Stepper.semin(5);
  Selector_Stepper.semax(2);
  Selector_Stepper.sedn(0b01);
  Selector_Stepper.sgt(SELECTOR_STALL_VALUE);

  //Bearings Stepstick SetUp
  Bearings_Stepper.begin();
  Bearings_Stepper.toff(4);
  Bearings_Stepper.blank_time(24);
  Bearings_Stepper.rms_current(Bearings_Stepper_Current); // mA
  Bearings_Stepper.microsteps(32);
  Bearings_Stepper.en_pwm_mode(true);
  Bearings_Stepper.pwm_autoscale(true);
  Bearings_Stepper.TCOOLTHRS(0xFFFFF); // 20bit max
  Bearings_Stepper.THIGH(0);
  Bearings_Stepper.semin(5);
  Bearings_Stepper.semax(2);
  Bearings_Stepper.sedn(0b01);
  Bearings_Stepper.sgt(BEARINGS_STALL_VALUE);

  //Extruder Feed Wheels Stepstick SetUp
  Extruder_Feed_Wheels_Stepper.begin();
  Extruder_Feed_Wheels_Stepper.toff(4);
  Extruder_Feed_Wheels_Stepper.blank_time(24);
  Extruder_Feed_Wheels_Stepper.rms_current(Extruder_Feed_Wheels_Stepper_Current); // mA
  Extruder_Feed_Wheels_Stepper.microsteps(16);
  Extruder_Feed_Wheels_Stepper.en_pwm_mode(true);
  Extruder_Feed_Wheels_Stepper.pwm_autoscale(true);
  Extruder_Feed_Wheels_Stepper.TCOOLTHRS(0xFFFFF); // 20bit max
  Extruder_Feed_Wheels_Stepper.THIGH(0);
  Extruder_Feed_Wheels_Stepper.semin(5);
  Extruder_Feed_Wheels_Stepper.semax(2);
  Extruder_Feed_Wheels_Stepper.sedn(0b01);
  Extruder_Feed_Wheels_Stepper.sgt(EXTRUDER_FEED_WHEELS_STALL_VALUE);

  // Setup 74HC595 pins as Outputs
  pinMode(STCP, OUTPUT);
  pinMode(SHCP, OUTPUT);
  pinMode(DS, OUTPUT);
}

void loop() {
  static uint32_t last_time=0;
  uint32_t ms = millis();

  if(Serial.available() > 0) {
      reading=Serial.readString();
      reading.trim();
/*      if (read_byte == '0')      {
        selectorMoveEnable = 0;
      }
      else if (read_byte == '1') {
      digitalWrite(STCP, LOW);
      shiftOut(DS, SHCP, MSBFIRST, 0B00000000);
      digitalWrite(STCP, HIGH);
      selectorMoveEnable = 1;
      move(Selector_Step_Pin, 1);
      }
      else if (read_byte == '2') {
      digitalWrite(STCP, LOW);
      shiftOut(DS, SHCP, MSBFIRST, 0B00000100);
      digitalWrite(STCP, HIGH);
      selectorMoveEnable = 1;
      move(Selector_Step_Pin, 1);
      }*/
      if (reading == "homeSelector") {
        homeSelector();
      }
      else if(reading == "homeBearings"){
        homeBearings();
      }
      else if(reading == "TS0"){
        loadFilamentToSlot(1);
      }
      else if(reading == "TS1"){
        loadFilamentToSlot(2);
      }
      else if(reading == "TS2"){
        loadFilamentToSlot(3);
      }
      else if(reading == "TS3"){
        loadFilamentToSlot(4);
      }
      else if(reading == "TS4"){
        loadFilamentToSlot(5);
      }
      //else if(reading == "loadFilament"){
        //loadFilamentToSlot(1);
      //}
      //else if(reading != "s"){
        //goToPosition(Bearings_Step_Pin, reading.toInt());
      //}
       else if(reading == "T0"){
        loadFilamentToNozzle(1);
      }
       else if(reading == "T1"){
        loadFilamentToNozzle(2);
      }
       else if(reading == "T2"){
        loadFilamentToNozzle(3);
      }
       else if(reading == "T3"){
        loadFilamentToNozzle(4);
      }
       else if(reading == "T4"){
        loadFilamentToNozzle(5);
      }
  }

   //digitalWrite(Selector_Step_Pin, !digitalRead(Selector_Step_Pin));
   //delayMicroseconds(100);

  if((ms-last_time) > 100) { //run every 0.1s
    last_time = ms;

    //DRV_STATUS_t drv_status{0};
    //drv_status.sr = Selector_Stepper.DRV_STATUS();

    //Serial.println(analogRead(A1));

    /*Serial.print("0 ");
    Serial.print(drv_status.sg_result, DEC);
    Serial.print(" ");
    Serial.println(Selector_Stepper.cs2rms(drv_status.cs_actual), DEC);*/

   
  }
}
