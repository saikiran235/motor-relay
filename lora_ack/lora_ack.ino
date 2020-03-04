#include "lora.h"
#include "json.h"
#define relay 17
#define led 16
#define buffer_size 50
bool valid_data_rxvd=false;
char state[10];
extern char device_id[10];
bool flag;
extern bool status_var;
unsigned long       interval_delay = 0;
unsigned long       start_time = 0;
uint8_t sync_word=0xBB; const unsigned long frequency=865E6;
void send_ack()
{
  char send_buf[50]={0};
  create_json_object(send_buf,sizeof(send_buf));
  send_lora_data(send_buf);
  memset(state,'\0',sizeof(state));
 }
void setup()
{
 Serial.begin(115200);
 delay(2000);
 while(!Serial);
 init_lora(frequency,sync_word);
 pinMode(led,OUTPUT);
 pinMode(relay,OUTPUT);
 digitalWrite(led,0);
 digitalWrite(relay,0);
}
void loop() 
{
   char buf[200]={0};
   int val;
  if(receive_lora_packet(buf))
  { 
    if(strlen(buf) < buffer_size)
    {
     parse_json(buf,sizeof(buf));
     if(strcmp(device_id,"LoRa_1") == 0)
     {
     if(valid_data_rxvd)
     {
      val=atoi(state);
      switch(val)
      {
      case 0:
      {status_var =  0;
      digitalWrite(led,status_var);
      digitalWrite(relay,status_var);
      Serial.println("LED:OFF");
      Serial.println("RELAY:OFF");
      Serial.println("ACK_OFF SENT");
      send_ack();
        }break;
      
        case 1:
        { status_var = 1;
      digitalWrite(led,status_var);
      digitalWrite(relay,status_var);
      Serial.println("LED:ON");
      Serial.println("RELAY:ON");
      Serial.println("ACK_ON SENT"); 
       send_ack();
      }break;
      }
      valid_data_rxvd=false;
      }
    }
   } 
  }
    if((millis() - start_time) > interval_delay)
     {
       char tx_packet_buffer[50] = {0};
         flag = 1;
         create_json_object(tx_packet_buffer, sizeof(tx_packet_buffer));
         send_lora_data(tx_packet_buffer);
         start_time = millis(); 
         interval_delay = 31000;        
       }
    delay(1);
 
}
