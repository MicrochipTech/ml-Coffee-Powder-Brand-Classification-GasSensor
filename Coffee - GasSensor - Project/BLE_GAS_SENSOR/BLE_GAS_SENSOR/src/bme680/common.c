/**
 * Copyright (C) 2023 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./bme680/bme68x.h"
//#include "coines.h"
#include "./bme680/common.h"
#include "sensor.h"
// *****************************************************************************
// *****************************************************************************
// Section: Platform specific includes
// *****************************************************************************
// *****************************************************************************
#include "definitions.h"
#include "app_config.h"

/******************************************************************************/
/*!                 Macro definitions                                         */
/*! BME68X shuttle board ID */
#define BME68X_SHUTTLE_ID  0x93
#define SNSR_COM_BUF_SIZE  128

/******************************************************************************/
/*!                Static variable definition                                 */
static uint8_t dev_addr;

/******************************************************************************/
/*!                User interface functions                                   */

/*!
 * I2C read function map to COINES platform
 */
//bool SERCOM2_I2C_Read(uint16_t address, uint8_t* rdData, uint32_t rdLength);
//
//bool SERCOM2_I2C_Write(uint16_t address, uint8_t* wrData, uint32_t wrLength);
//
//bool SERCOM2_I2C_WriteRead(uint16_t address, uint8_t* wrData, uint32_t wrLength, uint8_t* rdData, uint32_t rdLength);

BME68X_INTF_RET_TYPE bme68x_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    uint8_t device_addr = *(uint8_t*)intf_ptr;

    (void)intf_ptr;
//    GPIO_RA10_Set();
//    GPIO_RA10_OutputEnable();
    
    if(SERCOM2_I2C_WriteRead((uint16_t) device_addr, &reg_addr, 1, reg_data, (uint32_t) len)) {
        while(SERCOM2_I2C_IsBusy()){}
//        GPIO_RA10_Clear();
        return 0;
    }
    else {
//        GPIO_RA10_Clear();
        return -2;       
    }
//    GPIO_RA10_Clear();
    return -3;
    //return coines_read_i2c(COINES_I2C_BUS_0, device_addr, reg_addr, reg_data, (uint16_t)len);
}

/*!
 * I2C write function map to COINES platform
 */
BME68X_INTF_RET_TYPE bme68x_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    uint8_t device_addr = *(uint8_t*)intf_ptr;
    static uint8_t buff [SNSR_COM_BUF_SIZE];
//    GPIO_RA10_Set();
//    GPIO_RA10_OutputEnable();
    
    if ((len + 1) > SNSR_COM_BUF_SIZE)
        return UINT8_C(-2);
  
    buff[0] = reg_addr;
    memcpy(&buff[1], reg_data, len);
    (void)intf_ptr;
    
    if (SERCOM2_I2C_Write((uint16_t) device_addr, buff, (uint32_t) len + 1)) {
        while(SERCOM2_I2C_IsBusy());
//        GPIO_RA10_Clear();
        return 0;
        } else {
//        GPIO_RA10_Clear();
        return -2; 
        }
//    GPIO_RA10_Clear();
    return -3;

    //return coines_write_i2c(COINES_I2C_BUS_0, device_addr, reg_addr, (uint8_t *)reg_data, (uint16_t)len);
}

//static int8_t bme688_i2c_write (uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len) {
//    static uint8_t buff [SNSR_COM_BUF_SIZE];
//    
//    if ((len + 1) > SNSR_COM_BUF_SIZE)
//        return UINT8_C(-2);
//    
//    buff[0] = reg_addr;
//    memcpy(&buff[1], data, len);
//    
//    if (SERCOM0_I2C_Write((uint16_t) dev_addr, buff, (uint32_t) len + 1)) {
//        while(SERCOM0_I2C_IsBusy());
//        return UINT8_C(0);
//    } else {
//        return UINT8_C(-2); 
//    }
//}

/*!
 * SPI read function map to COINES platform
 */
BME68X_INTF_RET_TYPE bme68x_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    //uint8_t device_addr = *(uint8_t*)intf_ptr;

    (void)intf_ptr;

    return 0;//coines_read_spi(COINES_SPI_BUS_0, device_addr, reg_addr, reg_data, (uint16_t)len);
}

/*!
 * SPI write function map to COINES platform
 */
BME68X_INTF_RET_TYPE bme68x_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    //uint8_t device_addr = *(uint8_t*)intf_ptr;

    (void)intf_ptr;

    return 0;//coines_write_spi(COINES_SPI_BUS_0, device_addr, reg_addr, (uint8_t *)reg_data, (uint16_t)len);
}

/*!
 * Delay function map to COINES platform
 */
