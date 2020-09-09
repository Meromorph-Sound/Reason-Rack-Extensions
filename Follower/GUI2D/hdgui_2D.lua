format_version = "2.0"
front = jbox.panel { 
	graphics = {
		node = "Bg",
	},
	widgets = {
		jbox.analog_knob {
			graphics = { node = "learningRate1" },
			value = "/custom_properties/learningRate1",
		},
		jbox.analog_knob {
			graphics = { node = "threshold1" },
			value = "/custom_properties/threshold1",
		},
		jbox.toggle_button {
			graphics = { node = "rectification1" },
			value = "/custom_properties/rectification1",
		},
		jbox.sequence_meter {
			graphics = { node="rectificationDisplay1" },
			value = "/custom_properties/rectificationDisplay1",
		},
		jbox.sequence_meter {
		  graphics = { node="gateLED1" },
		  value = "/custom_properties/gateCV1",
		},
		jbox.analog_knob {
      graphics = { node = "learningRate2" },
      value = "/custom_properties/learningRate2",
    },
    jbox.analog_knob {
      graphics = { node = "threshold2" },
      value = "/custom_properties/threshold2",
    },
    jbox.toggle_button {
      graphics = { node = "rectification2" },
      value = "/custom_properties/rectification2",
    },
    jbox.sequence_meter {
      graphics = { node="rectificationDisplay2" },
      value = "/custom_properties/rectificationDisplay2",
    },
    jbox.sequence_meter {
      graphics = { node="gateLED2" },
      value = "/custom_properties/gateCV2",
    },
		jbox.device_name {
			graphics = { node = "deviceName" },
		},
		jbox.sequence_fader{
      graphics = { node = "onoffbypass" },
      handle_size = 0,
      value = "/custom_properties/builtin_onoffbypass",
    },
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
			graphics = { node = "SignalLeftSocket1" },
			socket = "/audio_inputs/signalleft1",
		},
		jbox.audio_input_socket {
      graphics = { node = "SignalRightSocket1" },
      socket = "/audio_inputs/signalright1",
    },
		jbox.audio_output_socket {
			graphics = { node = "EnvelopeLeftSocket1" },
			socket = "/audio_outputs/envelopeleft1",
		},
		jbox.audio_output_socket {
      graphics = { node = "EnvelopeRightSocket1" },
      socket = "/audio_outputs/enveloperight1",
    },
		jbox.cv_output_socket {
			graphics = { node = "GateOutputSocket1" },
			socket = "/cv_outputs/gate1",
		},
		jbox.audio_input_socket {
      graphics = { node = "SignalLeftSocket2" },
      socket = "/audio_inputs/signalleft2",
    },
    jbox.audio_input_socket {
      graphics = { node = "SignalRightSocket2" },
      socket = "/audio_inputs/signalright2",
    },
    jbox.audio_output_socket {
      graphics = { node = "EnvelopeLeftSocket2" },
      socket = "/audio_outputs/envelopeleft2",
    },
    jbox.audio_output_socket {
      graphics = { node = "EnvelopeRightSocket2" },
      socket = "/audio_outputs/enveloperight2",
    },
    jbox.cv_output_socket {
      graphics = { node = "GateOutputSocket2" },
      socket = "/cv_outputs/gate2",
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
