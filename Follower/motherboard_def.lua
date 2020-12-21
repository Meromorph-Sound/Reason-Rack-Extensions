format_version = "3.0"
  

custom_properties = jbox.property_set{	
	document_owner = { 
		properties = { 
			learningRate = jbox.number { 
				property_tag = 1,
				default = 0.0,
				ui_name = jbox.ui_text("propertyname_LearningRate"),
				ui_type = jbox.ui_linear({min=0, max=1, units={{decimals=4}}}),
			},
			threshold = jbox.number { 
				property_tag = 2,
				default = 0.5,
				ui_name = jbox.ui_text("propertyname_Threshold"),
				ui_type = jbox.ui_linear({min=0, max=0.9999, units={{decimals=4}}}),
			},
			rectification = jbox.number {
        property_tag = 3,
        default = 0.0,
        steps = 3,
        ui_name = jbox.ui_text("propertyname_Rectification"),
        ui_type = jbox.ui_selector { jbox.ui_text("halfwave"), jbox.ui_text("fullwave"), jbox.ui_text("squared") },
      }
		}
	},
	rt_owner = {
		properties = {
			thresholdLED = jbox.number {
       property_tag=5,
       default=1,
       steps=3,
       ui_name = jbox.ui_text("propertyname_GateDisplay"),
       ui_type = jbox.ui_selector { jbox.ui_text("off"), jbox.ui_text("n/a"), jbox.ui_text("on") },
      },
		}
	},
	rtc_owner = {
		properties = {
			instance = jbox.native_object{},
		}
	},
}

midi_implementation_chart = {
  midi_cc_chart = {
   [20] = "/custom_properties/learningRate",
   [21] = "/custom_properties/threshold",
   [22] = "/custom_properties/rectification"
  }
}

remote_implementation_chart = {
  ["/custom_properties/learningRate"] = {
    internal_name="Learning Rate",
    short_ui_name=jbox.ui_text("short_learningRate"),
    shortest_ui_name=jbox.ui_text("shortest_learningRate")
  },
  ["/custom_properties/threshold"] = {
    internal_name="Threshold",
    short_ui_name=jbox.ui_text("short_threshold"),
    shortest_ui_name=jbox.ui_text("shortest_threshold")
  }
}

audio_inputs = {
  signal1 = jbox.audio_input{ ui_name = jbox.ui_text("audioInput") },
  signal2 = jbox.audio_input{ ui_name = jbox.ui_text("audioInput") },
}

audio_outputs = {
  envelope1 = jbox.audio_output{ ui_name = jbox.ui_text("envelopeOutput") }, 
  envelope2 = jbox.audio_output{ ui_name = jbox.ui_text("envelopeOutput") },    
}

cv_outputs = {
  gate = jbox.cv_output{ ui_name = jbox.ui_text("gateOutput") }
}

jbox.add_stereo_effect_routing_hint{
  left_input = "/audio_inputs/signal1",
  right_input = "/audio_inputs/signal2",
  left_output = "/audio_outputs/envelope1",
  right_output = "/audio_outputs/envelope2",
  type = "true_stereo"
}
jbox.add_stereo_audio_routing_target{
  signal_type = "return",
  left = "/audio_inputs/signal1",
  right = "/audio_inputs/signal2",
  auto_route_enable = true
}
jbox.add_stereo_audio_routing_target{
  signal_type = "send",
  left = "/audio_outputs/envelope1",
  right = "/audio_outputs/envelope2",
  auto_route_enable = true
}
jbox.add_stereo_audio_routing_pair{
  left = "/audio_inputs/signal1",
  right = "/audio_inputs/signal2"
}
jbox.add_stereo_audio_routing_pair{
  left = "/audio_outputs/envelope1",
  right = "/audio_outputs/envelope2"
}
jbox.set_effect_auto_bypass_routing{
  {
    "/audio_inputs/signal1",
    "/audio_outputs/envelope1"
  },
  {
    "/audio_inputs/signal2",
    "/audio_outputs/envelope2"
  }
}

