#include <Arduino.h>
#include "freertos/task.h"

#define LED 2
#define button 15

TaskHandle_t task1 = NULL;
TaskHandle_t task2 = NULL;

void task1function(void* pvParameters);
void task2function(void* pvParameters);

int cont = 0;

void isrhandle(){
  xTaskResumeFromISR(task1);
  cont = 0;
    
}

void setup() {

 pinMode(LED,OUTPUT);
 pinMode(button,INPUT); 
 Serial.begin(9600);
 attachInterrupt(digitalPinToInterrupt(button),isrhandle,RISING);
 xTaskCreate(task1function,"Task1",configMINIMAL_STACK_SIZE+1024,NULL,1,&task1);
 xTaskCreate(task2function,"Task2",configMINIMAL_STACK_SIZE+1024,NULL,1,&task2);

}

void loop(){
  vTaskDelay(pdMS_TO_TICKS(10));
}

void task1function(void* pvParameters){
  while (1){
    digitalWrite(LED,!digitalRead(LED));
    vTaskDelay(pdMS_TO_TICKS(500));
  }
    

}
void task2function(void* pvParameters){
  
  Serial.println("Testando chamada em interrupção.");
  while(1){
    cont++;
    Serial.println(cont);
    if(cont >= 10){
      vTaskSuspend(task1);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));

  }
      
}


 