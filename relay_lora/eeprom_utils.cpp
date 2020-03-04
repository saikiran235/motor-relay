/****************************************************************
*             _____  _____  _   _______   ___
*            |  __ \| ____|| | |__   __| / _ \   TM
*            | |  \ | |___ | |    | |   / / \ \
*            | |  | | ____|| |    | |  | |___| |
*            | |_/  | |___ | |___ | |  |  ___  |
*            |_____/|_____||_____||_|  |_|   |_|
*
*
* COPYRIGHT:
* Copyright (c) DELTA THINGS Pvt Ltd as an unpublished work
* THIS SOFTWARE AND/OR MATERIAL IS THE PROPERTY OF
* DELTA THINGS Pvt Ltd.  ALL USE, DISCLOSURE, AND/OR
* REPRODUCTION NOT SPECIFICALLY AUTHORIZED BY
* DELTA THINGS Pvt Ltd IS PROHIBITED.
****************************************************************/
/*!
 *  @file      eeprom_utils.cpp
 *  @brief     EEPROM related operations
 *  @details   Saving and reading data to EEPROM.
 *  @author    Delta Things.
 *  @version   1.0
 *  @date      15 March 2019
 *  @pre       First initialize the system.
 *  @bug       Not detected any.
 *  @copyright (c) DELTA THINGS Pvt Ltd.
 */
#include "device_config.h"

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
/*!
 * @fn      bool init_eeprom()
 * @brief   initialises the EEPROM.
 * @return
 *      - true if initialization succeeds.
 *      - false if initilization fails.
 */
bool init_eeprom()
{
  EEPROM.begin();
  return true;
}
#elif defined(ESP32)
/*!
 * @fn      bool init_eeprom(int size)
 * @brief   initialises the EEPROM.
 * @param[in]   size physical size of the EEPROM in bytes.
 * @return
 *      - true if initialization succeeds.
 *      - false if initilization fails.
 */
bool init_eeprom(int size)
{
  if(!EEPROM.begin(size))
  {
    delay(1000);
    return false;
  }
  return true;
}
#elif defined(ESP8266)
/*!
 * @fn      void init_eeprom(int size)
 * @brief   initialises the EEPROM.
 * @param[in]   size physical size of the EEPROM in bytes.
 * 
  */
void init_eeprom(int size)
{
  EEPROM.begin(size);
}
#endif

/*!
 * @fn      String read_from_eeprom(int addr)
 * @brief   reads data from EEPROM from address provided as an argument to it and returns the data in Arduino String format.
 * @param[in]   addr address of the memory location.
 * @return  String.
 */
String read_from_eeprom(int addr)
{
  uint8_t len = (uint8_t)EEPROM.read(addr);  ///< unit8_t len
  addr++;
  String data;                               ///< String data
  for(int i = 0;i<len;i++)
  {
    data += (char)EEPROM.read(addr); 
    addr++;
  }
/*!<data.trim(); This call removes spaces from the string, use carefully. */
    return data;
}

/*!
 * @fn      void save_to_eeprom(int addr, String data)
 * @brief   Saves data in Arduino String format to EEPROM at a given address.
 * @param[in]   addr Base address of a EEPROM location from where data to be stored.
 * @param[in]   data  data in Arduino String format.
 */
void save_to_eeprom(int addr ,String data)
{
  EEPROM.write(addr,(uint8_t)data.length());
  #if defined(ESP8266) || defined(ESP32)
  EEPROM.commit();
  #endif
  addr++;

  for(int i=0;i<data.length();i++)
  {
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    EEPROM.update(addr+i,data[i]);
#else
    EEPROM.write(addr+i,data[i]);
#endif
  }
  /*!< EEPROM.write(addr+_size,'\0');   /*!Add termination null character for String Data. */
  #if defined(ESP8266) || defined(ESP32)
  EEPROM.commit();
  #endif
}
/*!
 * @fn          void erase_eeprom(int start_address, int end_address)
 * @brief       Nullify the EEPROM adresses with '\0'.
 * @param[in]   start_address Starting address of the EEPROM.
 * @param[in]   end_address  End address of the EEPROM.
 */
void erase_eeprom(int start_address, int end_address)
{
  for(int addr = start_address;addr<end_address;addr++)
  {
    EEPROM.write(addr,'\0');
  }
  #if defined(ESP8266) || defined(ESP32)
  EEPROM.commit();
  #endif
}
/*!
 * @fn      void deinit_eeprom(void)
 * @brief   Deinitialises the EEPROM.
 */
void deinit_eeprom(void)
{
  EEPROM.end();
}
