void goToPosition(int selectedStepper, int value){
  //Selector
  if(selectedStepper == Selector_Step_Pin){
    if(selectorPosition < value && value <= 75 && selectorPositionKnown == 1){
      digitalWrite(STCP, LOW);
      shiftOut(DS, SHCP, MSBFIRST, 0B00000000);
      digitalWrite(STCP, HIGH);
      word toMove = (value - selectorPosition)*800;              //800 = 16*200/4 (16 microsteps, 200 steps is equal to 1 full rotate, 4 mm thread pitch)
      delayMicroseconds(100);
      word i = 0;
      while(i < toMove){
        digitalWrite(Selector_Step_Pin, !digitalRead(Selector_Step_Pin));
        delayMicroseconds(50);
        i++;
        if(i == toMove){
          selectorPosition = value;
          delayMicroseconds(100);
          break;
        }
      }
    }
    if(selectorPosition > value && value >= 0 && selectorPositionKnown == 1){
      digitalWrite(STCP, LOW);
      shiftOut(DS, SHCP, MSBFIRST, 0B00000100);
      digitalWrite(STCP, HIGH);
      word toMove = (selectorPosition - value)*800;              //800 = 16*200/4 (16 microsteps, 200 steps is equal to 1 full rotate, 4 mm thread pitch)
      delayMicroseconds(100);
      word i = 0;
      while(i < toMove){
        digitalWrite(Selector_Step_Pin, !digitalRead(Selector_Step_Pin));
        delayMicroseconds(50);
        i++;
        if(i == toMove){
          selectorPosition = value;
          delayMicroseconds(100);
          break;
        }
      }
    }
  }
  
  //Bearings
  if(selectedStepper == Bearings_Step_Pin){
    if(bearingsPosition < value /*&& bearingsPositionKnown == 1 */&& value <= 300){
      digitalWrite(STCP, LOW);
      shiftOut(DS, SHCP, MSBFIRST, 0B00010000);
      digitalWrite(STCP, HIGH);
      word toMove = (value - bearingsPosition)*32;              //32 = 32(32 microsteps)
      delayMicroseconds(100);
      word i = 0;
      while(i < toMove){
        digitalWrite(Bearings_Step_Pin, !digitalRead(Bearings_Step_Pin));
        delayMicroseconds(100);
        i++;
        if(i == toMove){
          bearingsPosition = value;
          delayMicroseconds(100);
          break;
        }
      }
    }
    if(bearingsPosition > value && bearingsPositionKnown == 1 && value >= 0){
      digitalWrite(STCP, LOW);
      shiftOut(DS, SHCP, MSBFIRST, 0B00000000);
      digitalWrite(STCP, HIGH);
      word toMove = (bearingsPosition - value)*32;              //32 = 32(32 microsteps)
      delayMicroseconds(100);
      word i = 0;
      while(i < toMove){
        digitalWrite(Bearings_Step_Pin, !digitalRead(Bearings_Step_Pin));
        delayMicroseconds(100);
        i++;
        if(i == toMove){
          bearingsPosition = value;
          delayMicroseconds(100);
          break;
        }
      }
    }
  }

  //Extruder Feed Wheels
  if(selectedStepper == Extruder_Feed_Wheels_Step_Pin){
    if(extruderFeedWheelsRotationDirection == 1){
      digitalWrite(STCP, LOW);
      shiftOut(DS, SHCP, MSBFIRST, 0B00000000);
      digitalWrite(STCP, HIGH);
      delayMicroseconds(100);
    }
    if(extruderFeedWheelsRotationDirection == 0){
      digitalWrite(STCP, LOW);
      shiftOut(DS, SHCP, MSBFIRST, 0B00000001);
      digitalWrite(STCP, HIGH);
      delayMicroseconds(100);
    }
    word toMove = 340;                                      //320 = 16*200/10 (16 microsteps, 200 steps is equal to 1 full rotate, 8mm shaft diameter)
    int delayTime = 250;
    for(int i = 0; i <= value; i++){
      if(unloadingFilament == 1 && analogRead(filamentSensor) < 400){
        for(int x = 0; x <= 25*340; x++){
          digitalWrite(Extruder_Feed_Wheels_Step_Pin, !digitalRead(Extruder_Feed_Wheels_Step_Pin));
          delayMicroseconds(250);                            //250
        }
        break;
      }
      int j = 0;
      if(i >= 10 && delayTime > 50 && i <= 150){
        delayTime = delayTime - 5;
      }
      if(i >= value - 30 && delayTime <= 250){
        delayTime = delayTime + 5;
      }
      while(j < toMove){
        digitalWrite(Extruder_Feed_Wheels_Step_Pin, !digitalRead(Extruder_Feed_Wheels_Step_Pin));
        delayMicroseconds(delayTime);                            //250
        j++;
      }
      if(i >= value){
        break;
      }
    }    
  }
}
