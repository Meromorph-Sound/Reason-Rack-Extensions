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
		  graphics = { node="thresholdLED1" },
		  value = "/custom_properties/thresholdLED1",
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
      graphics = { node="thresholdLED2" },
      value = "/custom_properties/thresholdLED2",
    },
    jbox.analog_knob {
      graphics = { node = "learningRate3" },
      value = "/custom_properties/learningRate3",
    },
    jbox.analog_knob {
      graphics = { node = "threshold3" },
      value = "/custom_properties/threshold3",
    },
    jbox.toggle_button {
      graphics = { node = "rectification3" },
      value = "/custom_properties/rectification3",
    },
    jbox.sequence_meter {
      graphics = { node="rectificationDisplay3" },
      value = "/custom_properties/rectificationDisplay3",
    },
    jbox.sequence_meter {
      graphics = { node="thresholdLED3" },
      value = "/custom_properties/thresholdLED3",
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
			graphics = { node = "SignalInputSocket1" },
			socket = "/audio_inputs/signal1",
		},
		jbox.audio_output_socket {
			graphics = { node = "EnvelopeOutputSocket1" },
			socket = "/audio_outputs/envelope1",
		},
		jbox.cv_output_socket {
			graphics = { node = "GateOutputSocket1" },
			socket = "/cv_outputs/gate1",
		},
		jbox.audio_input_socket {
      graphics = { node = "SignalInputSocket2" },
      socket = "/audio_inputs/signal2",
    },
    jbox.audio_output_socket {
      graphics = { node = "EnvelopeOutputSocket2" },
      socket = "/audio_outputs/envelope2",
    },
    jbox.cv_output_socket {
      graphics = { node = "GateOutputSocket2" },
      socket = "/cv_outputs/gate2",
    },
    jbox.audio_input_socket {
      graphics = { node = "SignalInputSocket3" },
      socket = "/audio_inputs/signal3",
    },
    jbox.audio_output_socket {
      graphics = { node = "EnvelopeOutputSocket3" },
      socket = "/audio_outputs/envelope3",
    },
    jbox.cv_output_socket {
      graphics = { node = "GateOutputSocket3" },
      socket = "/cv_outputs/gate3",
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
