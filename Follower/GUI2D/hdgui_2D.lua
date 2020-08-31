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
