void loadFilamentToSlot(int filamentNumber){
  if(analogRead(filamentSensor) >= 400){
    goToPosition(Bearings_Step_Pin, (bearingsPosition + 60));
    unloadingFilament = 1;
    extruderFeedWheelsRotationDirection = 0;
    if(analogRead(filamentSensor) >= 400){
      goToPosition(Extruder_Feed_Wheels_Step_Pin, loadDistance);
      unloadingFilament == 0;
    }
  }

  selectFilament(filamentNumber);
  extruderFeedWheelsRotationDirection = 1;
  while(analogRead(filamentSensor) <= 400){
    goToPosition(Extruder_Feed_Wheels_Step_Pin, 1);
  }
  extruderFeedWheelsRotationDirection = 0;
  goToPosition(Extruder_Feed_Wheels_Step_Pin, 25);
  goToPosition(Bearings_Step_Pin, (bearingsPosition - 60));
}
