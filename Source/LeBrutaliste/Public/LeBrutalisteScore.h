// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include <vector>
#include <string>

/**
 * 
 */

enum ScoreCanal{
	SCORE_POINTS = 0,
	SCORE_BUILD_POINTS = 1,
};

struct pointSystem{
	int32 value;
	int32 scoreMin;
	int32 scoreMax;
	std::string scoreName;
};

class LEBRUTALISTE_API ALeBrutalisteScore
{
private:

	static std::vector<pointSystem*> score;

protected:

	bool multiplierChain;

	int32 currentMultiplier;

	int32 currentScore;

	int32 currentBP;
	
public:

	/*ALeBrutalisteScore();
	~ALeBrutalisteScore();*/

	static void ReinitScore(std::string scoreName);

	//notify the score counter that we gained score
	static void Gain(std::string scoreName, int32 ScoreGained);

	////notify the score counter that we lost score
	//static void Lose(ScoreCanal, int32 ScoreGained);

	//score getter
	static int32 GetScore(std::string scoreName);

	//score setter
	static void SetScore(std::string scoreName, int32 toSet);
	

	static void initScore(std::string scoreName, int32 scoreMax, int32 scoreMin, int32 defaultStartValue);

	static pointSystem* getPointSystem(std::string scoreName);


	////notify the score counter that a multiplier started
	//void multiplierStarted();

	////update the score counter with the desired number
	//void multiplierUpdate(int32 toAdd);

	////notify the score counter that the multiplier ended
	//void multiplierEnded();

	////notify the score counter that we gained score
	//void Gain(int32 ScoreGained);

	////notify the build points counter that we gained build points
	//void GainBP(int32 BPointsGained);

	////notify the score counter that we lost points
	//void LoseScore(int32);

	////notify the score counter that we lost build points
	//void LoseBP(int32 buildPointsLost);
	//
	////score getter
	//int32 GetScore();

	////Build points getter
	//int32 GetBP();

	////score setter
	//void SetScore(int32 toSet);

	////Build points setter
	//void SetBP(int32 toSet);
};