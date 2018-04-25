// NMEA library
// @author Vladimir Ziablitskii
// Copyright 2018 All rights reserved

#pragma once
#include "stdafx.h"
#include "types.h"

namespace nmea
{
	class NMEA_API GeoCoordinate
	{
	public:
		GeoCoordinate(int iDegrees = 0, double dMinutes = .0, Direction eDirection = Direction::UNKNOWN);
		virtual ~GeoCoordinate();

		Direction GetDirection() const;
		FChar GetDirectionSymbol() const;
		int GetDegrees() const;
		double GetMinutes() const;

	protected:
		int m_iDegrees;
		double m_dMinutes;
		Direction m_eDirecton;
	};

	class NMEA_API Latitude : public GeoCoordinate
	{
	public:
		Latitude(int iDegrees = 0, double dMinutes = .0, Direction eDirection = Direction::UNKNOWN);
	};

	class NMEA_API Longitude : public GeoCoordinate
	{
	public:
		Longitude(int iDegrees = 0, double dMinutes = .0, Direction eDirection = Direction::UNKNOWN);
	};
}