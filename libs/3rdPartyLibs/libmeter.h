#ifndef LIBMETER_H
#define LIBMETER_H

enum errorCodes
{
    NULL_VALUE_FROM_METER = -3,
    NOT_INITIALIZED,
    OBIS_CODE_NOT_SUPPORTED,
    SUCCESS
};

int initializeMeterComm(void);
int getValueFromMeter(char* output_buff, char* parameter);

#endif
