// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#ifndef __LEBRUTALISTE_H__
#define __LEBRUTALISTE_H__

#define DEBUGLOG(text)\
DEBUGLOGFULL(-1, 15.0f, FColor::Red, text);

#define DEBUGLOGINT(num)\
DEBUGLOG(FString::FromInt(num));

#define DEBUGLOGFLOAT(floatNum)\
DEBUGLOG(FString::SanitizeFloat(floatNum));

#define DEBUGLOGFULL(keyCode, displayTime, color, text)\
GEngine->AddOnScreenDebugMessage(keyCode, displayTime, color, text);

#include "Engine.h"
				   
#endif
