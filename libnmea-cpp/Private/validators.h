// NMEA library
// @author Vladimir Ziablitskii
// Copyright 2018 All rights reserved

#pragma once
#include "stdafx.h"
#include "types.h"
#include "utils.h"
#include "gps_time.h"
#include "geo_coord.h"
#include "nmea_exception.h"

#define DEFINE_VALIDATOR(Type) \
	class Type ## Validator : public Validator<Type> \
	{ \
	public: \
		explicit Type ## Validator(const FString& sSentence) : Validator<Type>(sSentence) {} \
		Type ## Validator& Validate(const FString& sValue); \
	}

#define DEFINE_VALIDATOR_TwoValue(Type) \
	class Type ## Validator : public Validator<Type> \
	{ \
	public: \
		explicit Type ## Validator(const FString& sSentence) : Validator<Type>(sSentence) {} \
		Type ## Validator& Validate(const FString& sValue, const FString& sUnit); \
	}

namespace nmea
{
	/*
	* Base Validator template
	*/
	template<typename T>
	class Validator
	{
	public:
		explicit Validator(const FString& sSentence) :
			m_sSentence(sSentence),
			m_oValue()
		{
		}

		inline T Get() const {
			return m_oValue;
		}

	protected:
		FString m_sSentence;
		T m_oValue;
	};

	/* Complex type validators */
	DEFINE_VALIDATOR(GPSTime);
	DEFINE_VALIDATOR_TwoValue(Latitude);
	DEFINE_VALIDATOR_TwoValue(Longitude);
	DEFINE_VALIDATOR(GPSQuality);
	DEFINE_VALIDATOR(FDuration);

	class AltitudeValidator : public Validator<float>
	{
	public:
		explicit AltitudeValidator(const FString& sSentence) : Validator<float>(sSentence) {}
		AltitudeValidator& Validate(const FString& sValue, const FString& sUnit);
	};

	/*
	* Number validators: in range, min, check number
	*/
	template<typename T>
	class NumberValidator : public Validator<T>
	{
	public:
		NumberValidator(const FString& sSentence) : Validator<T>(sSentence) { this->m_oValue = 0; }

		// IsNumber
		NumberValidator& Validate(const FString& sValue)
		{
			if (sValue.empty()) return *this;
			if (!Utils::IsNumber(sValue)) throw SyntaxException(_S("Incorrect number string"), this->m_sSentence);

			float fValue = std::stof(sValue);
			this->m_oValue = (T)fValue;
			if (this->m_oValue != fValue) throw NumberException<float>(_S("Number has incorrect type"), fValue, this->m_sSentence);

			return *this;
		}

		// IsNumber and in range
		NumberValidator& ValidateRange(const FString& sValue, T minValue, T maxValue)
		{
			if (sValue.empty()) return *this;
			if (!Utils::IsNumber(sValue)) throw SyntaxException(_S("Incorrect number string"), this->m_sSentence);

			float fValue = std::stof(sValue);
			if (fValue < minValue || fValue > maxValue) throw NumberException<float>(_S("Number is not in range"), fValue, this->m_sSentence);

			this->m_oValue = (T)fValue;
			if (this->m_oValue != fValue) throw NumberException<float>(_S("Number has incorrect type"), fValue, this->m_sSentence);

			return *this;
		}

		// IsNumber and greater than minValue
		NumberValidator& ValidateMin(const FString& sValue, T minValue)
		{
			if (sValue.empty()) return *this;
			if (!Utils::IsNumber(sValue)) throw SyntaxException(_S("Incorrect number string"), this->m_sSentence);

			float fValue = std::stof(sValue);
			if (fValue < minValue) throw NumberException<float>(_S("Number is less than minimum value"), fValue, this->m_sSentence);

			this->m_oValue = (T)fValue;
			if (this->m_oValue != fValue) throw NumberException<float>(_S("Number has incorrect type"), fValue, this->m_sSentence);

			return *this;
		}
	};
}