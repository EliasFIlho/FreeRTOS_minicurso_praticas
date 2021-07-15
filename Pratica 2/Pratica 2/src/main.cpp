#include <Arduino.h>
#include "freertos/task.h"
#define LED 2

TaskHandle_t task1 = NULL; //Handle das tasks 
TaskHandle_t task2 = NULL; //     1 e 2

void taskfunc1(void *pvParameter);// Declaração das funções 
void taskfunc2(void *pvParameter);//      das tasks


void setup() {
  
  xTaskCreate(taskfunc1,"TASK1",configMINIMAL_STACK_SIZE,NULL,1,&task1); //Criação das tasks
  xTaskCreate(taskfunc2,"TASK1",configMINIMAL_STACK_SIZE+1024,NULL,1,&task2);// 1 e 2
  pinMode(LED,OUTPUT); //Setando o GPIO2 como saida
  Serial.begin(9600); //Iniciando a comunicação serial
  
}
     
void loop() {

vTaskDelay(pdMS_TO_TICKS(10));
  
} 

void taskfunc1(void *pvParameter){
  while(1){
    digitalWrite(LED,HIGH);//
    vTaskDelay(pdMS_TO_TICKS(500));//invertendo o valor do LED a cada meio segundo
    digitalWrite(LED,LOW);//
    vTaskDelay(pdMS_TO_TICKS(500));//
  }



}

void taskfunc2(void *pvParameter){
  int cont = 0;
  while(1){
     Serial.println(cont);
     cont++;
     Serial.println("estado da task: " + String(eTaskGetState(task1)));
     if(cont >= 10){
      vTaskSuspend(task1); // Bloqueando a task
      Serial.println("estado da task: " + String(eTaskGetState(task1))); // Imprimindo o estado da task;
     }
     if (cont > 14 ){
      vTaskResume(task1); //
      Serial.println("estado da task: " + String(eTaskGetState(task1)));
      cont = 0;
     }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  

}