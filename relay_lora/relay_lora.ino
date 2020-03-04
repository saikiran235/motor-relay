


#include "device_config.h"
#include <Ticker.h>
/*!
   @var     struct device_info dev_info
   @brief   Contains device specific info
 */
#define buffer_size 50

 char ack[10];
 char received_dev_id[10];

int button_pressed = _UNDEFINED;

bool Mode = 0;
/*!
   @var     const unsigned long frequency
   @brief   The frequency in MHz on which LoRa device communicates
*/
const unsigned long frequency             = 865E6;

/*!
   @var     const uint8_t sync_word
   @brief   A unique value for synchronisation between Tx and Rx
*/
const byte          sync_word             = 0xBB;

bool                LoRa_ack = false;    

unsigned long       start_time = 0;
unsigned long       status_time = 30000;
unsigned long       status_delay =70000;
 


int                 ON_button_state = HIGH;     

int                 OFF_button_state = HIGH;             

int                 last_ON_button_state = HIGH;

int                 last_OFF_button_state = HIGH;

unsigned long       ON_button_last_debounce_time = 0;

unsigned long       OFF_button_last_debounce_time = 0;

unsigned long       debounce_delay = 50;  

int flag;
bool status_flag = 0;
bool status_var;
Ticker ticker;
void tik()
{
 digitalWrite(Status_LED,Mode);
 Mode = !Mode;
    }
void setup()
{
  Serial.begin(115200);
  delay(2000);
  pinMode(ON_BUTTON_PIN, INPUT);
  pinMode(OFF_BUTTON_PIN, INPUT);
  pinMode(LoRa_LED, OUTPUT);
  pinMode(Status_LED,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ON_BUTTON_PIN), ON_buttonPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(OFF_BUTTON_PIN), OFF_buttonPressed, FALLING);
  digitalWrite(LoRa_LED, LOW);
  digitalWrite(Status_LED,LOW);
  //print_welcome_msg();



  //Initialize the LoRa subsystem
  init_lora(frequency, sync_word);
  
}
void loop(){
   char tx_packet_buffer[50] = {0};
  char rx_packet_buffer[200] = {0};
  
  int ON_button_reading = digitalRead(ON_BUTTON_PIN);
  int OFF_button_reading = digitalRead(OFF_BUTTON_PIN);
  ////////////////////////////////////////
  if (ON_button_reading != last_ON_button_state)
  {
    // reset the debouncing timer
    ON_button_last_debounce_time = millis();
  }
  
  if ((millis() - ON_button_last_debounce_time) > debounce_delay)
  {
    if (ON_button_reading != ON_button_state)
    {
      ON_button_state = ON_button_reading;
      if (ON_button_state == LOW)
      {
       if(button_pressed == ON_BUTTON_PRESSED)
       {
          Serial.println("\nON BUTTON PRESSED");
        create_json_object(tx_packet_buffer, sizeof(tx_packet_buffer));
        send_lora_data(tx_packet_buffer);
        button_pressed = _UNDEFINED; 
      }
     }
      attachInterrupt(digitalPinToInterrupt(ON_BUTTON_PIN), ON_buttonPressed, FALLING);
    
    }
    //attachInterrupt(digitalPinToInterrupt(OFF_BUTTON_PIN), OFF_buttonPressed, FALLING); 
  }

 if (OFF_button_reading != last_OFF_button_state)
  {
    // reset the debouncing timer
    OFF_button_last_debounce_time = millis();
  }
  
  if ((millis() - OFF_button_last_debounce_time) > debounce_delay)
  {
    if (OFF_button_reading != OFF_button_state)
    {
      OFF_button_state = OFF_button_reading;
      if (OFF_button_state == LOW)
      {
        if(button_pressed == OFF_BUTTON_PRESSED)
       {
        Serial.println("\nOFF BUTTON PRESSED");
        create_json_object(tx_packet_buffer, sizeof(tx_packet_buffer));
        send_lora_data(tx_packet_buffer);
        button_pressed = _UNDEFINED;
       }
      }
      attachInterrupt(digitalPinToInterrupt(OFF_BUTTON_PIN), OFF_buttonPressed, FALLING);    
 
   }
    //attachInterrupt(digitalPinToInterrupt(ON_BUTTON_PIN), ON_buttonPressed, FALLING);
  
  }
  // save the reading. Next time through the loop, it'll be the last_ON_button_state:
    last_ON_button_state = ON_button_reading;
    last_OFF_button_state = OFF_button_reading;
    
   
   
   if(receive_lora_packet(rx_packet_buffer))
      {
        if(strlen(rx_packet_buffer) < buffer_size)
        {
        if(parse_json(rx_packet_buffer, sizeof(rx_packet_buffer)))
        {
         
          int val;
          val = atoi(ack);
           switch(val)
           {
            case 0:{
              digitalWrite(LoRa_LED,LOW);

              //attachInterrupt(digitalPinToInterrupt(OFF_BUTTON_PIN), OFF_buttonPressed, FALLING);
              }
              break;
            case 1:{
              digitalWrite(LoRa_LED,HIGH);

              //attachInterrupt(digitalPinToInterrupt(ON_BUTTON_PIN), ON_buttonPressed, FALLING);
              }
              break;
            case 2:{
             ticker.attach(0.2,tik);
              status_time = millis();   
              digitalWrite(LoRa_LED,status_var);
              }
              break;
            default:
            break;
           }
         }
        }
       }
       else{
         if((start_time - status_time) > status_delay)
         {
            digitalWrite(LoRa_LED, LOW);
            ticker.detach();
            digitalWrite(Status_LED,LOW);
            status_time = start_time;
          }  
       }
start_time = millis();
delay(1);
}

ICACHE_RAM_ATTR void ON_buttonPressed()
{
   // if (ON_button_state == HIGH)
      //{
    detachInterrupt(digitalPinToInterrupt(ON_BUTTON_PIN));
    //detachInterrupt(digitalPinToInterrupt(OFF_BUTTON_PIN));
    button_pressed = ON_BUTTON_PRESSED;

      //}
}

ICACHE_RAM_ATTR void OFF_buttonPressed()
{
    //if (OFF_button_state == HIGH)
      //{
    //detachInterrupt(digitalPinToInterrupt(ON_BUTTON_PIN));
    detachInterrupt(digitalPinToInterrupt(OFF_BUTTON_PIN));
    button_pressed = OFF_BUTTON_PRESSED;
      //}
}
