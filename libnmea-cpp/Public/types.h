// NMEA library
// @author Vladimir Ziablitskii
// Copyright 2018 All rights reserved

#pragma once
#include "stdafx.h"

#define _S(text) text

namespace nmea
{
	typedef char FChar;
	typedef std::string FString;
	typedef std::ostringstream FStream;
	typedef std::chrono::milliseconds FDuration;

	const FChar DIR_NORTH = _S('N');
	const FChar DIR_SOUTH = _S('S');
	const FChar DIR_EAST = _S('E');
	const FChar DIR_WEST = _S('W');
	const FChar DIR_UNKNOWN = _S('\0');
	const uint8_t SENTENCE_MAX_LENGTH = 82;
	const uint8_t SENTENCE_MIN_LENGTH = 25;
	const uint8_t SENTENCE_PREFIX_LENGTH = 5;
	const FChar SENTENCE_BEGIN = _S('$');
	const FString SENTENCE_ENDINGS = _S("\r\n");
	const FChar SENTENCE_DELIM = _S('*');
	const FChar SENTENCE_PART_DELIM = _S(',');
	const FChar UNIT_METER = _S('M');

	enum class SentenceType : uint8_t
	{
		UNKNOWN,
		GPGGA,
		GPGLL,
		GPRMC
	};

	enum class ValidationStatus : uint8_t
	{
		UNKNOWN,
		OK,
		INCORRECT_LENGTH,
		INCORRECT_BEGIN_SIGN,
		INCORRECT_ENDINGS,
		INCORRECT_PREFIX,
		INCORRECT_CHECKSUM
	};

	enum class Direction : uint8_t
	{
		UNKNOWN,
		NORTH,
		SOUTH,
		EAST,
		WEST
	};

	enum class GPSQuality : uint8_t
	{
		NOT_AVAILABLE = 0,
		GPS_SPS,
		GPS_DIFFERENTIAL,
		GPS_PPS,
		RTK,
		FLOAT_RTK,
		ESTIMATED,
		MANUAL,
		SIMULATOR
	};

	enum class Unit : uint8_t
	{
		METER
	};
}