format_version = "2.0"
front = jbox.panel { 
  graphics = { node = "Bg" },
  widgets = {
    jbox.device_name {
      graphics = { node = "deviceName" },
    },
    jbox.sequence_fader{
      graphics = { node = "onoffbypass" },
      handle_size = 0,
      value = "/custom_properties/builtin_onoffbypass",
    }
  }
}
back = jbox.panel { 
  graphics = { node = "Bg" },
  widgets = {
    jbox.placeholder {
      graphics = { node = "Placeholder" },
    },
    jbox.audio_output_socket {
      graphics = { node = "audioOut" },
      socket = "/audio_outputs/audioOut",
    },
    jbox.cv_output_socket {
      graphics = { node = "cvOut" },
      socket = "/cv_outputs/cvOut",
    },
    jbox.cv_input_socket {
      graphics = { node = "cvIn" },
      socket = "/cv_outputs/cvIn",
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
