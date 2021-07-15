#include <Arduino.h>
#include "freertos/task.h"
#define LED 2

TaskHandle_t task1 = NULL; //Handle das tasks 
TaskHandle_t task2 = NULL; //     1 e 2

void taskfunc1(void *pvParameter);// Declaração das funções 
void taskfunc2(void *pvParameter);//      das tasks


void setup() {
  
  xTaskCreate(taskfunc1,"TASK1",configMINIMAL_STACK_SIZE,NULL,1,&task1);
  xTaskCreate(taskfunc2,"TASK1",configMINIMAL_STACK_SIZE+1024,NULL,1,&task2);
  pinMode(LED,OUTPUT);
  Serial.begin(9600);

}
     
void loop() {
  vTaskDelay(pdMS_TO_TICKS(10));
} 

void taskfunc1(void *pvParameter){
  while(1){
    digitalWrite(LED,!digitalRead(LED));
    vTaskDelay(pdMS_TO_TICKS(1000));
  }



}

void taskfunc2(void *pvParameter){
  while(1){
    Serial.println("Olá FreeRTOS");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  

}