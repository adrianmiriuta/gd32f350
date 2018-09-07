#include "protocol_handle.h"
#include "./uart/uart.h"
#include "string.h"
#include "./calendar/calendar.h"
#include "./kv/b_kv/b_kv/inc/b_kv.h"
#include "./spiflash/flash_dev.h"
#include "./led/led.h"
#ifndef NULL
#define NULL    ((void *)0)
#endif


#define RECORD_MAX_NUMBER   10


uint8_t pair_name[7] = "oduns2";

static uint8_t mac_record[RECORD_MAX_NUMBER][6];
static uint8_t mac_rcd_number = 0;
volatile static self_status_t s_status = S_BRIDGE_M;
static uint8_t cmd_idle = 0;
static pro_value_struct_t pro_value_struct;

static pro_date_info_t kv_day_table[SAVE_MAX_DAY];
static uint32_t d_index = 0;
static void kv_next_day(void);
static self_status_t c_status = S_NULL;
static uint32_t timeout_s = 0;
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



static void pro_get_step()
{   
    cmd_idle++;
    pro_total_step_require_t pro_total_step_require;
    calendar_info_t calendar_info;
    calendar_get_date(&calendar_info);
    pro_total_step_require.month = calendar_info.month;
    pro_total_step_require.day = calendar_info.day;
    if(s_status >= S_WR_ING)
    {
        protocol_struct_t  pro_struct = PROTOCOL_STRUCT_DEFAULT(CMD_GET_TOTAL_STEP);
        protocol_send(pro_struct, (uint8_t *)&pro_total_step_require, sizeof(pro_total_step_require_t));
    } 
    cmd_idle--;    
}


static void pro_get_useid_handler(protocol_info_t info)
{
    if(s_status == S_BRIDGE_M)
    {
        return;
    }
    if(s_status == S_GET_ID)
    {
        if(info.param == NULL)
        {
            s_status = S_WR_ING;
            return;
        }
        pro_value_struct.id = ((pro_user_id_t *)(info.param))->user_id;
        pro_get_step();
        s_status = S_GET_STEP;
        timeout_s = 0;
        c_status = S_GET_STEP;
    }
}

static void pro_tool_scan_handler(protocol_info_t info)
{
    pro_scan_response_t *pinfo = (pro_scan_response_t *)info.param;
    if(s_status == S_BRIDGE_M)
    {
        return;
    }    
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
        s_status = S_VALID_DEVICE;
        pro_stop_scan();
    }
}

static void pro_tool_conn_handler(protocol_info_t info)
{
    ;
}

static void pro_tool_conn_sta_handler(protocol_info_t info)
{
    pro_conn_sta_t *ptmp = (pro_conn_sta_t *)info.param;
    if(s_status == S_BRIDGE_M)
    {
        return;
    }    
    if(ptmp != NULL)
    {
        if(ptmp->status == 2)
        {
            s_status = S_WR_ING;
            led2_control(1);
        }
        else if(ptmp->status == 0)
        {
            s_status = S_NULL;
            led2_control(0);
            led3_control(0);
        }
    }
}


static void pro_get_total_step_handler(protocol_info_t info)
{
    if(s_status == S_BRIDGE_M)
    {
        return;
    }    
    if(s_status == S_GET_STEP)
    {
        if(info.param == NULL)
        {
            s_status = S_WR_ING;
            return;
        }
        led3_control(1);
        pro_value_struct.step = ((pro_total_step_response_t *)(info.param))->total_step;
        pro_value_struct.month = ((pro_total_step_response_t *)(info.param))->month;
        pro_value_struct.day = ((pro_total_step_response_t *)(info.param))->day;
        if(pro_value_struct.day != kv_day_table[d_index].day)
        {
            kv_next_day();
        }
        b_kv_add_value((bKVU8 *)(&pro_value_struct.id), (bKVU8 *)(&pro_value_struct), sizeof(pro_value_struct_t));
        
        protocol_struct_t  pro_struct = PROTOCOL_STRUCT_DEFAULT(CMD_REBOOT);
        protocol_send(pro_struct, NULL, 0);
   
        s_status = S_WAIT_DISCONN;
        c_status = S_NULL;
    }
}


static void pro_connect_dev(uint8_t *pmac)
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



static void pro_get_userid()
{
    cmd_idle++;
    if(s_status >= S_WR_ING)
    {
        protocol_struct_t  pro_struct = PROTOCOL_STRUCT_DEFAULT(CMD_GET_USER_ID);
        protocol_send(pro_struct, NULL, 0);
    } 
    cmd_idle--;    
}


/** ---------------------------------------------  */


