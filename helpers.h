/* 
 * File:   helpers.h
 * Author: Thomas
 *
 * Created on October 14, 2017, 3:47 AM
 */

#ifndef HELPERS_H
#define	HELPERS_H

#ifdef	__cplusplus
extern "C" {
#endif

void startup();
void updateStatus();
void getData(uint8_t length, char* buffer);
void sendResponse(bool type, uint8_t length, char *buffer);
int getCommands();
bool testTolerance(float tol,float tgt,float act);
void updateOutputs();

#ifdef	__cplusplus
}
#endif

#endif	/* HELPERS_H */

