/*
 * Filament slots positions for selector:
 * Filament 1:  74
 * Filament 2:  60
 * Filament 3:  46
 * Filament 4:  32
 * Filament 5:  18
 * 
 * Filament slots positions for bearings:
 * Filament 1: 250
 * Filament 2: 200
 * Filament 3: 150
 * Filament 4: 100
 * Filament 5: 60
 */

void selectFilament(int filamentSlotNumber){
  if(analogRead(filamentSensor) <= 500){
    if(selectorPositionKnown == 0){
      homeSelector();
      delay(500);
    }
    if(bearingsPositionKnown == 0){
      homeBearings();
    }
    if(filamentSlotNumber == 1){
      goToPosition(Selector_Step_Pin, 74);
      goToPosition(Bearings_Step_Pin, 250);
    }
    else if(filamentSlotNumber == 2){
      goToPosition(Selector_Step_Pin, 60);
      goToPosition(Bearings_Step_Pin, 200);
    }
    else if(filamentSlotNumber == 3){
      goToPosition(Selector_Step_Pin, 46);
      goToPosition(Bearings_Step_Pin, 150);
    }
    else if(filamentSlotNumber == 4){
      goToPosition(Selector_Step_Pin, 32);
      goToPosition(Bearings_Step_Pin, 100);
    }
    else if(filamentSlotNumber == 5){
      goToPosition(Selector_Step_Pin, 18);
      goToPosition(Bearings_Step_Pin, 60);
    }
  }
}
