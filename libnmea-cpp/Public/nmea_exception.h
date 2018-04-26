// NMEA library
// @author Vladimir Ziablitskii
// Copyright 2018 All rights reserved

#pragma once
#include "stdafx.h"
#include "types.h"
#include <stdexcept>

namespace nmea
{
	/*
	* BaseException class error message with sentence
	*/
	class NMEA_API BaseException : public std::runtime_error
	{
	public:
		explicit BaseException(const FString& sMessage, const FString& sSentence) :
			runtime_error(sMessage),
			m_sSentence(sSentence)
		{
		}

		virtual char const* sentence() const {
			return m_sSentence.c_str();
		}
	private:
		FString m_sSentence;
	};

	class NMEA_API SyntaxException : public BaseException
	{
	public:
		explicit SyntaxException(const FString& sMessage, const FString& sSentence) :
			BaseException(sMessage, sSentence)
		{
		};
	};

	template<typename T>
	class NMEA_API NumberException : public BaseException
	{
	public:
		explicit NumberException(const FString& sMessage, T oValue, const FString& sSentence) :
			BaseException(sMessage, sSentence),
			m_oValue(oValue)
		{
		};

		// TODO: show number in what() message
		virtual char const* what() const override {
			return BaseException::what();
		}

	private:
		T m_oValue;
	};
}