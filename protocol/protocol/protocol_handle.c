#include "protocol_handle.h"
#include "protocol.h"


void pro_get_useid_handler(protocol_info_t info)
{
    ;
}




/** ---------------------------------------------  */

void pro_init()
{
    protocol_init();
    protocol_regist_command(CMD_GET_USER_ID, pro_get_useid_handler);
}












