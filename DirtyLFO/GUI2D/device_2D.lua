format_version = "2.0"



front = {
  Bg = { {path = "frontPanel"} },
  onoffbypass = {
      offset = {185,45},
      {path="Fader_Bypass_3frames", frames = 3 },
    },
  deviceName = {
    offset = { 185, 215},
    { path = "TapeHorz", frames = 1 },
  },
  growthrate = {
    offset = { 600, 100 },
    { path = "Knob_63frames", frames = 63 }
  },
  barrier = {
    offset = { 800, 100 },
    { path = "Knob_63frames", frames = 63 }
  },
  inputscale = {
    offset = { 1000, 100 },
    { path = "Knob_63frames", frames = 63 }
  },
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
  audioIn = {
    offset = { 2400,100 },
    { path = "SharedAudioJack", frames = 1 }
  },
  audioOut = {
    offset = { 2600,100 },
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





