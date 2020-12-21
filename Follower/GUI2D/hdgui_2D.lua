format_version = "2.0"
front = jbox.panel { 
	graphics = {
		node = "Bg",
	},
	widgets = {
		jbox.analog_knob {
			graphics = { node = "learningRate" },
			value = "/custom_properties/learningRate",
		},
		jbox.analog_knob {
			graphics = { node = "threshold" },
			value = "/custom_properties/threshold",
		},
		jbox.step_button {
		  graphics = { node = "rectification" },
		  value = "/custom_properties/rectification",
		  increasing = true
		},
		--jbox.toggle_button {
		--	graphics = { node = "rectification" },
		--	value = "/custom_properties/rectification",
		--},
		jbox.sequence_meter {
			graphics = { node="rectificationDisplay" },
			value = "/custom_properties/rectification",
		},
		jbox.sequence_meter {
		  graphics = { node="thresholdLED" },
		  value = "/custom_properties/thresholdLED",
		},
		jbox.device_name {
			graphics = { node = "deviceName" },
		},
		jbox.sequence_fader{
      graphics = { node = "onoffbypass" },
      handle_size = 0,
      value = "/custom_properties/builtin_onoffbypass",
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
			graphics = { node = "SignalInputLeft" },
			socket = "/audio_inputs/signal1",
		},
		jbox.audio_output_socket {
			graphics = { node = "EnvelopeOutputLeft" },
			socket = "/audio_outputs/envelope1",
		},
		jbox.cv_output_socket {
			graphics = { node = "GateOutputCV" },
			socket = "/cv_outputs/gate",
		},
		jbox.audio_input_socket {
      graphics = { node = "SignalInputRight" },
      socket = "/audio_inputs/signal2",
    },
    jbox.audio_output_socket {
      graphics = { node = "EnvelopeOutputRight" },
      socket = "/audio_outputs/envelope2",
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
