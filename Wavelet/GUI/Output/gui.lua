format_version = "4.0"
front = jbox.panel{
	backdrop = jbox.image{path="Reason_GUI_front1U"},
	widgets = {
		jbox.device_name{
			transform = {640,50},
		},
		jbox.sequence_fader{
			transform = {37,10},
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
		jbox.analog_knob{
			transform = {370,10},
			animation = jbox.image_sequence{path = "Reason_GUI_Knob_63frames", frames = 63},
			value = "/custom_properties/GrowthRate",
			show_remote_box = true,
			show_automation_rect = true,
		},
		jbox.analog_knob{
			transform = {470,10},
			animation = jbox.image_sequence{path = "Reason_GUI_Knob_63frames", frames = 63},
			value = "/custom_properties/Barrier",
			show_remote_box = true,
			show_automation_rect = true,
		},
		jbox.analog_knob{
			transform = {420,10},
			animation = jbox.image_sequence{path = "Reason_GUI_Knob_63frames", frames = 63},
			value = "/custom_properties/InputScale",
			show_remote_box = true,
			show_automation_rect = true,
		},
		jbox.analog_knob{
			transform = {520,10},
			animation = jbox.image_sequence{path = "Reason_GUI_Knob_63frames", frames = 63},
			value = "/custom_properties/Amplitude",
			show_remote_box = true,
			show_automation_rect = true,
		},
		jbox.analog_knob{
			transform = {590,10},
			animation = jbox.image_sequence{path = "Reason_GUI_Knob_63frames", frames = 63},
			value = "/custom_properties/Smoothing",
			show_remote_box = true,
			show_automation_rect = true,
		},
		jbox.toggle_button{
			transform = {570,11},
			background = jbox.image_sequence{path = "Reason_GUI_Button_53_2frames", frames = 2},
			value = "/custom_properties/Smooth",
			show_remote_box = true,
			show_automation_rect = true,
		},
		jbox.momentary_button{
			transform = {300,17},
			background = jbox.image_sequence{path = "Reason_GUI_Button_63_2frames", frames = 2},
			value = "/custom_properties/Zero",
			show_remote_box = true,
			show_automation_rect = true,
		},
		jbox.sequence_meter{
			transform = {200,24},
			animation = jbox.image_sequence{path = "Reason_GUI_DoubleLamp_4frames", frames = 4},
			value = "/custom_properties/InMode",
		},
		jbox.sequence_meter{
			transform = {240,24},
			animation = jbox.image_sequence{path = "Reason_GUI_DoubleLamp_4frames", frames = 4},
			value = "/custom_properties/OutMode",
		},
	}
}

folded_front = jbox.panel{
	backdrop = jbox.image{path="Reason_GUI_Panel_Folded_Front"},
	widgets = {
	}
}

back = jbox.panel{
	backdrop = jbox.image{path="Reason_GUI_backPanel"},
	widgets = {
		jbox.placeholder{
			transform = {400,20},
		},
		jbox.audio_output_socket{
			transform = {320,24},
			socket = "/audio_outputs/audioOut",
		},
		jbox.audio_input_socket{
			transform = {200,24},
			socket = "/audio_inputs/audioIn",
		},
		jbox.cv_output_socket{
			transform = {360,26},
			socket = "/cv_outputs/cvOut",
		},
		jbox.cv_input_socket{
			transform = {240,26},
			socket = "/cv_inputs/cvIn",
		},
		jbox.device_name{
			transform = {10,44},
		},
	}
}

folded_back = jbox.panel{
	backdrop = jbox.image{path="Reason_GUI_Panel_Folded_Back"},
	cable_origin = {377,15},
	widgets = {
	}
}

