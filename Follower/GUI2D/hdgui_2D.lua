format_version = "2.0"
front = jbox.panel { 
	graphics = {
		node = "Bg",
	},
	widgets = {
		jbox.analog_knob {
			graphics = {
				node = "learningRate",
			},
			value = "/custom_properties/learningRate",
		},
		jbox.analog_knob {
			graphics = {
				node = "threshold",
			},
			value = "/custom_properties/threshold",
		},
		jbox.toggle_button {
			graphics = { 
				node = "rectification",
				--hit_boundaries = { left=Q*12, top=Q*12, right=Q*12, bottom=Q*12 }, 
			},
			value = "/custom_properties/rectification",
		},
		jbox.sequence_meter {
			graphics = {
				node="rectificationDisplay",
			},
			value = "/custom_properties/rectificationDisplay",
		},
		jbox.device_name {
			graphics = {
				node = "deviceName",
			},
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
			graphics = { node = "SignalInputSocket" },
			socket = "/audio_inputs/signal",
		},
		jbox.audio_output_socket {
			graphics = { node = "EnvelopeOutputSocket" },
			socket = "/audio_outputs/envelope",
		},
		jbox.cv_output_socket {
			graphics = { node = "GateOutputSocket" },
			socket = "/cv_outputs/gate",
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
