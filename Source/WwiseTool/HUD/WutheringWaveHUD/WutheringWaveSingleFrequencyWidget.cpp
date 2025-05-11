﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "WutheringWaveSingleFrequencyWidget.h"

#include "Components/ProgressBar.h"



void UWutheringWaveSingleFrequencyWidget::SetFrequency(float Frequency)
{
	if(FrequencyPro == nullptr)
		return;
	FrequencyPro->SetPercent(Frequency);
}
