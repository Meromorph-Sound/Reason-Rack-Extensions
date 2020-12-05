format_version = "2.0"


front = {

	Surface_Bg = {
		{ path = "Background_VerySimpleSampler" },
	},

	-------------------------------------------
	-------------------------------------------
	---  rootkey and fine tune
	-------------------------------------------
	
	Surface_RootKeyOffset = {
		offset = {281 * 5, 46 * 5 },
		{ path = "Knob_Green", frames = 63}
	},

	Surface_TuneCents = {
		offset = {281 * 5, 92 * 5 },
		{ path = "Knob_Green", frames = 63}
	},

	
	
	-------------------------------------------
	-------------------------------------------
	--- Play Start/End 
	-------------------------------------------
	Surface_PlayStart = {
		offset = { 500 * 5, 57 * 5 },
		{ path = "Knob_Red", frames = 63 }
	},
	
	Surface_PlayEnd = {
		offset = { 580 * 5, 57 * 5 },
		{ path = "Knob_Red", frames = 63 }
	},
	
	
	-------------------------------------------
	-------------------------------------------
	--- Loopery 
	-------------------------------------------

	Surface_LoopMode = {
		offset = { 414 * 5, 97 * 5 },
		{ path = "Knob_LoopMode", frames = 63 }
	},
	
	Surface_LoopStart = {
		offset = { 499 * 5, 93 * 5 },
		{ path = "Knob_Blue", frames = 63 }
	},
	
	Surface_LoopEnd = {
		offset = { 579 * 5, 93 * 5 },
		{ path = "Knob_Blue", frames = 63 }
	},
	
	
	-------------------------------------------
	-------------------------------------------
	--- Level 
	-------------------------------------------
	Surface_ZoneLevel = {
		offset = { 650 * 5, 70 * 5 },
		{ path = "Knob_Level", frames = 63 }
	},
	
	-------------------------------------------
	-------------------------------------------
	--- Edit sample
	-------------------------------------------
	Surface_EditSample = {
		offset = { 60 * 5, 35 * 5 },
		{ path = "PushButton", frames = 2 }
	},
	
	-------------------------------------------
	-------------------------------------------
	--- Delete sample
	-------------------------------------------
	Surface_DeleteSample = {
		offset = { 60 * 5, 80 * 5 },
		{ path = "PushButton", frames = 2 }
	},
	
	
	-------------------------------------------
	-------------------------------------------
	--- On/Off Button
	-------------------------------------------
	Surface_DeviceOn = {
		offset = { 30*5, 4*5 },
		{ path = "Button_OnOff", frames = 4 }
	},
	
	-------------------------------------------
	-------------------------------------------
	---  Displays
	-------------------------------------------
	{
		offset = {47*5, 131*5},
		{
			Surface_ZoneSelectorDisplay = {
				offset = { 0, 0 },
				{ path = "Background_ZoneSelect_Empty"},
			},
			Surface_Zone1 = {
				offset = { 0, 0 },
				{ size = { 32 * 5, 260 } },
			},
			Surface_Zone2 = {
				offset = { 32 * 5, 0 },
				{ size = { 33 * 5, 260 } },
			},
			Surface_Zone3 = {
				offset = { (32 + 33) * 5, 0 },
				{ size = { 25 * 5, 260 } },
			},
			Surface_Zone4 = {
				offset = { (32 + 33 + 25) * 5, 0 },
				{ size = { 31 * 5, 260 } },
			}
		},
	},

	Surface_TextDisplay = {
		offset = {268*5, 129*5},
		{path = "Background_TextDisplay_Empty"},
	},
	
	-------------------------------------------
	-------------------------------------------
	--- Patch settings
	-------------------------------------------
	Surface_PatchName = {
		offset = { 127*5, 10*5 },
		{ path = "PatchNameSurface" },
	},
	{
		offset = { 62*5, 7*5 },
		Surface_PatchBrowseGroup = {
			offset = { 0, 0 },
			{ path = "PatchBrowseGroup" },
		}
	},
	{
		offset =  { 311 * 5, 11 * 5 },
		Surface_SampleBrowseGroup = {
			offset = { 0, 0 },
			{ path = "SampleBrowseGroup" },
		},
	},
	Surface_TapeVert = {
		offset = { 430*5, 13*5 },
		{ path = "TapeHorz" }
	},
}



front = {
  Bg = { {path = "frontPanel"} },
  onoffbypass = {
      offset = {185,45},
      {path="Fader_Bypass_3frames", frames = 3 },
    },
  deviceName = {
    offset = { 185, 215},
    { path = "TapeHorz", frames = 1 },
  }
}
back = {
  Bg = { {path = "backPanel"} },
  Placeholder = {
    offset = { 100, 100 },
    { path = "Placeholder" },
  },
  deviceName = {
    offset = { 3280, 50},
    { path = "TapeHorz", frames = 1 },
  },
  cvIn = {
    offset = { 2000,100 },
    { path = "SharedCVJack", frames = 1 }
  },
  cvOut = {
    offset = { 2200,100 },
    { path = "SharedCVJack", frames = 1 }
  },
  audioOut = {
    offset = { 2400,100 },
    { path = "SharedAudioJack", frames = 1 }
  },
}




folded_front = {
	Bg = {{ path = "Panel_Folded_Front" }}
}
folded_back = { 
  Bg = {{ path = "Panel_Folded_Back" }},
  CableOrigin = { offset = { 1885, 75 }}
}





