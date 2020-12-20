format_version = "2.0"
front = jbox.panel { 
  graphics = { node = "Bg" },
  widgets = {
    jbox.device_name { graphics = { node = "deviceName" } },
    jbox.sequence_fader{
      graphics = { node = "onoffbypass" },
      handle_size = 0,
      value = "/custom_properties/builtin_onoffbypass",
    },
    jbox.analog_knob { 
      graphics = { node = "detail1" },
      value = "/custom_properties/Detail1"
    },
    jbox.analog_knob { 
      graphics = { node = "detail2" },
      value = "/custom_properties/Detail2"
     },
     jbox.analog_knob { 
      graphics = { node = "detail3" },
      value = "/custom_properties/Detail3"
     },
     jbox.analog_knob { 
      graphics = { node = "detail4" },
      value = "/custom_properties/Detail4"
     },
     jbox.analog_knob { 
      graphics = { node = "approximation" },
      value = "/custom_properties/Approximation"
     },
     jbox.sequence_fader {
      graphics = { node = "algorithm" },
      value = "/custom_properties/Algorithm"
     },
     
  }
}
back = jbox.panel { 
  graphics = { node = "Bg" },
  widgets = {
    jbox.placeholder {
      graphics = { node = "Placeholder" },
    },
    jbox.audio_output_socket {
      graphics = { node = "audioOutL" },
      socket = "/audio_outputs/audioOutL",
    },
    jbox.audio_output_socket {
      graphics = { node = "audioOutR" },
      socket = "/audio_outputs/audioOutR",
    },
    jbox.audio_input_socket {
      graphics = { node = "audioInL" },
      socket = "/audio_inputs/audioInL",
    },
    jbox.audio_input_socket {
      graphics = { node = "audioInR" },
      socket = "/audio_inputs/audioInR",
    },
    jbox.device_name {
      graphics = { node = "deviceName" },
    },
  },
}
folded_front = jbox.panel { 
  graphics = { node = "Bg" },
  widgets = {},
}
folded_back = jbox.panel { 
  graphics = { node = "Bg" },
  cable_origin = { node = "CableOrigin" },
  widgets = {},
}
