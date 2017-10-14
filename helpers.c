#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct statuss {
    float setV;
    float setI;
    float measV;
    float measI;
    float measBatt;
    float convsp;
    bool curlim;
    bool enconv;    
};

struct states {
    bool pwrdn;
    bool connected;
    bool startup;
    bool lowBatt;
    bool updateThisLoop;
    int loopCount;
};

struct states state;
struct statuss status;


void startup()
{
    state.pwrdn = true;
    state.connected = false;
    state.startup = true;
    state.lowBatt = false;
    
    status.setV=0;
    status.setI=0;
    status.convsp=0;
    status.enconv=false;
    status.curlim=false;
    status.measV = 0;
    status.measBatt = 0;
    status.measI = 0;
}

bool ignErr;



/*
 * Auto Updates Status Struct with latest measurements.
 */
void updateStatus()
{
    //get measurements
}

#define NEW_LINE 0x0D
typedef union float_char_union {
    float fl;
    char ch[4];
};

void getData(uint8_t length, char* buffer)
{
    // Reconstruct buffer array from pointer
    memset(buffer,0,length * sizeof(*buffer));
    for(uint8_t i = sizeof(buffer); i != 0; i--)
    {
	buffer[sizeof(buffer)-i] = EUSART_Read();
    }
}
/* Function void sendResponse(type,length,*buffer)
 * Description:
 * If type == true,
 * Send given buffer over EUSART
 * Or
 * Send Newline over EUSART as an ack.
 */
void sendResponse(bool type, uint8_t length, char *buffer)
{
    // type = 1 -> Response req.
    if(type)
    {
        // Reconstruct buffer array from pointer
        memset(buffer,0,length * sizeof(*buffer));
	// Iterate on buffer and send byte by byte
        for(uint8_t i = sizeof(buffer);i!=0;i--)
        {
            EUSART_Write(buffer[sizeof(buffer)-i]);
        }
        EUSART_Write(NEW_LINE);
    }
    else
    {
	EUSART_Write(NEW_LINE);
    }
    
}

/* Command Set                      Returns
     * 0x01 +4B Set Voltage             0
     * 0x02 +4B Set Current             0
     * 0x03     Get Voltage SP          4B float
     * 0x04     Get Current SP          4B float
     * 0x05     Return State Struct     TBD
     * 0x06     Get Measured Voltage    4B float
     * 0x07     Get Measured Current    4B float
     * 0x08     Get Battery Voltage     4B float
     * All responses followed by new line
     */
int getCommands()
{
    if(!EUSART_DataReady) return 0x00;
    //Serial input
    char input;
    getData(1,&input);
    float value;
    value = 1.5;
    union float_char_union fcu;
    switch (input)
    {
            case 0x01:
		sendResponse(0,0,0);
                break;
            case 0x02:
		sendResponse(0,0,0);
                break;
            case 0x03:
	    {
		//get the voltage
		fcu.fl = value;
		sendResponse(1,4,fcu.ch);
                break;
	    }
            case 0x04:
	    {
		//get the voltage
		fcu.fl = value;
		sendResponse(1,4,fcu.ch);
                break;
	    }
            case 0x05:
	    {
		//get the voltage
		fcu.fl = value;
		sendResponse(1,4,fcu.ch);
                break;
	    }
            case 0x06:
	    {
		//get the voltage
		fcu.fl = value;
		sendResponse(1,4,fcu.ch);
                break;
	    }
            case 0x07:
	    {
		//get the voltage
		fcu.fl = value;
		sendResponse(1,4,fcu.ch);
                break;
	    }
	    case 0x08:
	    {
		//get the voltage
		fcu.fl = value;
		sendResponse(1,4,fcu.ch);
                break;
	    }
            default:
                break;
    }           
    return 0;
}

/*
 * bool testTolerance(float tol,float tgt,float act);
 * 
 * tol	->  Tolerance, +-
 * 
 * tgt	->  Target value
 * 
 * act	->  Actual Value
 * 
 * Returns true if test passes
 */ 
bool testTolerance(float tol, float tgt, float act)
{
    return (act >= tgt-tol) && (act <= tgt+tol) ;
}

void updateOutputs()
{
    //@TODO
}



