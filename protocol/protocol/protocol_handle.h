#ifndef __PROTOCOL_HANDLE_H__
#define __PROTOCOL_HANDLE_H__

#include "protocol.h"

#define PROTOCOL_STRUCT_DEFAULT(c)        \
{                                         \
    .cmd = c,                             \
    .status = CMD_STATUS_SUCCESS,         \
}


typedef enum
{
    S_NULL,
    S_SCAN,
    S_VALID_DEVICE,
    S_CONN_ING,
    S_WR_ING,
    S_BRIDGE_M,
}self_status_t;

void pro_init(void);
void pro_send_hb(void);
void pro_main(void);

#endif



