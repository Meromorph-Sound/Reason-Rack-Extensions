-- require 'math'
-- require 'table'

format_version = "1.0"

GRAPH_COLOUR = { r=0, g=255, b=0 }
MARKER_COLOUR = { r=255, g=255, b=0 }
LINE_WIDTH = 4
GRAPH_STEP = 10
WIDTH_FACTOR = 4

function clamp(x) 
  assert(x ~= nil)
  return math.max(0, math.min(1, x))
end

--[[ Left display ]]--

function drawController(property_values, display_info, dirty_rect)

  -- Get the width and height of the display (in virtual pixels)

  local width = display_info.width
  local height = display_info.height
  
  local x = property_values[1]
  local y = property_values[2]
  assert(x ~= nil)
  assert(y ~= nil)
  
  local cx = width*clamp(x)
  local cy = width*clamp(y)
  
  jbox_display.draw_rect({ 
    left = cx - 10, 
    top = cy - 10,
    right = cx + 10,
    bottom = cy + 10 
  },
  GRAPH_COLOUR
  ) 
end

function changeTable(x,y,name)
  x=clamp(x)
  y=clamp(y)
  jbox.trace("Setting (X1,Y1) = " .. pairString(x,y) .. "for function " .. name)
  
  local changes = {}
  changes[1] = x
  changes[2] = y
  return {
    gesture_ui_name = jbox.ui_text(name),
    property_changes = changes
  }
end

function pairString(x,y) 
  return "(" .. tostring(x) .. "," .. tostring(y) .. ")"
end


function setControllerPosition(property_values,display_info,gesture_info,custom_data) 
  local width = display_info.width
  local height = display_info.height
  
  local x = gesture_info.current_point.x
  local y = gesture_info.current_point.y
  assert(x ~= nil)
  assert(y ~= nil)
  
  return changeTable(x/width,y/height,"setController")
end

function resetControllerPosition(property_values,display_info,gesture_info,custom_data)
  local x = custom_data.x
  local y = custom_data.y
  assert(x ~= nil)
  assert(y ~= nil)
  
  return changeTable(x,y,"resetController")
end
  

function handleControllerInput(property_values, display_info, gesture_start_point)
  
  local gestureDefinition = {
    custom_data = {
      x = property_values[1],
      y = property_values[2]
    },
    handlers = {
      on_tap = "setControllerPosition",
      on_update = "setControllerPosition",
      on_release = "setControllerPosition",
      on_cancel = "resetControllerPosition"
    }
  }
  return gestureDefinition

end
