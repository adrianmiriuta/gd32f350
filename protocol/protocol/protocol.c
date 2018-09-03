#include "protocol.h"
#include "./b_tp_stream/b_tp/inc/b_tp.h"


static protocol_control_t sg_protocol_control;        /**< global variable for protocol module  */
static uint8_t sg_cnumber = 0; 
static pcmd_handler_t handler_table[CMD_MAX_NUMBER];


/**
 * @defgroup FOR_TP_MODULE 
 * @{
 */
b_tp_err_code_t _b_tp_rec_check_head(b_tp_head_t *phead)
{
    sg_cnumber = phead->number;
    return B_TP_SUCCESS;
}

void _b_tp_send_set_head(b_tp_head_t *phead)
{
    phead->number = sg_cnumber;
}

/**
 * @}
 */

static void _protocol_dispatch(protocol_info_t protocol_info)
{
    protocol_struct_t protocol_struct = 
    {
        .status = CMD_STATUS_SUCCESS,
    };    
    heart_beat_clear();
    if(protocol_info.cmd < CMD_MAX_NUMBER)
    {
        if(handler_table[protocol_info.cmd] != NULL)
        {
            handler_table[protocol_info.cmd](protocol_info);
            return;
        }
    }
    protocol_struct.cmd = protocol_info.cmd;
    protocol_struct.status = CMD_STATUS_UNKNOWN;
    protocol_send(protocol_struct, NULL, 0);    
}



void b_tp_callback_f(b_TPU8 *pbuf, b_TPU32 len)
{
    uint32_t off = STRUCT_OFF(protocol_info_t, param);
    PROTO_PARAM_PTR_CHECK(pbuf);
    if(len > (PROTO_REC_BUF_LEN + off))
    {
        return;
    }
    uint8_t i = 0;
    for(i = 0;i < len;i++)
    {
        b_log("%x ", pbuf[i]);
    }
    b_log("\n\r");
       
    sg_protocol_control.protocol_info.cmd = pbuf[0];
    sg_protocol_control.protocol_info.status = pbuf[1];
    if((len - off) > 0)
    {
        sg_protocol_control.protocol_info.param = pbuf + off;
    }
    else
    {
        sg_protocol_control.protocol_info.param = NULL;
    }
    _protocol_dispatch(sg_protocol_control.protocol_info);
}





void protocol_init()
{
    b_tp_reg_callback(b_tp_callback_f);
    
    memset(&sg_protocol_control, 0, sizeof(protocol_control_t));
    memset(handler_table, 0, sizeof(handler_table));
    
}


/**
 * @brief the interface that sending data to APP or wechat
 */
int protocol_send(protocol_struct_t protocol_struct, uint8_t *param, uint32_t param_len)
{
    uint8_t proto_send_buf[PROTO_SEND_BUF_LEN];
    protocol_struct_t *p = NULL;
    b_tp_err_code_t err_code = B_TP_SUCCESS;
    if(param == NULL && param_len != 0)
    {
        return RETVAL_PARAM_ERROR;
    }

    p = (protocol_struct_t *)proto_send_buf;
    p->cmd = protocol_struct.cmd;
    p->status = protocol_struct.status;
    memcpy(p->param, param, param_len);

    uint8_t i = 0;
    for(i = 0;i < param_len + sizeof(protocol_struct_t) - 1;i++)
    {
        b_log("%x ", ((uint8_t *)p)[i]);
    }
    b_log("\n\r");
    
    err_code = b_tp_send_data((uint8_t *)p, param_len + sizeof(protocol_struct_t) - 1);
    if(err_code != B_TP_SUCCESS)
    {
        return RETVAL_EXE_ERR;
    }
    return RETVAL_SUCCESS;
}


int protocol_regist_command(uint8_t cmd, pcmd_handler_t phandler)
{
    if(cmd >= CMD_MAX_NUMBER || phandler == NULL)
    {
        return RETVAL_PARAM_ERROR;
    }
    handler_table[cmd] = phandler;
    return RETVAL_SUCCESS;
}

int protocol_unregist_command(uint8_t cmd)
{
    if(cmd >= CMD_MAX_NUMBER)
    {
        return RETVAL_PARAM_ERROR;
    }
    handler_table[cmd] = NULL;
    return RETVAL_SUCCESS; 
}








