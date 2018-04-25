// NMEA library
// @author Vladimir Ziablitskii
// Copyright 2018 All rights reserved

#pragma once
#include "stdafx.h"
#include "gps_data.h"

namespace nmea
{
	const size_t GPGGA_TIME = 0;
	const size_t GPGGA_LATITUDE = 1;
	const size_t GPGGA_LATITUDE_DIRECTION = 2;
	const size_t GPGGA_LONGITUDE = 3;
	const size_t GPGGA_LONGITUDE_DIRECTION = 4;
	const size_t GPGGA_QUALITY_INDICATOR = 5;
	const size_t GPGGA_SATELLITES = 6;
	const size_t GPGGA_HORIZONTAL_DILUTION = 7;
	const size_t GPGGA_ALTITUDE = 8;
	const size_t GPGGA_ALTITUDE_UNIT = 9;
	const size_t GPGGA_GEOIDAL = 10;
	const size_t GPGGA_GEOIDAL_UNIT = 11;
	const size_t GPGGA_AGE_DIFFERENTIAL_GPS_DATA = 12;
	const size_t GPGGA_STATION_ID = 13;

	class NMEA_API GPSDataGPGGA : public GPSDataInterface
	{
	public:
		static FString GetTypeString();
		virtual FString GetSentence() const override;
		inline virtual SentenceType GetType() const override {
			return SentenceType::GPGGA;
		}
		virtual ValidationStatus GetValidateState() const override;

		virtual GPSTime GetTime() const override;
		virtual Latitude GetLatitude() const override;
		virtual Longitude GetLongitude() const override;
		virtual GPSQuality GetGPSQualityIndicator() const override;
		virtual unsigned short GetSatellitesNumber() const override;
		virtual float GetHorizontalDilution() const override;
		virtual float GetAntennaAltitude() const override;
		virtual float GetGeoidalSeparation() const override;
		virtual FDuration GetDifferentialDataAge() const override;
		virtual unsigned short GetDifferentialStationID() const override;

	protected:
		friend class GPSDataInterface;
		GPSDataGPGGA(const FString& sSentence);
		void Initialize();

	private:
		FString m_sSentence;
		GPSTime m_oTime;
		Latitude m_oLat;
		Longitude m_oLong;
		GPSQuality m_eGPSQuality;
		uint8_t m_uSatellites;
		float m_fHorizontalDilution;
		float m_fAntennaAltitude;
		float m_fGeoidalSeparation;
		FDuration m_uDiffDataAge;
		unsigned short m_uStationID;
	};
}