static void update_kv_dtable()
{
    uint8_t i = 0;
    pro_date_info_t pro_date_info = {0,0,0};
    flash_read_buf((uint8_t *)kv_day_table, 0x0, sizeof(kv_day_table));
    
    for(i = 0;i < SAVE_MAX_DAY;i++)
    {
        if(kv_day_table[i].month == 0xff && kv_day_table[i].day == 0xff && kv_day_table[i].year == 0xff)
        {
            continue;
        }
        else if(kv_day_table[i].day < 1 || kv_day_table[i].day > 31
            || kv_day_table[i].month < 1 || kv_day_table[i].month > 12)
        {
            memset(kv_day_table, 0xff, sizeof(kv_day_table));
            d_index = 0;
            break;
        }
        else
        {
            if(kv_day_table[i].year > pro_date_info.year)
            {
                pro_date_info.year = kv_day_table[i].year;
                pro_date_info.month = kv_day_table[i].month;
                pro_date_info.day = kv_day_table[i].day;
                d_index = i;
            }
            else if(kv_day_table[i].year == pro_date_info.year)
            {
                if(kv_day_table[i].month > pro_date_info.month)
                {
                    pro_date_info.year = kv_day_table[i].year;
                    pro_date_info.month = kv_day_table[i].month;
                    pro_date_info.day = kv_day_table[i].day;
                    d_index = i;
                }
                else if(kv_day_table[i].month == pro_date_info.month)
                {
                    if(kv_day_table[i].day >= pro_date_info.day)
                    {
                        pro_date_info.year = kv_day_table[i].year;
                        pro_date_info.month = kv_day_table[i].month;
                        pro_date_info.day = kv_day_table[i].day;
                        d_index = i;
                    }  
                }
            }
        }
    }
    calendar_info_t calendar_info;
    calendar_get_date(&calendar_info);    
    if(kv_day_table[d_index].month == 0xff)
    {
        kv_day_table[d_index].year = calendar_info.year;
        kv_day_table[d_index].month = calendar_info.month;
        kv_day_table[d_index].day = calendar_info.day;
    }
    else if(kv_day_table[d_index].day != calendar_info.day)
    {
        if((d_index + 1) >= SAVE_MAX_DAY)
        {
            d_index = 0; 
        }
        else
        {
            d_index = d_index + 1;
        }
        kv_day_table[d_index].year = calendar_info.year;
        kv_day_table[d_index].month = calendar_info.month;
        kv_day_table[d_index].day = calendar_info.day;
    }
    flash_erase_xsector(0, 1);
    flash_write_buf((uint8_t *)kv_day_table, 0x0, sizeof(kv_day_table));
}

static void kv_next_day()
{
    calendar_info_t calendar_info;
    calendar_get_date(&calendar_info); 
    if((d_index + 1) >= SAVE_MAX_DAY)
    {
        d_index = 0; 
    }
    else
    {
        d_index = d_index + 1;
    }
    kv_day_table[d_index].year = calendar_info.year;
    kv_day_table[d_index].month = calendar_info.month;
    kv_day_table[d_index].day = calendar_info.day;
    flash_erase_xsector(0, 1);
    flash_write_buf((uint8_t *)kv_day_table, 0x0, sizeof(kv_day_table));
    b_kv_init(KV_START_ADDRESS + d_index * B_KV_TOTAL_SIZE);
}


static void pro_b_set_time_handler(protocol_info_t info)
{
    pro_time_t *pro_time = (pro_time_t *)info.param;
    calendar_info_t calendar_info;
    if(pro_time == NULL)
    {
        return;
    }
    calendar_info.year = pro_time->year;
    calendar_info.month = pro_time->month;
    calendar_info.day = pro_time->day;
    calendar_info.hour = pro_time->hour;
    calendar_info.min = pro_time->minute;
    calendar_info.second = pro_time->second;
    calendar_init(calendar_info);
}

static void pro_b_get_time_handler(protocol_info_t info)
{
    pro_time_t pro_time;;
    calendar_info_t calendar_info;
    calendar_get_date(&calendar_info); 

    pro_time.year = calendar_info.year;
    pro_time.month = calendar_info.month;
    pro_time.day = calendar_info.day;
    pro_time.hour = calendar_info.hour;
    pro_time.minute = calendar_info.min;
    pro_time.second = calendar_info.second;
    
    protocol_struct_t  pro_struct = PROTOCOL_STRUCT_DEFAULT(CMD_BRIDGE_GET_TIME);
    protocol_send(pro_struct, (uint8_t *)&pro_time, sizeof(pro_time_t));
}

static void pro_bridge_end_handler(protocol_info_t info)
{
    s_status = S_NULL;
    v32_uartx = USART0;
}


