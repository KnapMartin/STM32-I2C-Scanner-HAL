#ifndef SCANNER_H
#define SCANNER_H

#include "main.h"
#include <stdio.h>

void I2C_Scanner(I2C_HandleTypeDef *hi2c)
{
    char buffer[64];
    uint8_t i2c_address;
    HAL_StatusTypeDef result;
    int devices_found = 0;

    printf("I2C Scanner Initialized\r\n");
    printf("Scanning for I2C devices...\r\n");

    for (i2c_address = 0x03; i2c_address <= 0x77; i2c_address++) {
        // Send a test command to the current address
        result = HAL_I2C_IsDeviceReady(hi2c, (i2c_address << 1), 1, 10);

        if (result == HAL_OK) {
            // Device responded
            snprintf(buffer, sizeof(buffer), "Device found at 0x%02X\r\n", i2c_address);
            printf(buffer);
            devices_found++;
        }
    }

    if (devices_found == 0) {
        printf("No I2C devices found.\r\n");
    } else {
        snprintf(buffer, sizeof(buffer), "Scan complete. %d devices found.\r\n", devices_found);
        printf(buffer);
    }
}

#endif

