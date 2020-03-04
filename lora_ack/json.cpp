/****************************************************************
              _____  _____  _   _______   ___
             |  __ \| ____|| | |__   __| / _ \   TM
             | |  \ | |___ | |    | |   / / \ \
             | |  | | ____|| |    | |  | |___| |
             | |_/  | |___ | |___ | |  |  ___  |
             |_____/|_____||_____||_|  |_|   |_|


  COPYRIGHT:
  Copyright (c) DELTA THINGS Pvt Ltd as an unpublished work
  THIS SOFTWARE AND/OR MATERIAL IS THE PROPERTY OF
  DELTA THINGS Pvt Ltd.  ALL USE, DISCLOSURE, AND/OR
  REPRODUCTION NOT SPECIFICALLY AUTHORIZED BY
  DELTA THINGS Pvt Ltd IS PROHIBITED.
****************************************************************/
/*!
   @file     json.cpp
*/
#include <ArduinoJson.h>
#include <Arduino.h>
#include "json.h"
//#include "device_config.h"
extern bool valid_data_rxvd; 
extern char state[10];
extern bool flag;
bool status_var;
char device_id[10];

//extern struct   device_info dev_info;
//extern String   received_device_id;
//extern String   pb_state;
//extern String   ppm_val;
/*!
   @var           bool ack
   @brief         flag to acknowledge the node that lora packet is received  .
*/
//bool LoRa_ack;

/*!
   @fn          void  create_json_object(char *tx_packet_buffer, const uint8_t tx_packet_buffer_size).
   @brief       creates JSON object.
   @param[out]  tx_packet_buffer Base address of a buffer in which JSON object to be stored
   @param[in]   tx_packet_buffer_size Size of the tx_packet_buffer
*/
void create_json_object( char *tx_packet_buffer, const uint8_t tx_packet_buffer_size)
{
#if ARDUINOJSON_VERSION_MAJOR==6
  StaticJsonDocument<150> jsonBuffer;
  JsonObject root = jsonBuffer.to<JsonObject>();
#else
  StaticJsonBuffer<150> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
#endif
  root["id"]    =device_id;
  if(strcmp(state,"1") == 0)
  {
  root["ack"]   ="1";
  flag=0;
  }
   else if(strcmp(state,"0") == 0)
  {
    root["ack"]   ="0";
   flag=0;
   }
   else if(flag==1)
   {
    root["ack"] = "2";
    root["status"] = status_var;
    flag=0;
    }
#if ARDUINOJSON_VERSION_MAJOR==6
  //serializeJsonPretty(root, tx_packet_buffer,tx_packet_buffer_size);
  serializeJson(root, tx_packet_buffer, tx_packet_buffer_size);
#else
  //root.prettyPrintTo(tx_packet_buffer, tx_packet_buffer_size);
  root.printTo(tx_packet_buffer, tx_packet_buffer_size);
#endif
}

/*!
   @fn        bool parse_json(char *packet_buffer,const uint8_t packet_buffer_size).
   @brief     Parses the JSON and values are extracted according to known keys.
   @param[in] packet_buffer base address of the memory location from where JSON object is stored.
   @param[in] packet_buffer_size size of the JSON object.

   @return
        - Returns true, if JSON parsing is successful.
        - Returns false, if JSON parsing fails.
*/

bool parse_json(char *packet_buffer, const uint8_t packet_buffer_size)
{
  char buff[100];
  memcpy(buff, packet_buffer, 100);
#if ARDUINOJSON_VERSION_MAJOR==6
  StaticJsonDocument<100> root;
  
#else
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(buff);
#endif

#if ARDUINOJSON_VERSION_MAJOR==6

  // Loop through all the key-value pairs in obj
  
  DeserializationError error = deserializeJson(root, buff);
  if (error)
  {
    Serial.print(F("[JSON]\t: deserializeJson() failed: "));
    Serial.println(error.c_str());
    return false;
  }
#else
  if (!root.success())
  {
    Serial.println(F("\n[ERROR]\t: JSON parsing failed"));
    return false;
  }
#endif
  Serial.println(F("\n[JSON]\t: Parsed"));
 char s[10];
   strcpy(s,root["s"]);
   strcpy(device_id,root["id"]);
  valid_data_rxvd=true;
    strcpy(state,s); 
   return true;
}

/** End of File Copyright ******************************************

   Copyright (c) DELTA THINGS Pvt Ltd as an unpublished work
   THIS SOFTWARE AND/OR MATERIAL IS THE PROPERTY OF
   DELTA THINGS Pvt Ltd.  ALL USE, DISCLOSURE, AND/OR
   REPRODUCTION NOT SPECIFICALLY AUTHORIZED BY
   DELTA THINGS Pvt Ltd IS PROHIBITED.

 *******************************************************************/
