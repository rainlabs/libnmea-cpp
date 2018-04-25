// NMEA library
// @author Vladimir Ziablitskii
// Copyright 2018 All rights reserved

#pragma once
#include "stdafx.h"
#include "types.h"
#include <vector>
#include "geo_coord.h"
#include "gps_time.h"

namespace nmea
{
	class GPSDataInterface;
	typedef std::shared_ptr<GPSDataInterface> GPSDataPtr;

	class NMEA_API GPSDataInterface
	{
	public:
		static GPSDataPtr Parse(const FString& sSentence);
		virtual ~GPSDataInterface() {};
		virtual FString GetSentence() const = 0;
		virtual SentenceType GetType() const = 0;
		virtual ValidationStatus GetValidateState() const = 0;
		// UTC hhmmss.sss
		virtual GPSTime GetTime() const = 0;
		// Latitude llll.ll N/S
		virtual Latitude GetLatitude() const = 0;
		// Longitude yyyyy.yy E/W
		virtual Longitude GetLongitude() const = 0;
		// GPS quality indicator x (0-8), 0 - invalid
		virtual GPSQuality GetGPSQualityIndicator() const = 0;
		// Number of satellites in use xx 00-12
		virtual unsigned short GetSatellitesNumber() const = 0;
		// Horizontal dilution of precision x.x
		virtual float GetHorizontalDilution() const = 0;
		// Antenna altitude above/below mean sea level (geoid) x.x
		// Units of antenna altitude, m M
		virtual float GetAntennaAltitude() const = 0;
		// Geoidal separation x.x
		// Units of Geoidal separation, m M
		virtual float GetGeoidalSeparation() const = 0;
		// Age of differential GPS data	x.x
		virtual FDuration GetDifferentialDataAge() const = 0;
		// Differential reference station ID, 0000-1023 xxxx
		virtual unsigned short GetDifferentialStationID() const = 0;
	protected:
		GPSDataInterface() {};

		ValidationStatus Validate(const FString& sSentence) const;
		uint8_t SentenceChecksum(const FString& sSentence) const;
		uint8_t ExtractChecksum(const FString& sSentence) const;
		void ExtractValues(const FString& sSentence, std::vector<FString>& vOutValues);
	};
}