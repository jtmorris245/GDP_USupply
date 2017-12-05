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
    bool testTolerance(float tol, float tgt, float act);
    void updateOutputs();

    struct statuss {
        float setV;
        float setI;
        float measV;
        float measI;
        float measBatt;
        float convsp;
        bool curlim;
        bool enconv;
    }; // 26 Bytes

    struct states {
        bool pwrdn;
        bool connected;
        bool startup;
        bool lowBatt;
        bool updateThisLoop;
        int loopCount;
    }; //9 bytes

    struct states state;
    struct statuss status;

#ifdef	__cplusplus
}
#endif

#endif	/* HELPERS_H */

