void homeSelector(){
  DRV_STATUS_t drv_status{0};
  digitalWrite(STCP, LOW);
  shiftOut(DS, SHCP, MSBFIRST, 0B00000000);
  digitalWrite(STCP, HIGH);

  for(int i = 0; i <= 16*100; i++){
    digitalWrite(Selector_Step_Pin, !digitalRead(Selector_Step_Pin));
    delayMicroseconds(200);
  }

  digitalWrite(STCP, LOW);
  shiftOut(DS, SHCP, MSBFIRST, 0B00000100);
  digitalWrite(STCP, HIGH);

  for(int i = 0; i <= 16*100; i++){
    digitalWrite(Selector_Step_Pin, !digitalRead(Selector_Step_Pin));
    delayMicroseconds(50);
    drv_status.sr = Selector_Stepper.DRV_STATUS();
  }


  drv_status.sr = Selector_Stepper.DRV_STATUS();
  while(drv_status.sg_result > 0){
    digitalWrite(Selector_Step_Pin, !digitalRead(Selector_Step_Pin));
    delayMicroseconds(50);

    drv_status.sr = Selector_Stepper.DRV_STATUS();
    
    if(drv_status.sg_result == 0){
      selectorPosition = 0;
      delayMicroseconds(100);
      selectorPositionKnown = 1;
      delayMicroseconds(100);
      break;
    }
  }
}
