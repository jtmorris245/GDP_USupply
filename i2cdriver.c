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
/// Returns True if I2C devices are initialised successfully, False otherwise.
/// Performs initial setup items required for each device on the bus.
bool initDevices()
{
    // Send General Command Reset, Then General command Wakeup
    int GCReset = 0x06;
    int resp =0;
    I2C1_MasterWrite(&GCReset,1,0,&resp);
    if(resp != I2C1_MESSAGE_COMPLETE) return 1;
    int GCWake = 0x09;
    I2C1_MasterWrite(&GCWake,1,0,&resp);
    if(resp != I2C1_MESSAGE_COMPLETE) return 1;
    
    // Now, Set the DAC to output 0
    int data[2] = [0,0];
    I2C1_MasterWrite(&data,2,DACADDR,&resp);
    if(resp != I2C1_MESSAGE_COMPLETE) return 1;
    
    //@TODO Init the EPOT and shunt measurement.
    
    return true;
    
}


