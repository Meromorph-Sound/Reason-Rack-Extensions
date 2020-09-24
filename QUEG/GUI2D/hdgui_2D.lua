format_version = "2.0"
front = jbox.panel { 
	graphics = {
		node = "Bg",
	},
	widgets = {
		jbox.device_name {
			graphics = { node = "deviceName" },
		},
		jbox.sequence_fader{
      			graphics = { node = "onoffbypass" },
      			handle_size = 0,
      			value = "/custom_properties/builtin_onoffbypass",
    },
    jbox.custom_display {
      graphics = {
        node = "controller1" 
      },
      display_width_pixels = 400,
      display_height_pixels = 400,
      values = { "/custom_properties/x1", "/custom_properties/y1" },
      draw_function = "drawController",
      gesture_function = "handleControllerInput"
    }
	},
}
back = jbox.panel { 
	graphics = {
		node = "Bg",
	},
	widgets = {
		jbox.placeholder {
			graphics = { node = "Placeholder" },
		},
		jbox.audio_input_socket {
			graphics = { node = "SignalInput1" },
			socket = "/audio_inputs/in1",
		},
               jbox.audio_input_socket {
                        graphics = { node = "SignalInput2" },
                        socket = "/audio_inputs/in2",
                },
               jbox.audio_input_socket {
                        graphics = { node = "SignalInput3" },
                        socket = "/audio_inputs/in3",
                },
               jbox.audio_input_socket {
                        graphics = { node = "SignalInput4" },
                        socket = "/audio_inputs/in4",
                },
		jbox.audio_output_socket {
			graphics = { node = "SignalOutputA" },
			socket = "/audio_outputs/outA",
		},
               jbox.audio_output_socket {
                        graphics = { node = "SignalOutputB" },
                        socket = "/audio_outputs/outB",
                },
               jbox.audio_output_socket {
                        graphics = { node = "SignalOutputC" },
                        socket = "/audio_outputs/outC",
                },
               jbox.audio_output_socket {
                        graphics = { node = "SignalOutputD" },
                        socket = "/audio_outputs/outD",
                },
    jbox.device_name {
      graphics = { node = "deviceName" },
    },
	},
}
folded_front = jbox.panel { 
	graphics = {
		node = "Bg",
	},
	widgets = {
	},
}
folded_back = jbox.panel { 
	graphics = {
		node = "Bg",
	},
	cable_origin = {
		node = "CableOrigin",
	},
	widgets = {
	},
}
