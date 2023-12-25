void homeBearings(){
  DRV_STATUS_t drv_status{0};
  digitalWrite(STCP, LOW);
  shiftOut(DS, SHCP, MSBFIRST, 0B00010000);
  digitalWrite(STCP, HIGH);

  for(int i = 0; i <= 32*300; i++){
    digitalWrite(Bearings_Step_Pin, !digitalRead(Bearings_Step_Pin));
    delayMicroseconds(200);
  }

  digitalWrite(STCP, LOW);
  shiftOut(DS, SHCP, MSBFIRST, 0B00000000);
  digitalWrite(STCP, HIGH);

  for(int i = 0; i <= 32*300; i++){
    digitalWrite(Bearings_Step_Pin, !digitalRead(Bearings_Step_Pin));
    delayMicroseconds(150);
    drv_status.sr = Bearings_Stepper.DRV_STATUS();
  }


  drv_status.sr = Bearings_Stepper.DRV_STATUS();
  while(drv_status.sg_result >= 0){
    digitalWrite(Bearings_Step_Pin, !digitalRead(Bearings_Step_Pin));
    delayMicroseconds(100);

    drv_status.sr = Bearings_Stepper.DRV_STATUS();
    
    if(drv_status.sg_result <= 200){
      bearingsPosition = 0;
      delayMicroseconds(100);
      bearingsPositionKnown = 1;
      delayMicroseconds(100);
      break;
    }
  }
}
