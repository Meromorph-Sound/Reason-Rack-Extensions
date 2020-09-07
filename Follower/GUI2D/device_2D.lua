format_version = "2.0"
PANEL_HEIGHT=345

KNOB_HEIGHT=200
KNOB_WIDTH=200

BUTTON_HEIGHT=160
BUTTON_WIDTH=160

LAMP_HEIGHT=480

MARGIN=50



front = { 
	Bg = {
		{ path = "front" },
	},
	onoffbypass = {
      offset = {185,45},
      {path="Fader_Bypass_3frames", frames = 3},
    },
	deviceName = {
		offset = { 185, 215},
		{ path = "Tape_Horizontal_1frames", frames = 1 },
	},
	{
	 learningRate1 = {
      offset = { 700, 80 },
      { path = "Knob_01_63frames", frames = 63 },
    },
  	threshold1 = {
  		offset = { 900, 80 },
  		{ path = "Knob_01_63frames", frames = 63 },
  	},
  	rectification1 = {
  		offset = { 1100, 100 },
  		{ path = "Button_23_2frames", frames = 2},
  	},
  	rectificationDisplay1 =
  	{
  		offset = { 1260, 100 },
  		{ path = "Lamp_18_3frames", frames = 3},
  	},
    thresholdLED1 = {
      offset = { 1100, 20 },
      { path = "Bicolour_LED_3frames", frames = 3 }
    }
	},
	{
   learningRate2 = {
      offset = { 1500, 80 },
      { path = "Knob_01_63frames", frames = 63 },
    },
    threshold2 = {
      offset = { 1700, 80 },
      { path = "Knob_01_63frames", frames = 63 },
    },
    rectification2 = {
      offset = { 1900, 100 },
      { path = "Button_23_2frames", frames = 2},
    },
    rectificationDisplay2 =
    {
      offset = { 2060, 100 },
      { path = "Lamp_18_3frames", frames = 3},
    },
    thresholdLED2 = {
      offset = { 1900, 20 },
      { path = "Bicolour_LED_3frames", frames = 3 }
    }
  },
  {
   learningRate3 = {
      offset = { 2300, 80 },
      { path = "Knob_01_63frames", frames = 63 },
    },
    threshold3 = {
      offset = { 2500, 80 },
      { path = "Knob_01_63frames", frames = 63 },
    },
    rectification3 = {
      offset = { 2700, 100 },
      { path = "Button_23_2frames", frames = 2},
    },
    rectificationDisplay3 =
    {
      offset = { 2860, 100 },
      { path = "Lamp_18_3frames", frames = 3},
    },
    thresholdLED3 = {
      offset = { 2700, 20 },
      { path = "Bicolour_LED_3frames", frames = 3 }
    }
  }
}
back = { 
	Bg = {
		{ path = "back" },
	},
	Placeholder = {
		offset = { 100, 100 },
		{ path = "Placeholder" },
	},
	SignalInputSocket1 = {
		offset = {500,100},
		{ path = "SharedAudioJack", frames = 3},
	},
	EnvelopeOutputSocket1 = {
		offset = {700,100},
		{ path = "SharedAudioJack", frames = 3},
	},
	GateOutputSocket1 = {
		offset = {900,100},
		{ path = "SharedCVJack", frames = 3},
	},
	SignalInputSocket2 = {
    offset = {1105,100},
    { path = "SharedAudioJack", frames = 3},
  },
  EnvelopeOutputSocket2 = {
    offset = {1300,100},
    { path = "SharedAudioJack", frames = 3},
  },
  GateOutputSocket2 = {
    offset = {1510,100},
    { path = "SharedCVJack", frames = 3},
  },
  SignalInputSocket3 = {
    offset = {1705,100},
    { path = "SharedAudioJack", frames = 3},
  },
  EnvelopeOutputSocket3 = {
    offset = {1905,100},
    { path = "SharedAudioJack", frames = 3},
  },
  GateOutputSocket3 = {
    offset = {2110,100},
    { path = "SharedCVJack", frames = 3},
  },
  deviceName = {
    offset = { 3280, 50},
    { path = "Tape_Horizontal_1frames", frames = 1 },
  },
  }
folded_front = { 
	Bg = {
		{ path = "Panel_Folded_Front" },
	},
}
folded_back = { 
	Bg = {
		{ path = "Panel_Folded_Back" },
	},
	CableOrigin = {
		offset = { 1885, 75 },
	},
}
