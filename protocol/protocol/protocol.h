#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "stdint.h"

#define CMD_HEART               0X00
#define CMD_SET_USER_ID         0X03
#define CMD_GET_TIME            0X05
#define CMD_GET_TOTAL_STEP      0X06
#define CMD_GET_BREAKDOWN       0X14
#define CMD_REBOOT              0X50
#define CMD_GET_USER_ID         0X57

#define CMD_TOOL_SCAN           0XA0
#define CMD_TOOL_CONNECT        0XA1
#define CMD_TOOL_CONN_STA       0XA2
#define CMD_BRIDGE_SET_TIME     0XA3
#define CMD_BRIDGE_GET_TIME     0XA4
#define CMD_BRIDGE_START        0XA5
#define CMD_BRIDGE_END          0XA6
#define CMD_BRIDGE_SYN          0XA7


#define CMD_MAX_NUMBER          0XAA


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


/** CMD_SET_USER_ID */
typedef struct
{
    uint32_t user_id; 
}pro_user_id_t;


/** CMD_TOOL_SCAN */

#define DEVICE_NAME_MAX_LEN           16

typedef struct
{
    uint8_t addr[6];
    int8_t  rssi;
    uint8_t name[DEVICE_NAME_MAX_LEN];
}pro_scan_response_t;

typedef struct
{
    uint8_t type;           //  0: stop  1: start
}pro_scan_require_t;

/** CMD_TOOL_CONNECT */

typedef struct
{
    uint8_t addr[6];
}pro_connect_info_t;


/** CMD_TOOL_CONN_STA */

typedef struct
{
    uint8_t status;
}pro_conn_sta_t;


/** CMD_GET_TOTAL_STEP */
typedef struct
{
    uint8_t  month;
    uint8_t  day;
}pro_total_step_require_t;


typedef struct
{
    uint8_t  month;
    uint8_t  day;
    uint32_t total_step;
}pro_total_step_response_t;


/** CMD_SET/GET_TIME */
typedef struct
{
    uint8_t  year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  hour;
    uint8_t  minute;
    uint8_t  second;
}pro_time_t;


typedef struct
{
    uint8_t  month;
    uint8_t  day;
}pro_syn_require_t;

/** CMD_SYN_WALK_DATA */
typedef struct
{
    uint8_t  month;
    uint8_t  day;
    uint32_t id;
    uint32_t step;
}pro_walk_info_t;


#pragma pack()

typedef struct
{
    protocol_info_t protocol_info;
}protocol_control_t;


typedef void (*pcmd_handler_t)(protocol_info_t);

#define PROTO_PARAM_PTR_CHECK(ptr)    do{if(ptr == NULL){ return; }}while(0)
#define STRUCT_OFF(type, n)     ((uint32_t)(&(((type *)0)->n)))


#define PROTO_REC_BUF_LEN     30            /**<  cmd + param ; this buffer save command and parameters that have been parsed */
#define PROTO_SEND_BUF_LEN    128           /**<  this buffer is used during packing data */

#ifndef RETVAL_TYPE

#define RETVAL_TYPE          int
#define RETVAL_SUCCESS       0
#define RETVAL_EXE_ERR       -1
#define RETVAL_PARAM_ERROR   -2

#endif

void protocol_init(void);
int protocol_send(protocol_struct_t protocol_struct, uint8_t *param, uint32_t param_len);
int protocol_regist_command(uint8_t cmd, pcmd_handler_t phandler);
int protocol_unregist_command(uint8_t cmd);

#endif


