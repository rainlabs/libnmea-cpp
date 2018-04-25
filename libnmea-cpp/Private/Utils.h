// NMEA library
// @author Vladimir Ziablitskii
// Copyright 2018 All rights reserved

#pragma once
#include "stdafx.h"
#include "types.h"

namespace nmea
{
	class Utils
	{
	public:
		static bool IsNumber(const FString& sRaw);
		static bool IsUppercase(const FString& sRaw);
	};
}