format_version = "2.0"



front = {
  Bg = { {path = "front1U"} },
  onoffbypass = {
      offset = {185,50},
      {path="Fader_Bypass_3frames", frames = 3 },
    },
  deviceName = {
    offset = { 3200, 250},
    { path = "TapeHorz", frames = 1 },
  },
  inMode = {
    offset = { 1000, 120 },
    { path = "DoubleLamp_4frames", frames = 4 }  
  },
  outMode = {
    offset = { 1200, 120 },
    { path = "DoubleLamp_4frames", frames = 4 }  
  },
  zero = {
    offset = { 1500, 85 },
    { path = "Button_63_2frames", frames = 2 }
  },
  growthrate = {
    offset = { 1850, 50 },
    { path = "Knob_63frames", frames = 63 }
  },
  inputscale = {
    offset = { 2100, 50 },
    { path = "Knob_63frames", frames = 63 }
  },
  barrier = {
    offset = { 2350, 50 },
    { path = "Knob_63frames", frames = 63 }
  },
  amplitude = {
    offset = { 2600, 50 },
    { path = "Knob_63frames", frames = 63 }
  },
  smoothing = {
    offset = { 2950, 50 },
    { path = "Knob_63frames", frames = 63 }
  },
  smooth = {
    offset = { 2850, 55 },
    { path = "Button_53_2frames", frames = 2 }
  }
}
back = {
  Bg = { {path = "backPanel"} },
  Placeholder = {
    offset = { 2000, 100 },
    { path = "Placeholder" },
  },
  deviceName = {
    offset = { 50, 220 },
    { path = "TapeHorz", frames = 1 },
  },
  cvIn = {
    offset = { 1200,130 },
    { path = "SharedCVJack", frames = 3 }
  },
  cvOut = {
    offset = { 1800,130 },
    { path = "SharedCVJack", frames = 3 }
  },
  audioIn = {
    offset = { 1000,120 },
    { path = "SharedAudioJack", frames = 3 }
  },
  audioOut = {
    offset = { 1600,120 },
    { path = "SharedAudioJack", frames = 3 }
  },
}




folded_front = {
	Bg = {{ path = "Panel_Folded_Front" }}
}
folded_back = { 
  Bg = {{ path = "Panel_Folded_Back" }},
  CableOrigin = { offset = { 1885, 75 }}
}





