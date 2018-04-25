// MEA library
// @author Vladimir Ziablitskii
// Copyright 2018 All rights reserved

#include "stdafx.h"
#include "Utils.h"

using namespace nmea;

bool Utils::IsNumber(const FString & sRaw)
{
	if (sRaw.empty()) return false;

	bool bDot(false);
	for (size_t i = 0; i < sRaw.size(); i++) {
		if (i == 0 && sRaw[i] == _S('-')) continue; //forward minus sign alowed
		if (sRaw[i] == _S('.') && !bDot) {
			bDot = true; // one dot on whole number
			continue;
		}

		if (sRaw[i] < _S('0') || sRaw[i] > _S('9')) return false;
	}

	return true;
}

bool Utils::IsUppercase(const FString & sRaw)
{
	if (sRaw.empty()) return false;

	for (auto it : sRaw) {
		if (it < _S('A') || it > _S('Z')) return false;
	}

	return true;
}
