#include <FastLED.h>

//DEFINE LEDS
#define NUM_LEDS 66
#define LED_PIN 2
#define irSensor 26
CRGB leds[NUM_LEDS];

#define irSensor 26

int count1 = 0;
int count2 = 0;

TaskHandle_t task1_handle = NULL;


//Creating two tasks that loops around the ledstrip
void task1(void * parameteres){
  while(true){
    //LOOP through ledstrip
    for (int i=0;i<NUM_LEDS;i++){
      leds[i] = CHSV( random(160,200), 200,200);
      FastLED.show();
      vTaskDelay(300/ portTICK_PERIOD_MS);
    }
  }
}


/*Task2 using IRsensor to measure distance 
If it gets close it sets the delay of the thread to between 200 and 30ms.
Default set at 1500ms*/

void task2(void * parameteres){
  int irDelay=500; 
  int irValue = 500;
  while(true){
    count2++;
    irValue = analogRead(irSensor);
    if(irValue>100){                            //Gets rid of false readings, sits around 18-40
      irDelay = map(irValue,16,2500,250,30);    //Never got above 2000 with my sensor
    }
    else{
      irDelay = 1500;
    }
    
    leds[count2] = CHSV( random(70,100), 200,200);
    FastLED.show();
    vTaskDelay(irDelay/ portTICK_PERIOD_MS);
   
    if(count2 == NUM_LEDS){
      count2 = 0;
    }
  }
}


//------------SETUP----------//
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //SETUP LEDS:
  FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);

  //Create two different tasks
  xTaskCreate(
    task1,    //function name
    "task 1", //task name
    1000,      //stack size
    NULL,     //Task paramters
    1,        //task priority
    &task1_handle      //task handle
    );

    xTaskCreate(
    task2,    //function name
    "task 2", //task name
    1000,     //stack size
    NULL,     //Task paramters
    1,        //task priority
    NULL      //task handle
    );

}
//------------SETUP DONE----------//



void loop() {
  // put your main code here, to run repeatedly:

}
