#define INC_DATA_TYES_H
#ifdef INC_DATA_TYES_H

#ifndef DATEANDTIME__DATE_TIME_TYPES_H_
#define DATEANDTIME__DATE_TIME_TYPES_H_

#include "stdint.h"

#define data_time_TIME_LEN (uint8_t)9U
#define data_time_DATA_LEN (uint8_t)11U

#define DATEFORMAT_MONTHS_MAX 12U
#define DATEFORMAT_DAYS_MAX 356U
struct dateformat_t
{
	uint16_t year;
	uint8_t month;
	uint8_t day;
};


#define TIMEFORMAT_HOURS_MAX	24U
#define TIMEFORMAT_MINUTES_MAX	60U
#define TIMEFORMAT_SECONDS_MAX	60U
#define TIMEFORMAT_MS_MAX 1000U
struct timeformat_t
{
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint16_t msec;
};

#endif /* DATEANDTIME__DATE_TIME_TYPES_H_ */

#endif // INC_DATA_TYES_H