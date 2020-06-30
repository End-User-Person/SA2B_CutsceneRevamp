// CutsceneRevamp.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <SA2ModLoader.h>
#include <SA2Functions.h>
#include <MemAccess.h>
#include <stdint.h>
#include <IniFile.hpp>

#define ReplaceEV(a,b) helperFunctions.ReplaceFile("resource\\gd_PC\\EVENT\\" a ".prs", "resource\\gd_PC\\EVENT\\" b ".prs");
#define ReplacePAK(a,b) helperFunctions.ReplaceFile("resource\\gd_PC\\EVENT\\prs\\" a ".pak", "resource\\gd_PC\\EVENT\\prs\\" b ".pak");
#define ReplaceEVM(a,b) helperFunctions.ReplaceFile("resource\\gd_PC\\EVENT\\" a ".bin", "resource\\gd_PC\\EVENT\\" b ".bin");
#define ReplaceSFX(a,b) helperFunctions.ReplaceFile("resource\\gd_PC\\EVENT\\MLT\\e0000\\" a, "resource\\gd_PC\\EVENT\\MLT\\e0000\\" b);
#define ReplaceSFD(a,b) helperFunctions.ReplaceFile("resource\\gd_PC\\" a ".sfd", "resource\\gd_PC\\" b ".sfd");
#define ReplaceADX(a,b) helperFunctions.ReplaceFile("resource\\gd_PC\\ADX\\" a ".adx", "resource\\gd_PC\\ADX\\" b ".adx");
#define ReplaceFMV(a,b) helperFunctions.ReplaceFile("resource\\gd_PC\\EVENT\\" a ".sfd", "resource\\gd_PC\\EVENT\\" b ".sfd");

static bool EnableDCIntro = true;
static bool WidescreenRatio = true;
static bool SA2BE0000Anims = false;
static bool TrialAudioTiming = false;
static bool TrialSonic = false;
static bool AmyEyeliner = false;

FunctionPointer(void, sub_5F8D90, (int a1, int a2, int a3, int a4, float a5, int a6), 0x5F8D90);

StoryEntry IntroStorySequence[] = {
	{ StoryEntryType_Event, Characters_Sonic, LevelIDs_BasicTest, 350, -1, -1, -1 },
	{ StoryEntryType_End }
};

void Init_IntroSequence()
{
	WriteData((StoryEntry**)0x0458728, IntroStorySequence);
}

void do169MovieEffects(int a1, int a2, int a3, int a4, float a5, int a6) {
	sub_5F8D90(-107, 0, 862, 480, a5, a6);
}

void Init_do169MovieEffects()
{
	if (HorizontalResolution / 640.0 / (VerticalResolution / 480.0) > 1.0) {
		WriteData<1>((int*)0x5FB4FE, 0x8B);
		WriteCall((void*)0x005FF311, do169MovieEffects);
	}
}

