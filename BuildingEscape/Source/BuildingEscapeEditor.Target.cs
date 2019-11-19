// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class BuildingEscapeEditorTarget : TargetRules
{
	public BuildingEscapeEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		bUseUnityBuild = false; // Added in Course Lecture 70
		bUsePCHFiles = false; // Added in Course Lecture 70

		ExtraModuleNames.AddRange( new string[] { "BuildingEscape" } );
	}
}
