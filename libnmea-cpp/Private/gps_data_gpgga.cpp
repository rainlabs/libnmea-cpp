// NMEA library
// @author Vladimir Ziablitskii
// Copyright 2018 All rights reserved

#include "stdafx.h"
#include "gps_data_gpgga.h"
#include "validators.h"

using namespace nmea;

FString nmea::GPSDataGPGGA::GetTypeString()
{
	return _S("GPGGA");
}

FString GPSDataGPGGA::GetSentence() const
{
	return m_sSentence;
}

ValidationStatus GPSDataGPGGA::GetValidateState() const
{
	return Validate(m_sSentence);
}

GPSTime GPSDataGPGGA::GetTime() const
{
	return m_oTime;
}

Latitude GPSDataGPGGA::GetLatitude() const
{
	return m_oLat;
}

Longitude GPSDataGPGGA::GetLongitude() const
{
	return m_oLong;
}

GPSQuality GPSDataGPGGA::GetGPSQualityIndicator() const
{
	return m_eGPSQuality;
}

unsigned short GPSDataGPGGA::GetSatellitesNumber() const
{
	return m_uSatellites;
}

float GPSDataGPGGA::GetHorizontalDilution() const
{
	return m_fHorizontalDilution;
}

float GPSDataGPGGA::GetAntennaAltitude() const
{
	return m_fAntennaAltitude;
}

float GPSDataGPGGA::GetGeoidalSeparation() const
{
	return m_fGeoidalSeparation;
}

FDuration GPSDataGPGGA::GetDifferentialDataAge() const
{
	return m_uDiffDataAge;
}

unsigned short GPSDataGPGGA::GetDifferentialStationID() const
{
	return m_uStationID;
}

GPSDataGPGGA::GPSDataGPGGA(const FString & sSentence) :
	m_sSentence(sSentence),
	m_oTime(),
	m_eGPSQuality(GPSQuality::NOT_AVAILABLE),
	m_uSatellites(0),
	m_fHorizontalDilution(.0f),
	m_fAntennaAltitude(.0f),
	m_fGeoidalSeparation(.0f),
	m_uDiffDataAge(0),
	m_uStationID(0)
{
	Initialize();
}

void GPSDataGPGGA::Initialize()
{
	//if (!Validate(m_sSentence)) return;

	std::vector<FString> vValues;
	ExtractValues(m_sSentence, vValues);

	// Temp/accumulate variable
	FString sValue(_S(""));

	for (size_t i = 0; i < vValues.size(); i++) {
		switch (i) {
		case (GPGGA_TIME):
			m_oTime = GPSTimeValidator(m_sSentence).Validate(vValues[i]).Get();
			break;
		case (GPGGA_LATITUDE):
			sValue = vValues[i]; // cache value, use it in next iteration
			break;
		case (GPGGA_LATITUDE_DIRECTION):
			m_oLat = LatitudeValidator(m_sSentence).Validate(sValue, vValues[i]).Get();
			break;
		case (GPGGA_LONGITUDE):
			sValue = vValues[i]; // cache value, use it in next iteration
			break;
		case (GPGGA_LONGITUDE_DIRECTION):
			m_oLong = LongitudeValidator(m_sSentence).Validate(sValue, vValues[i]).Get();
			break;
		case (GPGGA_QUALITY_INDICATOR):
			m_eGPSQuality = GPSQualityValidator(m_sSentence).Validate(vValues[i]).Get();
			break;
		case (GPGGA_SATELLITES):
			m_uSatellites = NumberValidator<uint8_t>(m_sSentence).ValidateRange(vValues[i], 0, 12).Get();
			break;
		case (GPGGA_HORIZONTAL_DILUTION):
			m_fHorizontalDilution = NumberValidator<float>(m_sSentence).ValidateMin(vValues[i], 0).Get();
			break;
		case (GPGGA_ALTITUDE):
			sValue = vValues[i]; // cache value, use it in next iteration
			break;
		case (GPGGA_ALTITUDE_UNIT):
			m_fAntennaAltitude = AltitudeValidator(m_sSentence).Validate(sValue, vValues[i]).Get();
			break;
		case (GPGGA_GEOIDAL):
			sValue = vValues[i]; // cache value, use it in next iteration
			break;
		case (GPGGA_GEOIDAL_UNIT):
			m_fGeoidalSeparation = AltitudeValidator(m_sSentence).Validate(sValue, vValues[i]).Get();
			break;
		case (GPGGA_AGE_DIFFERENTIAL_GPS_DATA):
			m_uDiffDataAge = FDurationValidator(m_sSentence).Validate(vValues[i]).Get();
			break;
		case (GPGGA_STATION_ID):
			m_uStationID = NumberValidator<unsigned short>(m_sSentence).ValidateRange(vValues[i], 0, 1023).Get();
			break;
		default:
			throw SyntaxException(_S("Too many parts in sentence"), m_sSentence);
			break;
		}
	}

	return;
}