extern "C"
{

	HMODULE NOBATTLE = GetModuleHandle(L"nobattle");

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };

	__declspec(dllexport) void _cdecl Init(const char *path, const HelperFunctions &helperFunctions)

	{

		const IniFile *config = new IniFile(std::string(path) + "\\config.ini");
		EnableDCIntro = config->getBool("Options", "EnableDCIntro", true);
		WidescreenRatio = config->getBool("Options", "Force169", true);
		SA2BE0000Anims = config->getBool("Options", "SA2BAnims", false);
		TrialAudioTiming =  config->getBool("Options", "TrialAudio", false);
		TrialSonic =  config->getBool("Options", "TrialSonic", false);
		AmyEyeliner =  config->getBool("Options", "AmyEyeliner", false);
		delete config;

		if (EnableDCIntro && !HaveBattleDLC || NOBATTLE)
		{
			Init_IntroSequence();
		}

		if (EnableDCIntro)
		{
			Init_IntroSequence();
		}

		if (WidescreenRatio)
			{
				Init_do169MovieEffects();
				ReplaceSFD("op360us", "op360us_w");
				ReplaceSFD("op360jp", "op360jp_w");
				ReplaceSFD("e206fsp", "e206fsp_w");
			}

		if (SA2BE0000Anims)
		{
			ReplaceEVM("e0000motion", "e0000motion_sa2b");
		}

		//else
		//{
		//	ReplaceSFX("e0000004000.mid", "e0000004000_fix.mid");
		//}

		if (TrialAudioTiming)
		{
			ReplaceADX("e000_sng", "e000_sng_trial");
			ReplaceEV("e0000_1", "e0000_1_trial");
			ReplaceEV("e0000_2", "e0000_2_trial");
			ReplaceEV("e0000_3", "e0000_3_trial");
			ReplaceEV("e0000_4", "e0000_4_trial");
			ReplaceEV("e0000_5", "e0000_5_trial");
			ReplaceEV("e0000_j", "e0000_j_trial");
		}

		if (TrialSonic)
		{
			ReplaceEV("e0000", "e0000_trial");
			ReplaceEV("e0002", "e0002_trial");
			ReplacePAK("e0002texture", "e0002texture_trial");
			ReplaceEV("e0006", "e0006_trial");
			ReplaceEV("e0011", "e0011_trial");
			ReplaceEV("e0015", "e0015_trial");
			ReplaceEV("e0016", "e0016_trial");
			ReplaceEV("e0017", "e0017_trial");
			ReplaceEV("e0019", "e0019_trial");
			ReplaceEV("e0021", "e0021_trial");
			ReplaceEV("e0022", "e0022_trial");
			ReplaceEV("e0025", "e0025_trial");
			ReplaceEV("e0026", "e0026_trial");
			ReplaceEV("e0027", "e0027_trial");
			ReplacePAK("e0027texture", "e0027texture_trial");
			ReplaceEV("e0107", "e0107_trial");
			ReplacePAK("e0107texture", "e0107texture_trial");
			ReplaceEV("e0118", "e0118_trial");
			ReplaceEV("e0123", "e0123_trial");
			ReplaceEV("e0128", "e0128_trial");
			ReplaceEV("e0130", "e0130_trial");
			ReplacePAK("e0130texture", "e0130texture_trial");
			ReplaceEV("e0201", "e0201_trial");
			ReplacePAK("e0201texture", "e0201texture_trial");
			ReplaceEV("e0203", "e0203_trial");
			ReplaceEV("e0205", "e0205_trial");
			ReplacePAK("e0205texture", "e0205texture_trial");
			ReplaceEV("e0206", "e0206_trial");
			ReplacePAK("e0206texture", "e0206texture_trial");
			ReplaceEV("e0207", "e0207_trial");
			ReplacePAK("e0207texture", "e0207texture_trial");
			ReplaceEV("e0208", "e0208_trial");
			ReplaceEV("e0210", "e0210_trial");
			ReplacePAK("e0210texture", "e0210texture_trial");
			ReplaceEV("e0360", "e0360_trial");
			ReplacePAK("e0360texture", "e0360texture_trial");
			ReplaceEV("e0361", "e0361_trial");
			ReplacePAK("e0361texture", "e0361texture_trial");
			ReplaceFMV("e0524_m", "e0524_m_trial");
		}

		if (AmyEyeliner)
		{
			ReplaceEV("e0004", "e0004_eyeliner");
			ReplaceEV("e0005", "e0005_eyeliner");
			ReplaceEV("e0006", "e0006_eyeliner");
			ReplaceEV("e0011", "e0011_eyeliner");
			ReplaceEV("e0014", "e0014_eyeliner");
			ReplaceEV("e0016", "e0016_eyeliner");
			ReplaceEV("e0017", "e0017_eyeliner");
			ReplaceEV("e0019", "e0019_eyeliner");
			ReplaceEV("e0021", "e0021_eyeliner");
			ReplaceEV("e0025", "e0025_eyeliner");
			ReplaceEV("e0028", "e0028_eyeliner");
			ReplaceEV("e0113", "e0113_eyeliner");
			ReplaceEV("e0123", "e0123_eyeliner");
			ReplaceEV("e0128", "e0128_eyeliner");
			ReplaceEV("e0203", "e0203_eyeliner");
			ReplaceEV("e0204", "e0204_eyeliner");
			ReplaceEV("e0210", "e0210_eyeliner");
		}

		if (TrialSonic && AmyEyeliner)
		{
			ReplaceEV("e0006", "e0006_mix");
			ReplaceEV("e0011", "e0011_mix");
			ReplaceEV("e0016", "e0016_mix");
			ReplaceEV("e0017", "e0017_mix");
			ReplaceEV("e0019", "e0019_mix");
			ReplaceEV("e0021", "e0021_mix");
			ReplaceEV("e0025", "e0025_mix");
			ReplaceEV("e0123", "e0123_mix");
			ReplaceEV("e0128", "e0128_mix");
			ReplaceEV("e0203", "e0203_mix");
			ReplaceEV("e0210", "e0210_mix");
		}
	}
}