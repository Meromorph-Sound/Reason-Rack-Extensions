format_version = "2.0"
PANEL_HEIGHT=345

KNOB_HEIGHT=200
KNOB_WIDTH=200

BUTTON_HEIGHT=160
BUTTON_WIDTH=160

LAMP_HEIGHT=270

MARGIN=50

function centre(height)
	return (PANEL_HEIGHT-height)//2
end

function fromBottom(height)
  return PANEL_HEIGHT-(MARGIN+height)
end


function xOf(nKnobs,nMargins) 
  return 1000+nKnobs*KNOB_WIDTH + nMargins*MARGIN
 end


front = { 
	Bg = {
		{ path = "FollowerFrontPanel" },
	},
	onoffbypass = {
      offset = {185,45},
      {path="Fader_Bypass_3frames", frames = 3},
    },
	deviceName = {
		offset = { 185, 215},
		{ path = "Tape_Horizontal_1frames", frames = 1 },
	},
	learningRate = {
		offset = { 1000, centre(KNOB_HEIGHT) },
		{ path = "Knob_01_63frames", frames = 63 },
	},
	threshold = {
		offset = { xOf(1,0), centre(KNOB_HEIGHT) },
		{ path = "Knob_01_63frames", frames = 63 },
	},
	rectification = {
		offset = { xOf(2,2),centre(BUTTON_HEIGHT) },
		{ path = "Button_23_2frames", frames = 2},
	},
	rectificationDisplay =
	{
		offset = { xOf(2,2) + BUTTON_WIDTH, centre(LAMP_HEIGHT/3) },
		{ path = "Lamp_18_3frames", frames = 3},
	}
}
back = { 
	Bg = {
		{ path = "Panel_Back_1U" },
	},
	Placeholder = {
		offset = { 100, 100 },
		{ path = "Placeholder" },
	},
	SignalInputSocket = {
		offset = {1000,100},
		{ path = "SharedAudioJack", frames = 3},
	},
	EnvelopeOutputSocket = {
		offset = {1200,100},
		{ path = "SharedAudioJack", frames = 3},
	},
	GateOutputSocket = {
		offset = {1400,100},
		{ path = "SharedAudioJack", frames = 3},
	}
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
