// NMEA library
// @author Vladimir Ziablitskii
// Copyright 2018 All rights reserved

#include "stdafx.h"
#include "gps_time.h"
#include "utils.h"

using namespace nmea;

GPSTime::GPSTime(uint8_t uHours, uint8_t uMinutes, uint8_t uSeconds, unsigned short uMilliseconds) :
	m_uHours(uHours),
	m_uMinutes(uMinutes),
	m_uSeconds(uSeconds),
	m_uMilliseconds(uMilliseconds)
{
}

GPSTime::~GPSTime()
{
}

unsigned short GPSTime::Hours() const
{
	return m_uHours;
}

unsigned short GPSTime::Minutes() const
{
	return m_uMinutes;
}

unsigned short GPSTime::Seconds() const
{
	return m_uSeconds;
}

unsigned short GPSTime::Milliseconds() const
{
	return m_uMilliseconds;
}

bool GPSTime::IsEmpty() const
{
	return m_uHours == 0 && m_uMinutes == 0 && m_uSeconds == 0 && m_uMilliseconds == 0;
}

FString GPSTime::ToString() const
{
	FStream oOS;

	oOS << (int) m_uHours
		<< _S(":")
		<< (int) m_uMinutes
		<< _S(":")
		<< (int) m_uSeconds
		<< _S(".")
		<< (int) m_uMilliseconds;

	return oOS.str();
}
