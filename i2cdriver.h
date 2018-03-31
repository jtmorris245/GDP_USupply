/* 
 * File:   i2cdriver.h
 * Author: jtm
 *
 * Created on 20 February 2018, 13:24
 */

#ifndef I2CDRIVER_H
#define	I2CDRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

    /// I2C Device Addresses
#define EPOTADDR    0x2F
#define SHUNTADDR   0x40
#define DACADDR     0x62

    bool initDevices();
    bool getBusVoltage(float *voltage);
    unsigned short calcShuntCalVal(float maxCurrent, float RShunt);

#ifdef	__cplusplus
}
#endif

#endif	/* I2CDRIVER_H */

