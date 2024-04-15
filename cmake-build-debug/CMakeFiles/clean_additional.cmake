# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\inchiriere_masini_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\inchiriere_masini_autogen.dir\\ParseCache.txt"
  "inchiriere_masini_autogen"
  )
endif()
