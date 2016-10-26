// Fill out your copyright notice in the Description page of Project Settings.

#include "LeBrutaliste.h"
#include "LeBrutalisteScore.h"

//attention valeurs de test (multiplier devrait etre a 0 et false de base)
//ALeBrutalisteScore::ALeBrutalisteScore() : currentBP(0), currentScore(0), currentMultiplier(0), multiplierChain(false) {};

std::vector<pointSystem*> ALeBrutalisteScore::score = std::vector<pointSystem*>();

void ALeBrutalisteScore::Gain(std::string scoreName, int32 ScoreGained)
{
	pointSystem* scoreSystem = getPointSystem(scoreName);

	if (scoreSystem->value + ScoreGained < scoreSystem->scoreMin)
		scoreSystem->value = scoreSystem->scoreMin;
	else if (scoreSystem->value + ScoreGained > scoreSystem->scoreMax)
		scoreSystem->value = scoreSystem->scoreMax;
	else
		scoreSystem->value += ScoreGained;
}

//void ALeBrutalisteScore::Gain(ScoreCanal canal, int32 ScoreLost)
//{
//	if (score[(int)canal] - ScoreLost < 0)
//		score[(int)canal] = 0;
//	else if (canal == SCORE_BUILD_POINTS && score[(int)canal] - ScoreGained > 10000)
//		score[(int)canal] = 10000;
//	else
//		score[(int)canal] -= ScoreGained;
//}

int32 ALeBrutalisteScore::GetScore(std::string scoreName)
{
	return getPointSystem(scoreName)->value;
}

void ALeBrutalisteScore::SetScore(std::string scoreName, int32 newScore)
{
	getPointSystem(scoreName)->value = newScore;
}

pointSystem* ALeBrutalisteScore::getPointSystem(std::string scoreName)
{
	for (pointSystem* currentSystem : score)
	{
		if (currentSystem->scoreName == scoreName)
			return currentSystem;
	}
	return NULL;
}

void ALeBrutalisteScore::initScore(std::string scoreName, int32 scoreMax, int32 scoreMin, int32 defaultStartValue)
{
	pointSystem* nouveauScore = new pointSystem();
	nouveauScore->value = defaultStartValue;
	nouveauScore->scoreMin = scoreMin;
	nouveauScore->scoreMax = scoreMax;
	nouveauScore->scoreName = scoreName;
	score.push_back(nouveauScore);
}

void ALeBrutalisteScore::ReinitScore(std::string scoreName)
{
	SetScore(scoreName, 0);
}

//void ALeBrutalisteScore::multiplierStarted()
//{
//	multiplierChain = true;
//}
//
////Allows "jumps" in multiplier chains. Not sure if it will be needed
//void ALeBrutalisteScore::multiplierUpdate(int32 toAdd)
//{
//	currentMultiplier += toAdd;
//}
//
//
//void ALeBrutalisteScore::multiplierEnded()
//{
//	multiplierChain = false;
//}
//
//
//void ALeBrutalisteScore::Gain(int32 ScoreGained)
//{
//	if (multiplierChain)
//	{
//		currentMultiplier += 1;
//		currentScore = currentScore + ScoreGained * currentMultiplier;
//	}
//	else
//		currentScore += ScoreGained;
//}
//
//int32 ALeBrutalisteScore::GetScore()
//{
//	return currentScore;
//}
//
//void ALeBrutalisteScore::SetScore(int32 toSet)
//{
//	currentScore = toSet;
//}
//
//void ALeBrutalisteScore::GainBP(int32 BuildPointsGained)
//{
//	currentBP += BuildPointsGained;
//	if (currentBP >= 10000)
//		currentBP = 10000;
//}
//
//int32 ALeBrutalisteScore::GetBP()
//{
//	return currentBP;
//}
//
//void ALeBrutalisteScore::SetBP(int32 toSet)
//{
//	currentBP = toSet;
//}
//
//void ALeBrutalisteScore::LoseScore(int32 PointsLost)
//{
//	currentScore -= PointsLost;
//	if (currentScore < 0)
//		currentScore = 0;
//}
//
//void ALeBrutalisteScore::LoseBP(int32 buildPointsLost)
//{
//	currentBP -= buildPointsLost;
//	if (currentBP < 0)
//		currentBP = 0;
//}
//
//
//ALeBrutalisteScore::~ALeBrutalisteScore()
//{
//}
