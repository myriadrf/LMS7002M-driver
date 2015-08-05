/**
 * This is the C adaptation from the lms7api.
@file	LMS7002M_statuses.h
@author Lime Microsystems (www.limemicro.com)
@brief 	LMS7002M control library statuses enumerations
*/

#ifndef LMS7API_STATUSES_H
#define LMS7API_STATUSES_H

static const char liblms7_status_strings[][64] =
{
"success",
"failure",
"index out of range",
"too many values",
"connection manager is NULL",
"not connected",
"frequency out of range",
"cannot deliver frequency"
};

typedef enum
{
    LIBLMS7_SUCCESS = 0,
    LIBLMS7_FAILURE,
    LIBLMS7_INDEX_OUT_OF_RANGE,
    LIBLMS7_TOO_MANY_VALUES,
    LIBLMS7_NO_CONNECTION_MANAGER,
    LIBLMS7_NOT_CONNECTED,
    LIBLMS7_FREQUENCY_OUT_OF_RANGE,    
    LIBLMS7_CANNOT_DELIVER_FREQUENCY,
} liblms7_status;

#endif