void bme68x_delay_us(uint32_t period, void *intf_ptr)
{
    (void)intf_ptr;
    vTaskDelay(period);
//    sleep_us(period);
    //coines_delay_usec(period);
}

void bme68x_check_rslt(const char api_name[], int8_t rslt)
{
    switch (rslt)
    {
        case BME68X_OK:

            /* Do nothing */
            break;
        case BME68X_E_NULL_PTR:
            printf("API name [%s]  Error [%d] : Null pointer\r\n", api_name, rslt);
            break;
        case BME68X_E_COM_FAIL:
            printf("API name [%s]  Error [%d] : Communication failure\r\n", api_name, rslt);
            break;
        case BME68X_E_INVALID_LENGTH:
            printf("API name [%s]  Error [%d] : Incorrect length parameter\r\n", api_name, rslt);
            break;
        case BME68X_E_DEV_NOT_FOUND:
            printf("API name [%s]  Error [%d] : Device not found\r\n", api_name, rslt);
            break;
        case BME68X_E_SELF_TEST:
            printf("API name [%s]  Error [%d] : Self test error\r\n", api_name, rslt);
            break;
        case BME68X_W_NO_NEW_DATA:
            printf("API name [%s]  Warning [%d] : No new data found\r\n", api_name, rslt);
            break;
        default:
            printf("API name [%s]  Error [%d] : Unknown error code\r\n", api_name, rslt);
            break;
    }
}

int8_t bme68x_interface_init(struct bme68x_dev *bme, uint8_t intf)
{
    int8_t rslt = BME68X_OK;
    //struct coines_board_info board_info;

    if (bme != NULL)
    {
//        int16_t result = coines_open_comm_intf(COINES_COMM_INTF_USB, NULL);
//        if (result < COINES_SUCCESS)
//        {
//            printf(
//                "\n Unable to connect with Application Board ! \n" " 1. Check if the board is connected and powered on. \n" " 2. Check if Application Board USB driver is installed. \n"
//                " 3. Check if board is in use by another application. (Insufficient permissions to access USB) \n");
//            exit(result);
//        }
//
//        result = coines_get_board_info(&board_info);

//#if defined(PC)
//        setbuf(stdout, NULL);
//#endif

//        if (result == COINES_SUCCESS)
//        {
//            if ((board_info.shuttle_id != BME68X_SHUTTLE_ID))
//            {
//                printf(
//                    "! Warning invalid sensor shuttle : 0x%x (Expected : 0x%x) \n ," "This application will not support this sensor \n",
//                    board_info.shuttle_id,
//                    BME68X_SHUTTLE_ID);
//            }
//        }
//
//        (void)coines_set_shuttleboard_vdd_vddio_config(0, 0);
//        coines_delay_msec(100);

        /* Bus configuration : I2C */
        if (intf == BME68X_I2C_INTF)
        {
//            printf("I2C Interface\n");
            dev_addr = BME68X_I2C_ADDR_LOW;
            bme->read = bme68x_i2c_read;
            bme->write = bme68x_i2c_write;
            bme->intf = BME68X_I2C_INTF;

            /* SDO pin is made low it is low by default*/
            //(void)coines_set_pin_config(COINES_SHUTTLE_PIN_SDO, COINES_PIN_DIRECTION_OUT, COINES_PIN_VALUE_LOW);

            //(void)coines_config_i2c_bus(COINES_I2C_BUS_0, COINES_I2C_STANDARD_MODE);
        }
        /* Bus configuration : SPI */
        else if (intf == BME68X_SPI_INTF)
        {
            //printf("SPI Interface\n");
            //dev_addr = COINES_SHUTTLE_PIN_7;
            //bme->read = bme68x_spi_read;
            //bme->write = bme68x_spi_write;
            //bme->intf = BME68X_SPI_INTF;
            //(void)coines_config_spi_bus(COINES_SPI_BUS_0, COINES_SPI_SPEED_7_5_MHZ, COINES_SPI_MODE0);
        }

        // 100 ms delay I2C
        //coines_delay_msec(100);

        //(void)coines_set_shuttleboard_vdd_vddio_config(3300, 3300);

        //coines_delay_msec(100);

        bme->delay_us = bme68x_delay_us;
        bme->intf_ptr = &dev_addr;
        bme->amb_temp = 25; /* The ambient temperature in deg C is used for defining the heater temperature */
    }
    else
    {
        rslt = BME68X_E_NULL_PTR;
    }

    return rslt;
}

void bme68x_coines_deinit(void)
{
    (void)fflush(stdout);

    //(void)coines_set_shuttleboard_vdd_vddio_config(0, 0);
    //coines_delay_msec(1000);

    /* Coines interface reset */
    //coines_soft_reset();
    //coines_delay_msec(1000);
    //`(void)coines_close_comm_intf(COINES_COMM_INTF_USB, NULL);
}
