
#include "colibri_bsp.h"

/* ����ʹ���������ϵ��豸 */
void EvbSetupEntry(void)
{
  EvbUart1Config();
  EvbLedConfig();//while(1)
  EvbKeyConfig();
}


void EvbTraceEntry(const char* str)
{
    EvbUart1WriteStr(str);
}


