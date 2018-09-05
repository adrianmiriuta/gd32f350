#include "calendar.h"


void calendar_init(calendar_info_t info)
{
    rtc_parameter_struct rtc_parameter = 
    {
        .rtc_factor_asyn = 0x4e - 1,
        .rtc_factor_syn = 0x200 - 1,
        .rtc_display_format = RTC_24HOUR,
    };

    rtc_parameter.rtc_year = DEC2BCD(info.year);
    rtc_parameter.rtc_month = info.month;
    rtc_parameter.rtc_date = DEC2BCD(info.day);
    rtc_parameter.rtc_day_of_week = info.week;
    rtc_parameter.rtc_hour = info.hour;
    rtc_parameter.rtc_minute = DEC2BCD(info.min);
    rtc_parameter.rtc_second = DEC2BCD(info.second);
    rtc_init(&rtc_parameter);

}


void calendar_get_date(calendar_info_t *pinfo)
{
    rtc_parameter_struct rtc_parameter;
    rtc_current_time_get(&rtc_parameter);
    pinfo->year = BCD2DEC(rtc_parameter.rtc_year);
    pinfo->month = rtc_parameter.rtc_month;
    pinfo->day = BCD2DEC(rtc_parameter.rtc_date);
    pinfo->week = rtc_parameter.rtc_day_of_week;
    pinfo->hour = rtc_parameter.rtc_hour;
    pinfo->min = BCD2DEC(rtc_parameter.rtc_minute);
    pinfo->second = BCD2DEC(rtc_parameter.rtc_second);
}








