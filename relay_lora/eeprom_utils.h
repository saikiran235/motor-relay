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
 *  @file      eeprom_utils.h
 *  @brief     EEPROM related operations
 *  @details   Saving and reading data to EEPROM.
 *  @author    Delta Things.
 *  @version   1.0
 *  @date      15 March 2019
 *  @pre       First initialize the system.
 *  @bug       Not detected any.
 *  @copyright (c) DELTA THINGS Pvt Ltd.
 */
#ifndef _EEPROM_UTILS_H_
#define _EEPROM_UTILS_H_

/*!
 * @var   step_size
 * @brief step size for wifi network base address.  
 */
const int step_size = 40;

/*!
 * @enum  eeprom_addresses
 * @brief Base addresses of the EEPROM used for various purpose.
 */
enum eeprom_addrress
{
  device_id_addr          = 1 /*!< Device id saved at this address. */
};

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
bool init_eeprom();
#elif defined(ESP32)
bool init_eeprom(int size);
#elif defined(ESP8266)
void init_eeprom(int size);
#endif
/** 
 *  function declarations 
 */
String  read_from_eeprom  (int addr);       /// function String  read_from_eeprom  (int addr);
void    save_to_eeprom    (int addr,String data); ///void    save_to_eeprom    (int addr,String data);
void    deinit_eeprom     (void);           ///void    deinit_eeprom     (void);
void    erase_eeprom      (int start_address, int end_address); ///void    erase_eeprom      (int start_address, int end_address);
#endif/*_EEPROM_UTILS_H_ */

/** End of File Copyright ******************************************
 *
 * Copyright (c) DELTA THINGS Pvt Ltd as an unpublished work
 * THIS SOFTWARE AND/OR MATERIAL IS THE PROPERTY OF
 * DELTA THINGS Pvt Ltd.  ALL USE, DISCLOSURE, AND/OR
 * REPRODUCTION NOT SPECIFICALLY AUTHORIZED BY
 * DELTA THINGS Pvt Ltd IS PROHIBITED.
 *
 *******************************************************************/
