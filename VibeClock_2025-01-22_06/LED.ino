void updateClockFace(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  char funCharSeconds[3];
  strftime(funCharSeconds,3, "%S", &timeinfo);
  secondCounter = atoi(funCharSeconds);
  char funCharMinutes[3];
  strftime(funCharMinutes,3, "%M", &timeinfo);
  minuteCounter = atoi(funCharMinutes);
  
  if(currentMode == 1){
    for(int i=0; i<60; i++){
      if (i<minuteCounter){
        leds[i] = CHSV(expiredMinuteColor, 255, 255);
      }else{
        leds[i] = CHSV(minuteColor, 255, 255);
      }
    }
  }else if(currentMode == 2){
    for(int i=0; i<60; i++){
      if (i<minuteCounter){
        leds[i] = CHSV(expiredMinuteColor, 255, 255);
      }else{
        leds[i] = CHSV(minuteColor, 0, 0);
      }
    }
  }else if(currentMode == 3){
    for(int i=0; i<60; i++){
      if (i<minuteCounter){
        leds[i] = CHSV(expiredMinuteColor, 0, 0);
      }else{
        leds[i] = CHSV(minuteColor, 255, 255);
      }
    }
  }
  if(showSeconds){
    leds[secondCounter] = CHSV(secondColor, 255, 255);
  }
  FastLED.show();
}


void fastSecondCycle(){
  if(showSeconds){
    if((millis() % 1000 < 100) && (!secondTriggered)){
      countSeconds();
      secondTriggered = true;
    }
    if((millis()%1000 > 500) &&(secondTriggered)){
      secondTriggered = false;
    }
  }
  if(showSixtieths){
    if((millis() % (1000/60) < 2) && (!sixtiethTriggered)){
      countSixtiethSeconds();
      sixtiethTriggered = true;
    }
    if((millis() % (1000/60) > 2) && sixtiethTriggered){
      sixtiethTriggered = false;
    }
  }
}

void countSixtiethSeconds(){
  if(sixtiethCounter == 59){
    leds[59] = CHSV(sixtiethColor, 0, 0);
    leds[0] = CHSV(sixtiethColor, 255, 255);
    sixtiethCounter = 0;
  }else{
    if(sixtiethCounter == secondCounter){
      leds[sixtiethCounter] = CHSV(secondColor, 255, 255);
      sixtiethCounter++;
      leds[sixtiethCounter] = CHSV(secondColor, 255, 255);
    }else{
      leds[sixtiethCounter] = CHSV(sixtiethColor, 0, 0);
      sixtiethCounter++;
      leds[sixtiethCounter] = CHSV(sixtiethColor, 255, 255);
    }
  }
  FastLED.show();
}

void countSeconds(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  char funCharSeconds[3];
  strftime(funCharSeconds,3, "%S", &timeinfo);
  secondCounter = atoi(funCharSeconds);
  if(secondCounter == 0){
    leds[59] = CHSV(secondColor, 0, 0);
    leds[0] = CHSV(secondColor, 255, 255);
  }else{
    leds[secondCounter-1] = CHSV(secondColor, 0, 0);
    leds[secondCounter] = CHSV(secondColor, 255, 255);
  }
  FastLED.show();
}

void clearLEDs(){
  for (int i=0; i < NUM_LEDS; i++){
    leds[i] = CHSV(0, 0, 0);
  }
  FastLED.show();
}

void currentModeSwitch(){
  switch(currentMode){
    case 0:
      fastSecondCycle();
      break;
    case 1:
      updateClockFace();
      break;
    case 2:
      updateClockFace();
      break;
    case 3:
      updateClockFace();
      break;
    default:
      break;
  }
}
