// NMEA library
// @author Vladimir Ziablitskii
// Copyright 2018 All rights reserved

#include "stdafx.h"
#include "geo_coord.h"

using namespace nmea;

GeoCoordinate::GeoCoordinate(int iDegrees, double dMinutes, Direction eDirection) :
	m_iDegrees(iDegrees),
	m_dMinutes(dMinutes),
	m_eDirecton(eDirection)
{
}

Latitude::Latitude(int iDegrees, double dMinutes, Direction eDirection) :
	GeoCoordinate(iDegrees, dMinutes, eDirection)
{
}

Longitude::Longitude(int iDegrees, double dMinutes, Direction eDirection) :
	GeoCoordinate(iDegrees, dMinutes, eDirection)
{
}

GeoCoordinate::~GeoCoordinate()
{
}

Direction GeoCoordinate::GetDirection() const
{
	return m_eDirecton;
}

FChar GeoCoordinate::GetDirectionSymbol() const
{
	switch (m_eDirecton) {
	case Direction::NORTH:
		return DIR_NORTH;
	case Direction::SOUTH:
		return DIR_SOUTH;
	case Direction::WEST:
		return DIR_WEST;
	case Direction::EAST:
		return DIR_EAST;
	}

	return DIR_UNKNOWN;
}

int GeoCoordinate::GetDegrees() const
{
	return m_iDegrees;
}

double GeoCoordinate::GetMinutes() const
{
	return m_dMinutes;
}
