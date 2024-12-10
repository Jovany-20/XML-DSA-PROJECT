# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\myFirstApplication_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\myFirstApplication_autogen.dir\\ParseCache.txt"
  "myFirstApplication_autogen"
  )
endif()
