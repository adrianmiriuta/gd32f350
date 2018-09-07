#ifndef __PROTOCOL_HANDLE_H__
#define __PROTOCOL_HANDLE_H__

#include "protocol.h"

#define PROTOCOL_STRUCT_DEFAULT(c)        \
{                                         \
    .cmd = c,                             \
    .status = CMD_STATUS_SUCCESS,         \
}


#define SAVE_MAX_DAY        10
#define KV_START_ADDRESS    0X1000

typedef enum
{
    S_NULL,
    S_SCAN,
    S_VALID_DEVICE,
    S_CONN_ING,
    S_WR_ING,
    S_GET_ID,
    S_GET_STEP,
    S_WAIT_DISCONN,
    S_BRIDGE_M,
}self_status_t;




#pragma pack(1)


typedef struct
{
    uint8_t month;
    uint8_t day;
    uint32_t id;
    uint32_t step;
}pro_value_struct_t;

typedef struct
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
}pro_date_info_t;

#pragma pack()








int pro_clear_mac_rcd(void);
void pro_init(void);
void pro_send_hb(void);
void pro_main(void);

#endif



