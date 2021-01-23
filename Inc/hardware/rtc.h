#pragma once

#include <stdio.h>

#include "../types.h"
#include "vendor/stm32h750xx.h"

namespace Hardware
{
	typedef enum
	{
		RTC_FORBIDDEN = 0b000,
		RTC_MONDAY,
		RTC_TUESDAY,
		RTC_WEDNESDAY,
		RTC_THURSDAY,
		RTC_FRIDAY,
		RTC_SATURDAY,
		RTC_SUNDAY
	} RTC_WeekDay_t;

	typedef struct
	{
		u8 hours, minutes, seconds;
	} RTC_Time_t;

	typedef struct
	{
		u8 year, month, date;
		RTC_WeekDay_t weekday;
	} RTC_Date_t;

	typedef struct
	{
		RTC_Time_t time;
		RTC_Date_t date;
	} RTC_DateTime_t;

	class RTCDriver
	{
	public:
		static void init(void) noexcept;

		static void getDateString(char *buffer) noexcept;
		static RTC_DateTime_t getDateTime(void) noexcept;
		static RTC_Time_t getTime(void) noexcept;
		static RTC_Date_t getDate(void) noexcept;
	private:
		static void unlock(void) noexcept;
		static void lock(void) noexcept;
		static void setTime(u8 hour, u8 minute, u8 seconds);
		static void setDate(u8 year, u8 month, u8 date, RTC_WeekDay_t weekday) noexcept;
	};
}
