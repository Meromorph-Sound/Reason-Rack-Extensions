format_version = "4.0"
front = jbox.panel{
	backdrop = jbox.image{path="Reason_GUI_FollowerFrontPanel"},
	widgets = {
		jbox.analog_knob{
			transform = {140,16},
			animation = jbox.image_sequence{path = "Reason_GUI_Knob_01_63frames", frames = 63},
			value = "/custom_properties/learningRate",
			show_remote_box = true,
			show_automation_rect = true,
		},
		jbox.analog_knob{
			transform = {180,16},
			animation = jbox.image_sequence{path = "Reason_GUI_Knob_01_63frames", frames = 63},
			value = "/custom_properties/threshold",
			show_remote_box = true,
			show_automation_rect = true,
		},
		jbox.toggle_button{
			transform = {220,20},
			background = jbox.image_sequence{path = "Reason_GUI_Button_23_2frames", frames = 2},
			value = "/custom_properties/rectification",
			show_remote_box = true,
			show_automation_rect = true,
		},
		jbox.sequence_meter{
			transform = {252,20},
			animation = jbox.image_sequence{path = "Reason_GUI_Lamp_18_3frames", frames = 3},
			value = "/custom_properties/rectificationDisplay",
		},
		jbox.device_name{
			transform = {37,43},
		},
		jbox.sequence_fader{
			transform = {37,9},
			animation = jbox.image_sequence{path = "Reason_GUI_Fader_Bypass_3frames", frames = 3},
			value = "/custom_properties/builtin_onoffbypass",
			handle_size = 0,
			inset1 = 0,
			inset2 = 0,
			orientation = "vertical",
			inverted = false,
			show_remote_box = true,
			show_automation_rect = true,
		},
	}
}

folded_front = jbox.panel{
	backdrop = jbox.image{path="Reason_GUI_Panel_Folded_Front"},
	widgets = {
	}
}

back = jbox.panel{
	backdrop = jbox.image{path="Reason_GUI_Panel_Back_1U"},
	widgets = {
		jbox.placeholder{
			transform = {20,20},
		},
		jbox.audio_input_socket{
			transform = {200,20},
			socket = "/audio_inputs/signal",
		},
		jbox.audio_output_socket{
			transform = {240,20},
			socket = "/audio_outputs/envelope",
		},
		jbox.cv_output_socket{
			transform = {280,20},
			socket = "/cv_outputs/gate",
		},
	}
}

folded_back = jbox.panel{
	backdrop = jbox.image{path="Reason_GUI_Panel_Folded_Back"},
	cable_origin = {377,15},
	widgets = {
	}
}

