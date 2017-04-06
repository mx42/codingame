-- https://www.codingame.com/ide/puzzle/the-descent
-- Xavier Morel - 2016-03-12

-- Auto-generated code below aims at helping you parse
-- the standard input according to the problem statement.


-- game loop
while true do
   v=0
   r=0
   for i=0,8-1 do
      mountainH = tonumber(io.read()) -- represents the height of one mountain, from 9 to 0.
      if mountainH > v then
         v = mountainH
         r = i
      end
   end

   -- Write an action using print()
   -- To debug: io.stderr:write("Debug message\n")

   print(r) -- The number of the mountain to fire on.
end
