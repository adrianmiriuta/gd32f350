#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "stdint.h"

#define CMD_HEART               0X00
#define CMD_SET_USER_ID         0X03
#define CMD_GET_TIME            0X05
#define CMD_GET_TOTAL_STEP      0X06
#define CMD_GET_BREAKDOWN       0X14

#define CMD_GET_USER_ID         0X57

#define CMD_MAX_NUMBER          0X58


#define CMD_STATUS_SUCCESS          0X0
#define CMD_STATUS_UNKNOWN          0X1
#define CMD_STATUS_ACK              0X2
#define CMD_STATUS_REPEAT           0X3
#define CMD_STATUS_LAST_ONE         0X4
#define CMD_STATUS_NO_DATA          0X5
#define CMD_STATUS_HW_ERROR         0X6
#define CMD_STATUS_PARAM_INVALID    0X7




#pragma pack(1)

typedef struct
{
    uint8_t cmd;
    uint8_t status;
    uint8_t *param;
}protocol_info_t;

typedef struct
{
    uint8_t cmd;
    uint8_t status;
    uint8_t param[1];
}protocol_struct_t;

#pragma pack()

typedef struct
{
    protocol_info_t protocol_info;
}protocol_control_t;


typedef void (*pcmd_handler_t)(protocol_info_t);


#define STRUCT_OFF(type, n)     ((uint32_t)(&(((type *)0)->n)))


#define PROTO_REC_BUF_LEN     30            /**<  cmd + param ; this buffer save command and parameters that have been parsed */
#define PROTO_SEND_BUF_LEN    128           /**<  this buffer is used during packing data */








#endif


