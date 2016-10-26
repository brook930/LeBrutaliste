// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

enum TimeCanal{
	Time1 = 0,
	Time2 = 1,
	Time3 = 2,
	Time4 = 3,
	Time5 = 4,
	Time6 = 5,
	Time7 = 6,
};

/**
 * 
 */
class LEBRUTALISTE_API TimeHandler
{
private:

	static FDateTime startTime[7];

public:

	static void startTimer(TimeCanal);
	static FTimespan TimeElapsed(TimeCanal);
	static int32 TimeElapsedInMinutes(TimeCanal);
	static int32 TimeElapsedInSeconds(TimeCanal);
	static int32 TimeElapsedInMilliseconds(TimeCanal);
	static void StopTimer(TimeCanal);
	static void resetTimer(TimeCanal);
	static bool isRunning(TimeCanal);

	static bool isInferiorTo(TimeCanal, float, int32 minutes = 0);
	static bool isSuperiorTo(TimeCanal, float, int32 minutes = 0);
};
