format_version = "3.0"

custom_properties = jbox.property_set{
	document_owner = {
		properties = {}
	},
	rtc_owner = {
		properties = {
			instance = jbox.native_object{}
		}
	},
	rt_owner = {
		properties = {}
	}
}

midi_implementation_chart = {
	midi_cc_chart = {}
}

remote_implementation_chart = {
}

ui_groups = {}

cv_inputs = {
  cvIn = jbox.cv_input{ ui_name = jbox.ui_text("cvInput") }
}
cv_outputs = {
  cvOut = jbox.cv_output{ ui_name = jbox.ui_text("cvOutput") }
}

audio_inputs = {}
audio_outputs = {
	audioOut = jbox.audio_output{ ui_name = jbox.ui_text("audioOutput") }
}




