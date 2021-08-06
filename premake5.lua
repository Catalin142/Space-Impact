workspace "Space Impact"
	architecture "x86"
	configurations { "Debug", "Release" }
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Space Impact"
