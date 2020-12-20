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
  detail1 = {
    offset = { 1850, 50 },
    { path = "Knob_63frames", frames = 63 }
  },
  detail2 = {
    offset = { 2100, 50 },
    { path = "Knob_63frames", frames = 63 }
  },
  detail3 = {
    offset = { 2350, 50 },
    { path = "Knob_63frames", frames = 63 }
  },
  detail4 = {
    offset = { 2600, 50 },
    { path = "Knob_63frames", frames = 63 }
  },
  approximation = {
    offset = { 2850, 50 },
    { path = "Knob_63frames", frames = 63 }
  },
  algorithm = {
    offset = { 3100, 55 },
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
  audioInL = {
    offset = { 1000,100 },
    { path = "SharedAudioJack", frames = 3 }
  },
  audioOutL = {
    offset = { 1000,200 },
    { path = "SharedAudioJack", frames = 3 }
  },
    audioInR = {
    offset = { 1400,100 },
    { path = "SharedAudioJack", frames = 3 }
  },
  audioOutR = {
    offset = { 1400,200 },
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





