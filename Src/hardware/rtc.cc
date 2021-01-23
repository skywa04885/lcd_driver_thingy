#include "hardware/rtc.h"

namespace Hardware
{
	void RTCDriver::unlock(void) noexcept
	{
		// Unlock RTC by writing key
		RTC->WPR = 0xCA;
		RTC->WPR = 0x53;
	}

	void RTCDriver::lock(void) noexcept
	{
		RTC->WPR = 0xFF;
	}

	void RTCDriver::init(void) noexcept
	{
		unlock();

		//
		// Configures the prescalar
		//

		RTC->PRER &= ~(RTC_PRER_PREDIV_A | RTC_PRER_PREDIV_S);
		RTC->PRER |= (127 << RTC_PRER_PREDIV_A_Pos) | (255 << RTC_PRER_PREDIV_S_Pos);

		//
		// Initialization mode
		//

		RTC->ISR |= RTC_ISR_INIT;
		while (!(RTC->ISR & RTC_ISR_INITF));

		setTime(0, 0, 0);
		setDate(20, 1, 1, RTC_MONDAY);

		RTC->ISR &= ~RTC_ISR_INIT;

		//
		// Finishes
		//

		lock();
	}

	void RTCDriver::getDateString(char *buffer) noexcept
	{
		RTC_DateTime_t dt = getDateTime();
		sprintf(buffer, "%u/%u/%u, %u:%u:%u",
				dt.date.date, dt.date.month, dt.date.year,
				dt.time.seconds, dt.time.minutes, dt.time.hours);
	}

	RTC_DateTime_t RTCDriver::getDateTime(void) noexcept
	{
		return RTC_DateTime_t {
				.time = getTime(),
				.date = getDate()
		};
	}

	RTC_Time_t RTCDriver::getTime(void) noexcept
	{
		RTC_Time_t time;

		time.hours = (RTC->TR & RTC_TR_HT) >> RTC_TR_HT_Pos;
		time.hours *= 10;
		time.hours += (RTC->TR & RTC_TR_HU) >> RTC_TR_HU_Pos;

		time.minutes = (RTC->TR & RTC_TR_MNT) >> RTC_TR_MNT_Pos;
		time.minutes *= 10;
		time.minutes += (RTC->TR & RTC_TR_MNU) >> RTC_TR_MNU_Pos;

		time.seconds = (RTC->TR & RTC_TR_ST) >> RTC_TR_ST_Pos;
		time.seconds *= 10;
		time.seconds += (RTC->TR & RTC_TR_SU) >> RTC_TR_SU_Pos;

		return time;
	}

	void RTCDriver::setTime(u8 hour, u8 minute, u8 seconds)
	{
		RTC->TR &= ~(RTC_TR_HT | RTC_TR_HU | RTC_TR_MNT | RTC_TR_MNU |
				RTC_TR_ST | RTC_TR_SU | RTC_TR_PM);

		RTC->TR |= ((hour / 10) << RTC_TR_HT_Pos);
		RTC->TR |= ((hour % 10) << RTC_TR_HU_Pos);

		RTC->TR |= ((minute / 10) << RTC_TR_MNT_Pos);
		RTC->TR |= ((minute % 10) << RTC_TR_MNU_Pos);

		RTC->TR |= ((seconds / 10) << RTC_TR_ST_Pos);
		RTC->TR |= ((seconds % 10) << RTC_TR_SU_Pos);
	}

	RTC_Date_t RTCDriver::getDate(void) noexcept
	{
		RTC_Date_t date;

		date.year = (RTC->DR & RTC_DR_YT) >> RTC_DR_YT_Pos;
		date.year *= 10;
		date.year += (RTC->DR & RTC_DR_YU) >> RTC_DR_YU_Pos;

		date.month = (RTC->DR & RTC_DR_MT) >> RTC_DR_MT_Pos;
		date.month *= 10;
		date.month += (RTC->DR & RTC_DR_MU) >> RTC_DR_MU_Pos;

		date.date = (RTC->DR & RTC_DR_DT) >> RTC_DR_DT_Pos;
		date.date *= 10;
		date.date += (RTC->DR & RTC_DR_DU) >> RTC_DR_DU_Pos;

		date.weekday = static_cast<RTC_WeekDay_t>((RTC->DR & RTC_DR_WDU) >> RTC_DR_WDU_Pos);

		return date;
	}

	void RTCDriver::setDate(u8 year, u8 month, u8 date, RTC_WeekDay_t weekday) noexcept
	{
		RTC->DR &= ~(RTC_DR_YT | RTC_DR_YU | RTC_DR_WDU | RTC_DR_MT |
				RTC_DR_MU | RTC_DR_DT | RTC_DR_DU);

		RTC->DR |= ((weekday & 0x7) << RTC_DR_WDU_Pos);

		RTC->DR |= ((year / 10) << RTC_DR_YT_Pos);
		RTC->DR |= ((year % 10) << RTC_DR_YU_Pos);

		RTC->DR |= ((month / 10) << RTC_DR_MT_Pos);
		RTC->DR |= ((month % 10) << RTC_DR_MU_Pos);

		RTC->DR |= ((date / 10) << RTC_DR_DT_Pos);
		RTC->DR |= ((date % 10) << RTC_DR_DU_Pos);
	}
}
