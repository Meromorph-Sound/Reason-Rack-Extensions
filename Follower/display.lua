-- require 'math'
-- require 'table'

format_version = "1.0"

GRAPH_COLOUR = { r=0, g=255, b=0 }
MARKER_COLOUR = { r=255, g=255, b=0 }
LINE_WIDTH = 4
GRAPH_STEP = 10
WIDTH_FACTOR = 4

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
  
  
  
  -- special cases
  
  if rho == 1 then
    -- constant 0; tau is zero, so no graph to draw
    jbox_display.draw_line({ x=0,y=height-LINE_WIDTH},{x=width-1,y=height-LINE_WIDTH}, GRAPH_COLOUR,LINE_WIDTH,"round")
  elseif rho == 0 then
    -- constant 1; tau is infinite
    jbox_display.draw_line({ x=LINE_WIDTH,y=0},{x=LINE_WIDTH,y=height-1}, GRAPH_COLOUR,LINE_WIDTH,"round")
  else
    -- the viable cases
    
    local tau = -1/math.log(1-rho)
    local xScale = WIDTH_FACTOR*tau/width
      
    local lines = {}
    for i = 0, width-1, GRAPH_STEP do
      local y = (1-math.exp(-xScale*i/tau)) * height
      table.insert(lines,{ x=i, y=y })
    end
    jbox_display.draw_lines(lines,GRAPH_COLOUR,"open",LINE_WIDTH,"round","round")
    
    -- draw the -3db line
    
    local x3DB = math.log(2)*tau/xScale
    jbox_display.draw_line({x=x3DB,y=0},{x=x3DB,y=height},MARKER_COLOUR,LINE_WIDTH,"round")
    
  end


end