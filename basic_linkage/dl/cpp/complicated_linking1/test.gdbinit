set environment LD_DEBUG=bindings
set environment LD_DEBUG_OUTPUT=testlog
catch load hello
catch load hello2
catch load hello3
catch unload hello
catch unload hello2
catch unload hello3

