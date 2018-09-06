#include "protocol_handle.h"
#include "./uart/uart.h"
#include "string.h"
#ifndef NULL
#define NULL    ((void *)0)
#endif


#define RECORD_MAX_NUMBER   10


uint8_t pair_name[7] = "oduns2";

static uint8_t mac_record[RECORD_MAX_NUMBER][6];
static uint8_t mac_rcd_number = 0;
static self_status_t s_status = S_NULL;

static int no_repeat(uint8_t *pmac)
{
    uint8_t i, j;
    if(mac_rcd_number == 0)
    {
        return 0;
    }
    if(pmac != NULL)
    {
        for(i = 0;i < mac_rcd_number;i++)
        {
            for(j = 0;j < 6;j++)
            {
                if(pmac[j] != mac_record[i][j])
                {
                    break;
                }
            }
            if(j >= 6)
            {
                return -1;
            }
        }
        return 0;
    }
    return -1;
}


static int pro_pair_name(uint8_t *pname)
{
    uint32_t len = 0, i = 0;
    if(pname == NULL)
    {
        return -1;
    }
    len = strlen((char *)pname);
    if(len < strlen((char *)pair_name))
    {
        return -1;
    }
    for(i = 0;i < strlen((char *)pair_name);i++)
    {
        if(pname[i] == pair_name[i] || pname[i] == ('A' + (pair_name[i] - 'a')))
        {
            ;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}


static void pro_start_scan()
{
    protocol_struct_t  pro_struct = PROTOCOL_STRUCT_DEFAULT(CMD_TOOL_SCAN);
    pro_scan_require_t pro_scan_require;
    pro_scan_require.type = 1;
    protocol_send(pro_struct, (uint8_t *)&pro_scan_require, sizeof(pro_scan_require_t));
}

static void pro_stop_scan()
{
    protocol_struct_t  pro_struct = PROTOCOL_STRUCT_DEFAULT(CMD_TOOL_SCAN);
    pro_scan_require_t pro_scan_require;
    pro_scan_require.type = 0;
    protocol_send(pro_struct, (uint8_t *)&pro_scan_require, sizeof(pro_scan_require_t));
}



static void pro_get_useid_handler(protocol_info_t info)
{
    ;
}

static void pro_tool_scan_handler(protocol_info_t info)
{
    pro_scan_response_t *pinfo = (pro_scan_response_t *)info.param;
    if(0 != pro_pair_name(pinfo->name))
    {
        return;
    }
    if(0 == no_repeat(pinfo->addr))
    {
        if(mac_rcd_number >= RECORD_MAX_NUMBER)
        {
            mac_rcd_number = 0;
        }
        memcpy(mac_record[mac_rcd_number], pinfo->addr, 6);
        mac_rcd_number++;
        pro_stop_scan();
        s_status = S_VALID_DEVICE;
    }
}

static void pro_tool_conn_handler(protocol_info_t info)
{
    ;
}

static void pro_tool_conn_sta_handler(protocol_info_t info)
{
    pro_conn_sta_t *ptmp = (pro_conn_sta_t *)info.param;
    if(ptmp != NULL)
    {
        uart1_write_ch(ptmp->status);
        if(ptmp->status == 2)
        {
            s_status = S_WR_ING;
        }
        else if(ptmp->status == 0 && s_status > S_SCAN)
        {
            s_status = S_NULL;
        }
    }
}



/** ---------------------------------------------  */

void pro_init()
{
    protocol_init();
    protocol_regist_command(CMD_GET_USER_ID, pro_get_useid_handler);
    protocol_regist_command(CMD_TOOL_SCAN, pro_tool_scan_handler);
    protocol_regist_command(CMD_TOOL_CONNECT, pro_tool_conn_handler);
    protocol_regist_command(CMD_TOOL_CONN_STA, pro_tool_conn_sta_handler);
}


void pro_connect_dev(uint8_t *pmac)
{
    if(pmac == NULL)
    {
        return;
    }
    protocol_struct_t  pro_struct = PROTOCOL_STRUCT_DEFAULT(CMD_TOOL_CONNECT);
    pro_connect_info_t pro_connect_info;
    memcpy(pro_connect_info.addr, pmac, 6);
    protocol_send(pro_struct, (uint8_t *)&pro_connect_info, sizeof(pro_connect_info_t));
}


void pro_send_hb()
{
    if(s_status == S_WR_ING)
    {
        protocol_struct_t  pro_struct = PROTOCOL_STRUCT_DEFAULT(CMD_HEART);
        protocol_send(pro_struct, NULL, 0);
    }
}





void pro_main()
{
    switch(s_status)
    {
        case S_NULL:
            pro_start_scan();
            s_status = S_SCAN;
            break;
        case S_VALID_DEVICE:
            pro_connect_dev(mac_record[mac_rcd_number - 1]);
            s_status = S_CONN_ING;
            break;
        case S_WR_ING:
            
            break;
        default: break;
    }
}


