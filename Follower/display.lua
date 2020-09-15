-- require 'math'
-- require 'table'

format_version = "1.0"

DRAWING_COLOUR = { r=255, g=127, b=0 }

function clamp(x) 
  return math.max(0, math.min(1, x))
end

--[[ Left display ]]--

function draw_response(property_values, display_info, dirty_rect)

  -- Get the width and height of the display (in virtual pixels)

  local width = display_info.width
  local height = display_info.height
  
  local rho = property_values[1]
  assert(rho ~= nil)
  rho=clamp(rho)  -- limit to [0,1]
  
  -- want Tmax to be based on lowest pheasable frequency.  If we say
  -- that's about 20 Hz, then make it (say) 0.25 seconds.
  
  -- special cases
  
  if rho == 1 then
    -- constant 0; tau is zero, so no graph to draw
    jbox_display.draw_line({ x=0,y=height},{x=width,y=height}, DRAWING_COLOUR)
  elseif rho == 0 then
    -- constant 1; tau is infinite
    jbox_display.draw_line({ x=0,y=height},{x=0,y=0}, DRAWING_COLOUR)
  else
    -- the viable cases
    local tau = -1/math.log(1-rho)
    local xMax = 4*tau
    local xScale = xMax/width
    
    local lines = {}
    for i = 0, width-1 do
      local y = (1-math.exp(-xScale*i/tau)) * height
      table.insert(lines,{ x=i, y=y })
    end
    jbox_display.draw_lines(lines,DRAWING_COLOUR,"open",4,"round","round")
  end


end