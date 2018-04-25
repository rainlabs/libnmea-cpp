// NMEA library
// @author Vladimir Ziablitskii
// Copyright 2018 All rights reserved

#pragma once
#include "stdafx.h"
#include "types.h"

namespace nmea
{
	class NMEA_API GPSTime
	{
	public:
		GPSTime(uint8_t uHours = 0, uint8_t uMinutes = 0, uint8_t uSeconds = 0, unsigned short uMilliseconds = 0);
		virtual ~GPSTime();

		unsigned short Hours() const;
		unsigned short Minutes() const;
		unsigned short Seconds() const;
		unsigned short Milliseconds() const;
		bool IsEmpty() const;
		FString ToString() const;

	protected:
		uint8_t m_uHours;
		uint8_t m_uMinutes;
		uint8_t m_uSeconds;
		unsigned short m_uMilliseconds;
	};
}