/*
 Encapsulates commands for each I2C device as required.
 
 */

#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "i2cdriver.h"
/// bool initDevices()
/// Returns false if I2C devices are initialised successfully, true otherwise.
/// Performs initial setup items required for each device on the bus.
bool initDevices()
{
    // Send General Command Reset, Then General command Wakeup
    int GCReset = 0x06;
    I2C1_MESSAGE_STATUS resp;
    I2C1_MasterWrite(&GCReset,1,0,resp);
    if(resp != I2C1_MESSAGE_COMPLETE) return 1;
    int GCWake = 0x09;
    I2C1_MasterWrite(&GCWake,1,0,resp);
    if(resp != I2C1_MESSAGE_COMPLETE) return 1;
    
    // Now, Set the DAC to output 0
    int data[2]= {0,0};
    I2C1_MasterWrite(&data,2,DACADDR,resp);
    if(resp != I2C1_MESSAGE_COMPLETE) return 1;
    
    //Set EPOT to 0, equiv to 9V Set point - DCDC should be off anyway.
    
    int data[2]= {0,0};
    I2C1_MasterWrite(&data,1,EPOTADDR,resp);
    if(resp != I2C1_MESSAGE_COMPLETE) return 1;
    
    //Shunt doesn't require any setup for basic operation. For current/Power
    //will need to calculate / measure calibration values.
    unsigned short calibrationValue = calcShuntCalVal(2.0f,1.0f);
    int data[2] = {0x05,0}; // Calibration register addr
    I2C1_MasterWrite(&data,1,SHUNTADDR,resp);
    if(resp != I2C1_MESSAGE_COMPLETE ) return 1;
    //Split it into 2 bytes to send
    data[0] = calibrationValue & 0xff;
    data[1] = (calibrationValue >> 8) & 0xff;
    // Send 2 bytes to the addr already set.
    I2C1_MasterWrite(&data,2,SHUNTADDR,resp);
    if(resp != I2C1_MESSAGE_COMPLETE ) return 1;
    // Nothing failed, so report success.
    return false;
    
}
///bool getBusVoltage(float* voltage)
///Gets bus voltage from shunt measurement device.
///Returns false if completed, true in event of an error.
bool getBusVoltage(float *voltage)
{
    I2C1_MESSAGE_STATUS resp;
    int data[1] = {0x02};
    // write to address register
    I2C1_MasterWrite(&data,1,SHUNTADDR,resp);
    if(resp != I2C1_MESSAGE_COMPLETE ) return 1;
    //read from this register
    char datares[2] = {0,0};
    I2C1_MasterRead(datares,2,SHUNTADDR,resp);
    if(resp != I2C1_MESSAGE_COMPLETE ) return 1;
    //extract required data from bytes... RSH 3 for unused bytes.
    // Format:
    // BD12 - BD11 ... BD0 - NONE - CNVR - OVF
    short recon = ((((short)datares[0]) << 8) | datares[1])>>3;
    //LSB = 4mv
    *voltage = recon * 0.004f;
    return false;
}
///unsigned short calcShuntCalVal(float maxCurrent, float RShunt)
///Calculates the calibration register value required.
///Returns an unsigned short to be sent to the cal register.
unsigned short calcShuntCalVal(float maxCurrent, float RShunt)
{
    float intval = 0.04096 ;
    float currentLSB = maxCurrent / 32768;
    float calval = intval/(currentLSB*RShunt);
    return (unsigned short)calval;
}

