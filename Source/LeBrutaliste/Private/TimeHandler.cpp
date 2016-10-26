// Fill out your copyright notice in the Description page of Project Settings.

#include "LeBrutaliste.h"
#include "TimeHandler.h"

FDateTime TimeHandler::startTime[7] = { FDateTime(0) };

void TimeHandler::startTimer(TimeCanal canal)
{
	if (!isRunning(canal))
		startTime[(int)canal] = FDateTime::Now();
}

FTimespan TimeHandler::TimeElapsed(TimeCanal canal)
{
	if (isRunning(canal))
		return FDateTime::Now() - startTime[(int)canal];
	else
		return FTimespan(0);
}


int32 TimeHandler::TimeElapsedInMinutes(TimeCanal canal)
{
	return TimeElapsed(canal).GetMinutes();
}

int32 TimeHandler::TimeElapsedInSeconds(TimeCanal canal)
{
	return TimeElapsed(canal).GetSeconds();
}

int32 TimeHandler::TimeElapsedInMilliseconds(TimeCanal canal)
{
	return TimeElapsed(canal).GetMilliseconds();
}

void TimeHandler::StopTimer(TimeCanal canal)
{
	if (isRunning(canal))
		startTime[(int)canal] = FDateTime(0);
}

void TimeHandler::resetTimer(TimeCanal canal)
{
	if (isRunning(canal))
	{
		StopTimer(canal);
		startTimer(canal);
	}
}

bool TimeHandler::isRunning(TimeCanal canal)
{
	return startTime[(int)canal] != FDateTime(0);
}

bool TimeHandler::isInferiorTo(TimeCanal canal, float secCommaMillisec, int32 minutes)
{
	if (TimeElapsedInMinutes(canal) < minutes)
	{
		return true;
	}
	else if (TimeElapsedInMinutes(canal) == minutes)
	{
		if (TimeElapsedInSeconds(canal) < FGenericPlatformMath::FloorToInt(secCommaMillisec))
		{
			return true;
		}
		else if (TimeElapsedInSeconds(canal) == FGenericPlatformMath::FloorToInt(secCommaMillisec))
		{
			if (TimeElapsedInMilliseconds(canal) < FGenericPlatformMath::Frac(secCommaMillisec) * 1000)
				return true;
			else
				return false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool TimeHandler::isSuperiorTo(TimeCanal canal, float secCommaMillisec, int32 minutes)
{
	if (FGenericPlatformMath::Frac(secCommaMillisec) * 100 != TimeElapsedInMilliseconds(canal))
		return !isInferiorTo(canal, secCommaMillisec, minutes);
	else
		return false;
}
