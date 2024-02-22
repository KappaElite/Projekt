# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/ProjektJIPP_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ProjektJIPP_autogen.dir/ParseCache.txt"
  "ProjektJIPP_autogen"
  )
endif()
