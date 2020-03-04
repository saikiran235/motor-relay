/*!
    @file      device_config.h
    @brief     This file defines the configuration related to device.
    @details   Details.
    @author    Delta Things
    @version   1.0
    @date      12 April 2018
    @pre       First initialize the system.
    @bug       Not detected any.
    @warning   1. Please include this library in all project source files
    @copyright (c) DELTA THINGS Pvt Ltd.
*/
#ifndef _DEVICE_CONFIG_H_
#define _DEVICE_CONFIG_H_

#include <Arduino.h>
#include <EEPROM.h>

#include "json.h"
#include "eeprom_utils.h"
#include "lora.h"

/*!
 * @def     SERIAL_DEBUG
 * @brief   Set the Default serial port for debugging.
 */
#define SERIAL_DEBUG        true

///*!
// * @def       SW_VERSION
// * @brief     Software version of the project.
// */
//#define SW_VERSION            String("1.0.0")
///*!
// * @def     SW_TEST
// * @brief  Set the SW_TEST macro to true for using testing functions
// */
//#define SW_TEST             true
//
///*!
// * @def     R1
// * @brief   R1 value set to 10 kilo ohms
// */
//#define R1 100000   // 100 Kilo Ohms
///*!
// * @def     R2 
// * @brief   Set R2 to 10 kilo Ohms.
// */
//#define R2 10000    //10 Kilo Ohms

/*!
 * @def     ON_BUTTON_PIN 
 * @brief   ON button pin.
 */
#define ON_BUTTON_PIN 21//3

/*!
 * @def     OFF_BUTTON_PIN 
 * @brief   OFF button pin.
 */
#define LoRa_LED 4

#define OFF_BUTTON_PIN 22
#define Status_LED 25
/*!
 * @struct      device_info
 * @brief       Device specific info.
 */
struct device_info
{
  String device_id;      /*!< Unique device ID. */ 
};
/*! @enum status  
*   @brief Status of sender device and gateway device
*/
enum status
{
  UNDEFINED = -1,         /*!<Receiver side*/
  LoRa_RX_OK = 0,         /*!<Sender side*/
  GATEWAY_RESET = 1,      /*!<Receiver side*/
  LoRa_RX_TIMEOUT = 3,    /*!<Receiver side*/ 
};

enum button
{
  _UNDEFINED = -1,
  ON_BUTTON_PRESSED = 1,
  OFF_BUTTON_PRESSED = 2,
  ALIVE = 3,
};
#endif
