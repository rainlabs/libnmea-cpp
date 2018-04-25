// NMEA library
// @author Vladimir Ziablitskii
// Copyright 2018 All rights reserved

#include "stdafx.h"
#include "gps_data.h"
#include "gps_data_gpgga.h"

using namespace nmea;

GPSDataPtr GPSDataInterface::Parse(const FString & sSentence)
{
	if (sSentence.size() > SENTENCE_MAX_LENGTH || sSentence.size() < SENTENCE_MIN_LENGTH) return nullptr; // Incorrect length

	if (sSentence.substr(1, SENTENCE_PREFIX_LENGTH) == GPSDataGPGGA::GetTypeString()) {
		GPSDataPtr pData = std::make_shared<GPSDataGPGGA>(GPSDataGPGGA(sSentence));
		return pData;
		//if (pData->IsValid()) return pData;
		//return nullptr;
	}

	return nullptr; // undefined sentence type
}

ValidationStatus GPSDataInterface::Validate(const FString & sSentence) const
{
	/* sentence length in range */
	if (sSentence.size() > SENTENCE_MAX_LENGTH || sSentence.size() < SENTENCE_MIN_LENGTH) return ValidationStatus::INCORRECT_LENGTH;
	/* should begin with $ sign */
	if (sSentence[0] != SENTENCE_BEGIN) return ValidationStatus::INCORRECT_BEGIN_SIGN;
	/* should ends with \r\n */
	if (sSentence.substr(sSentence.size() - 2) != SENTENCE_ENDINGS) return ValidationStatus::INCORRECT_ENDINGS;

	/* only UPPERCASE for prefix string */
	for (size_t i = 1; i <= SENTENCE_PREFIX_LENGTH; i++) {
		if (sSentence[i] < _S('A') || sSentence[i] > _S('Z')) return ValidationStatus::INCORRECT_PREFIX;
	}

	/* mandatory comma after prefix */
	if (sSentence[SENTENCE_PREFIX_LENGTH + 1] != SENTENCE_PART_DELIM) return ValidationStatus::INCORRECT_PREFIX;
	
	/* checksum should be valid and correct */
	uint8_t cChk = ExtractChecksum(sSentence);
	if (cChk == 0 || cChk != SentenceChecksum(sSentence)) return ValidationStatus::INCORRECT_CHECKSUM;

	return ValidationStatus::OK;
}

uint8_t GPSDataInterface::SentenceChecksum(const FString & sSentence) const
{
	uint8_t cChk(0);
	size_t uEndPos = sSentence.find(SENTENCE_DELIM);

	if (uEndPos == FString::npos) return 0; // incorrect sentence

	for (size_t i = 1; i < uEndPos; i++) {
		cChk ^= sSentence[i];
	}

	return cChk;
}

uint8_t GPSDataInterface::ExtractChecksum(const FString & sSentence) const
{
	size_t uEndPos = sSentence.find(SENTENCE_DELIM);

	if (uEndPos == FString::npos || (++uEndPos + 1) > sSentence.size()) return 0; // incorrect sentence

	return std::stoi(sSentence.substr(uEndPos, 2).c_str(), nullptr, 16); // hex digits
}

void GPSDataInterface::ExtractValues(const FString & sSentence, std::vector<FString>& vOutValues)
{
	size_t uFound(1);

	while ((uFound = sSentence.find_first_of(SENTENCE_PART_DELIM, uFound)) != FString::npos) {
		size_t uEndPart = sSentence.find_first_of(SENTENCE_PART_DELIM, ++uFound);
		if (uEndPart == FString::npos)
			uEndPart = sSentence.find_first_of(SENTENCE_DELIM, uFound);

		vOutValues.push_back( sSentence.substr(uFound, uEndPart - uFound) );
	}
}
