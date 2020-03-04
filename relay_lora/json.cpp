
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
 * @file      json.cpp
 * @author    Delta Things.
 * @version   1.0
 * @date      15 March 2019
 * @pre       First initialize the system.
 * @bug       Not detected any.
 * @copyright (c) DELTA THINGS Pvt Ltd.
 */
#include <ArduinoJson.h>
#include "device_config.h"

extern struct                 device_info dev_info; 
//extern float                  v_bat;                            
//extern bool                ON_button_pressed;
//extern bool                OFF_button_pressed;          
extern bool                   LoRa_ack;    
extern int button_pressed;
String received_device_id;  
extern char ack[10]; 
extern char received_dev_id[10];
extern int flag;  
extern bool status_var;
/*!
 * @fn          void  create_json_object(char *tx_packet_buffer, const uint8_t tx_packet_buffer_size).
 * @brief       creates JSON object.
 * @param[out]  tx_packet_buffer Base address of a buffer in which JSON object to be stored
 * @param[in]   tx_packet_buffer_size Size of the tx_packet_buffer
 */

void create_json_object(char *tx_packet_buffer,  uint8_t tx_packet_buffer_size)
{
#if ARDUINOJSON_VERSION_MAJOR==6
  StaticJsonDocument<150> doc;
  JsonObject root = doc.to<JsonObject>();
#else
  StaticJsonBuffer<150> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
#endif
  root["id"]        = "LoRa_1";
  if(button_pressed == ON_BUTTON_PRESSED)
  {
    root["s"]       = String("1");
  }
  else if(button_pressed == OFF_BUTTON_PRESSED)
  {
    root["s"]       = String("0");
  }
 else if ((flag == 1) && (button_pressed == -1))
  {
    root["s"]   =    String("2");
    flag = 0;
  }
 
#if ARDUINOJSON_VERSION_MAJOR==6
  //serializeJsonPretty(root, tx_packet_buffer,tx_packet_buffer_size);
  serializeJson(root, tx_packet_buffer,tx_packet_buffer_size);
#else
  //root.prettyPrintTo(tx_packet_buffer, tx_packet_buffer_size);
  root.printTo(tx_packet_buffer, tx_packet_buffer_size);
#endif
#if SERIAL_DEBUG
  //Serial.println(strlen(tx_packet_buffer));
#endif
}

/*!
 * @fn        bool parse_json(char *packet_buffer,const uint8_t packet_buffer_size).
 * @brief     Parses the JSON and values are extracted according to known keys.
 * @param[in] packet_buffer base address of the memory location from where JSON object is stored.
 * @param[in] packet_buffer_size size of the JSON object.
 * 
 * @return
 *      - Returns true, if JSON parsing is successful.
 *      - Returns false, if JSON parsing fails.
 */
bool parse_json(char *packet_buffer, const uint8_t packet_buffer_size)
{
  char buff[100]={0};
  memcpy(buff, packet_buffer, 100);
  
#if ARDUINOJSON_VERSION_MAJOR==6
  StaticJsonDocument<100> root;

#else
  StaticJsonBuffer<100> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(buff);
#endif
#if ARDUINOJSON_VERSION_MAJOR==6
  DeserializationError error = deserializeJson(root, packet_buffer);
  // Test if parsing succeeds.
  if (error) 
  {
    Serial.print(F("[JSON]\t: deserializeJson() failed: "));
    Serial.println(error.c_str());
    return false;
  }
#else
  if (!root.success())
  {
    Serial.println("\n[ERROR]\t: JSON parsing failed");
    return false;
  }
#endif
  Serial.println(F("\n[JSON]\t: Parsed"));
  Serial.println(packet_buffer);
  
  strcpy(received_dev_id,root["id"]);
  strcpy(ack,root["ack"]);
  status_var = root["status"];
 
 return true;
}