static void pro_bridge_start_handler(protocol_info_t info)
{
    s_status = S_BRIDGE_M;
    v32_uartx = USART1;
}

static void pro_bridge_syn_handler(protocol_info_t info)
{
    uint32_t i = 0, number,j = 0, k = 0;
    uint32_t *pkvinfo;
    pro_syn_require_t *pro_syn_require = (pro_syn_require_t *)info.param;
    pro_walk_info_t pro_walk_info;
    if(pro_syn_require == NULL)
    {
        return;
    }
    for(i = 0;i < SAVE_MAX_DAY;i++)
    {
        if(kv_day_table[i].month == pro_syn_require->month && kv_day_table[i].day == pro_syn_require->day)
        {
            b_kv_init(KV_START_ADDRESS + i * B_KV_TOTAL_SIZE);
            b_kv_get_info(&pkvinfo);
            b_kv_get_cnumber(&number);
            for(j = 0;j < B_KV_ITEM_MAX_NUMBER;j++)
            {
                if(pkvinfo[B_KV_ITEM_MAX_NUMBER - j - 1] == 0)
                {
                    continue;
                }
                for(k = (j + 1);k < B_KV_ITEM_MAX_NUMBER;k++)
                {
                    if(pkvinfo[B_KV_ITEM_MAX_NUMBER - k - 1] == 0)
                    {
                        continue;
                    }
                    if(pkvinfo[B_KV_ITEM_MAX_NUMBER - k - 1] == pkvinfo[B_KV_ITEM_MAX_NUMBER - j - 1])
                    {
                        pkvinfo[B_KV_ITEM_MAX_NUMBER - k - 1] = 0x0;
                    }
                }
            }
            
            for(j = 0;j < number;j++)
            {
                if(pkvinfo[j] == 0)
                {
                    continue;
                }
                flash_read_buf((uint8_t *)&pro_walk_info, KV_START_ADDRESS + i * B_KV_TOTAL_SIZE + B_KV_VALUE_SADDR + j * sizeof(pro_walk_info_t), sizeof(pro_walk_info_t));
                
                protocol_struct_t  pro_struct = PROTOCOL_STRUCT_DEFAULT(CMD_BRIDGE_SYN);
                protocol_send(pro_struct, (uint8_t *)&pro_walk_info, sizeof(pro_walk_info_t));
            }
            b_kv_init(KV_START_ADDRESS + d_index * B_KV_TOTAL_SIZE);
            break;
        }
    }
}

void pro_init()
{
    protocol_init();
    update_kv_dtable();
    protocol_regist_command(CMD_GET_USER_ID, pro_get_useid_handler);
    protocol_regist_command(CMD_TOOL_SCAN, pro_tool_scan_handler);
    protocol_regist_command(CMD_TOOL_CONNECT, pro_tool_conn_handler);
    protocol_regist_command(CMD_TOOL_CONN_STA, pro_tool_conn_sta_handler);
    protocol_regist_command(CMD_GET_TOTAL_STEP, pro_get_total_step_handler);
 
    protocol_regist_command(CMD_BRIDGE_SET_TIME, pro_b_set_time_handler);
    protocol_regist_command(CMD_BRIDGE_GET_TIME, pro_b_get_time_handler);
    protocol_regist_command(CMD_BRIDGE_START, pro_bridge_start_handler);
    protocol_regist_command(CMD_BRIDGE_END, pro_bridge_end_handler);
    protocol_regist_command(CMD_BRIDGE_SYN, pro_bridge_syn_handler);
    
    b_kv_init(KV_START_ADDRESS + d_index * B_KV_TOTAL_SIZE);
}

int pro_clear_mac_rcd()
{
    if(s_status == S_NULL)
    {
        mac_rcd_number = 0;
        return 0;
    }
    return -1;
}




void pro_send_hb()
{
    if(s_status == S_BRIDGE_M)
    {
        return;
    }
    if(s_status >= S_WR_ING && cmd_idle == 0)
    {
        protocol_struct_t  pro_struct = PROTOCOL_STRUCT_DEFAULT(CMD_HEART);
        protocol_send(pro_struct, NULL, 0);
    }
    if(c_status != S_NULL)
    {
        timeout_s++;
        if(timeout_s > 5)
        {
            if(c_status == S_GET_ID)
            {
                pro_get_userid();
                timeout_s = 0;
            }
            else if(c_status == S_GET_STEP)
            {
                pro_get_step();
                timeout_s = 0;
            }
        }
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
            memset(&pro_value_struct, 0, sizeof(pro_value_struct_t));
            pro_get_userid();
            c_status = S_GET_ID;
            s_status = S_GET_ID;
            break;
        default: break;
    }
}



