  const byte Microphone = 3;                         // Звуковой сенсор на пин 3
  const byte LampR = 0;                              // Пин 0
  const byte LampG = 1;                              // Пин 1
  const byte LampB = 2;                              // Пин 2
  int clap = 0;                                     // Переменная для хранения хлопков
  unsigned long Start_time = 0;                              // Время после первого хлопка
  unsigned long detection_range = 0;                         // Диапазон между хлопками
  bool status_lights = false;                       // При загрузке значение False
  int mode = 0;

void setup()
{
  pinMode(Microphone, INPUT);
  pinMode(LampR, OUTPUT);
  pinMode(LampG, OUTPUT);
  pinMode(LampB, OUTPUT);
}

void loop()
{
  int status_sensor = digitalRead(Microphone);      // Считываем значения со звукового датчика   

  if (status_sensor == 1) {                         // Если пришёл сигнал  
    if (clap == 0) {                                // Если хлопокв ещё не было    
      Start_time = detection_range = millis();      // Присваиваем текущее время переменным
      clap++;                                       // Увеличиваем количество хлопков
    }
    else if (clap > 0 && millis() - detection_range >= 50) {  // Если хлопков больше 0 и диапазон больше 50 мс
      detection_range = millis();
      clap++;                                       // Увеличиваем количество хлопков
    }
  }
  if (millis() - Start_time >= 800) {              // Если прошло больше 4/5 секунды     
    if (clap == 3){                                // Если 3 хлопка, то меняем режим
      mode++;

      if (mode > 3) {
        mode = 0;
      }
    }
    else if (clap == 2){                            // Если 2 хлопка, то включаем 
      if (!status_lights)                           // Меняем статус
        {
          status_lights = true;
        }
        else if (status_lights) {
          status_lights = false;
        }
    }
    clap = 0;
  }
  if (status_lights){                               //Режимы, вкл и выкл лампы
    if (mode == 0){
      analogWrite(LampR, 255);
      analogWrite(LampG, 230);
      analogWrite(LampB, 170);
    }
    else if (mode == 1){
      analogWrite(LampR, 255);
      analogWrite(LampG, 55);
      analogWrite(LampB, 0);
    }
    else if (mode == 2){
      analogWrite(LampR, 80);
      analogWrite(LampG, 200);
      analogWrite(LampB, 250);
    }
    else if (mode == 3){
      analogWrite(LampR, 255);
      analogWrite(LampG, 50);
      analogWrite(LampB, 60);
    }
  }
  else if (!status_lights){
      analogWrite(LampR, 0);
      analogWrite(LampG, 0);
      analogWrite(LampB, 0);
  }
}
