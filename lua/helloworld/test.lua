-- test.lua
io.write("Your Name: ")
local name = io.read()
c_greet(name)

io.write("x: ")
local x = io.read()
io.write("y: ")
local y = io.read()

local sum = c_add(x, y)

print(x .. ' + ' .. y .. ' = ' .. sum)
