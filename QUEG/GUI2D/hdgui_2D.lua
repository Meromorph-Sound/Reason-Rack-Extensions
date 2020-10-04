format_version = "2.0"

function displayForChannel(abcd,n)
  local suffix=abcd..n
  return jbox.custom_display {
      graphics = { node=suffix },
      display_width_pixels = 55,
      display_height_pixels = 55,
      values = { "/custom_properties/"..suffix },
      draw_function = "drawA"
    }
end

function makeWidgets()
  local widgets = {
    jbox.device_name {
      graphics = { node = "deviceName" },
    },
    jbox.sequence_fader{
            graphics = { node = "onoffbypass" },
            handle_size = 0,
            value = "/custom_properties/builtin_onoffbypass",
    }
  }
  for n=1, 4 do
    table.insert(widgets,jbox.custom_display {
      graphics = {
        node = "controller"..n 
      },
      display_width_pixels = 400,
      display_height_pixels = 400,
      values = { 
        "/custom_properties/x"..n, 
        "/custom_properties/y"..n,
        "/custom_properties/A"..n,
        "/custom_properties/B"..n,
        "/custom_properties/C"..n,
        "/custom_properties/D"..n,
         },
      draw_function = "drawController",
      gesture_function = "handleControllerInput"
    })
    table.insert(widgets,jbox.analog_knob {
      graphics = { node = "level"..n },
      value = "/custom_properties/level"..n
    })
    table.insert(widgets,jbox.toggle_button {
      graphics = { node = "manual"..n },
      value = "/custom_properties/manual"..n,
    })
    table.insert(widgets,jbox.toggle_button {
      graphics = { node = "vco"..n },
      
      value = "/custom_properties/vco"..n,
    })
    table.insert(widgets,displayForChannel('A',n))
    table.insert(widgets,displayForChannel('B',n))
    table.insert(widgets,displayForChannel('C',n))
    table.insert(widgets,displayForChannel('D',n))
  end
  return widgets
end

front = jbox.panel { 
	graphics = {
		node = "Bg",
	},
	widgets = makeWidgets()
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