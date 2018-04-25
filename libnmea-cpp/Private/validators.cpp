#include "stdafx.h"
#include "validators.h"

using namespace nmea;

GPSTimeValidator& GPSTimeValidator::Validate(const FString& sRawTime)
{
	if (sRawTime.empty()) return *this; // soft return
	if (!Utils::IsNumber(sRawTime)) throw SyntaxException(_S("Time part should contains only digits and one dot"), m_sSentence);

	size_t uDotPos = sRawTime.find_first_of(_S('.'));
	if (uDotPos != 6 || sRawTime.size() > 10) throw SyntaxException(_S("Incorrect time digits count"), m_sSentence);

	FString sLeftPart = sRawTime.substr(0, uDotPos);
	FString sRightPart = sRawTime.substr(uDotPos + 1);

	short iHours = std::stoi(sLeftPart.substr(0, 2));
	if(iHours < 0 || iHours > 23) throw NumberException<int>(_S("Time hours is not in range [0-23]"), iHours, m_sSentence);

	short iMinutes = std::stoi(sLeftPart.substr(2, 2));
	if (iMinutes < 0 || iMinutes > 59) throw NumberException<int>(_S("Time minutes is not in range [0-59]"), iMinutes, m_sSentence);

	short iSeconds = std::stoi(sLeftPart.substr(4, 2));
	if (iSeconds < 0 || iSeconds > 59) throw NumberException<int>(_S("Time seconds is not in range [0-59]"), iSeconds, m_sSentence);

	short iMilliseconds = std::stoi(sRightPart);
	if (iMilliseconds < 0 || iMilliseconds > 999) throw NumberException<int>(_S("Time milliseconds is not in range [0-999]"), iMilliseconds, m_sSentence);

	m_oValue = GPSTime(iHours, iMinutes, iSeconds, iMilliseconds);
	return *this;
}

LatitudeValidator & LatitudeValidator::Validate(const FString & sValue, const FString & sUnit)
{
	if (sValue.empty() && sUnit.empty()) return *this;
	if (sUnit.size() > 1) throw SyntaxException(_S("Latitude direction should be One symbol"), m_sSentence);

	double dMinutes(.0);
	int iDegrees(0);
	Direction eDirecton(Direction::UNKNOWN);

	if (!sValue.empty()) {
		size_t uFound = sValue.find(_S('.'));

		if (uFound != FString::npos) {
			uFound -= 2; // minutes starts 2 symbols before dot
			dMinutes = std::stod(sValue.substr(uFound));
			iDegrees = std::stoi(sValue.substr(0, uFound));
		}
	}

	if (sUnit.size() == 1) {
		FChar cDirection = sUnit[0];
		switch (cDirection) {
		case DIR_NORTH:
			eDirecton = Direction::NORTH;
			break;
		case DIR_SOUTH:
			eDirecton = Direction::SOUTH;
			break;
		default:
			throw SyntaxException(_S("Latitude direction can be only N/S symbol"), m_sSentence);
			break;
		}
	}

	// perhabs be 85.05112878
	if (iDegrees < 0 || iDegrees > 90 || (iDegrees == 90 && dMinutes > 0)) throw NumberException<int>(_S("Latitude degrees should be in range [0-90] for hemisphere"), iDegrees, m_sSentence);
	if (dMinutes < 0 || dMinutes >= 60) throw NumberException<double>(_S("Latitude minutes should be in range [0-60)"), dMinutes, m_sSentence);

	m_oValue = Latitude(iDegrees, dMinutes, eDirecton);
	return *this;
}

LongitudeValidator & LongitudeValidator::Validate(const FString & sValue, const FString & sUnit)
{
	if (sValue.empty() && sUnit.empty()) return *this;
	if (sUnit.size() > 1) throw SyntaxException(_S("Longitude direction should be One symbol"), m_sSentence);

	double dMinutes(.0);
	int iDegrees(0);
	Direction eDirecton(Direction::UNKNOWN);

	if (!sValue.empty()) {
		size_t uFound = sValue.find(_S('.'));

		if (uFound != FString::npos) {
			uFound -= 2; // minutes starts 2 symbols before dot
			dMinutes = std::stod(sValue.substr(uFound));
			iDegrees = std::stoi(sValue.substr(0, uFound));
		}
	}

	if (sUnit.size() == 1) {
		FChar cDirection = sUnit[0];
		switch (cDirection) {
		case DIR_WEST:
			eDirecton = Direction::WEST;
			break;
		case DIR_EAST:
			eDirecton = Direction::EAST;
			break;
		default:
			throw SyntaxException(_S("Longitude direction can be only W/E symbol"), m_sSentence);
			break;
		}
	}

	if (iDegrees < 0 || iDegrees > 180 || (iDegrees == 180 && dMinutes > 0)) throw NumberException<int>(_S("Longitude degrees should be in range [0-180] for hemisphere"), iDegrees, m_sSentence);
	if (dMinutes < 0 || dMinutes >= 60) throw NumberException<double>(_S("Longitude minutes should be in range [0-60)"), dMinutes, m_sSentence);

	m_oValue = Longitude(iDegrees, dMinutes, eDirecton);
	return *this;
}


GPSQualityValidator & GPSQualityValidator::Validate(const FString & sValue)
{
	if (sValue.empty()) return *this;
	if (sValue.size() > 1) throw SyntaxException(_S("GPSQuality should be one digit"), m_sSentence);
	if (!Utils::IsNumber(sValue)) throw SyntaxException(_S("GPSQuality should contains only one digit"), m_sSentence);

	float fValue = std::stof(sValue);
	if (fValue < 0 || fValue > 8) throw NumberException<int>(_S("GPSQuality should be in range [0-8]"), (int)fValue, m_sSentence);

	int iValue = (int) fValue;
	if(iValue != fValue) throw NumberException<float>(_S("GPSQuality should be integer"), fValue, m_sSentence);

	m_oValue = (GPSQuality)iValue;
	return *this;
}

FDurationValidator & FDurationValidator::Validate(const FString & sValue)
{
	if (sValue.empty()) return *this;
	if (!Utils::IsNumber(sValue)) throw SyntaxException(_S("Differntial data age should contains only number symbols"), m_sSentence);

	float fValue = std::stof(sValue);
	if (fValue < 0) throw NumberException<float>(_S("Differntial data age should be equal or greater than 0"), fValue, m_sSentence);

	std::chrono::duration<float> uSeconds(fValue);
	m_oValue = std::chrono::duration_cast<FDuration>(uSeconds);

	return *this;
}

AltitudeValidator & AltitudeValidator::Validate(const FString & sValue, const FString & sUnit)
{
	if (sUnit.size() != 1) throw SyntaxException(_S("Altitude/Geoidal unit incorrect size"), m_sSentence);
	if (sUnit[0] != UNIT_METER) throw SyntaxException(_S("Altitude/Geoidal unit unknown"), m_sSentence);

	m_oValue = NumberValidator<float>(m_sSentence).Validate(sValue).Get();
	return *this;
}
