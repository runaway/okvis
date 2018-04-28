if("7c57de5080c9f5a4f067e2d20b5f33bad5b1ade6" STREQUAL "")
  message(FATAL_ERROR "Tag for git checkout should not be empty.")
endif()

set(run 0)

if("/home/david/Downloads/okvis/build/ceres/src/ceres_external-stamp/ceres_external-gitinfo.txt" IS_NEWER_THAN "/home/david/Downloads/okvis/build/ceres/src/ceres_external-stamp/ceres_external-gitclone-lastrun.txt")
  set(run 1)
endif()

if(NOT run)
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: '/home/david/Downloads/okvis/build/ceres/src/ceres_external-stamp/ceres_external-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E remove_directory "/home/david/Downloads/okvis/build/ceres/src/ceres_external"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/david/Downloads/okvis/build/ceres/src/ceres_external'")
endif()

# try the clone 3 times incase there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git" clone --origin "origin" "https://github.com/ceres-solver/ceres-solver.git" "ceres_external"
    WORKING_DIRECTORY "/home/david/Downloads/okvis/build/ceres/src"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/ceres-solver/ceres-solver.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git" checkout 7c57de5080c9f5a4f067e2d20b5f33bad5b1ade6
  WORKING_DIRECTORY "/home/david/Downloads/okvis/build/ceres/src/ceres_external"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: '7c57de5080c9f5a4f067e2d20b5f33bad5b1ade6'")
endif()

execute_process(
  COMMAND "/usr/bin/git" submodule init 
  WORKING_DIRECTORY "/home/david/Downloads/okvis/build/ceres/src/ceres_external"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to init submodules in: '/home/david/Downloads/okvis/build/ceres/src/ceres_external'")
endif()

execute_process(
  COMMAND "/usr/bin/git" submodule update --recursive 
  WORKING_DIRECTORY "/home/david/Downloads/okvis/build/ceres/src/ceres_external"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/david/Downloads/okvis/build/ceres/src/ceres_external'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "/home/david/Downloads/okvis/build/ceres/src/ceres_external-stamp/ceres_external-gitinfo.txt"
    "/home/david/Downloads/okvis/build/ceres/src/ceres_external-stamp/ceres_external-gitclone-lastrun.txt"
  WORKING_DIRECTORY "/home/david/Downloads/okvis/build/ceres/src/ceres_external"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/david/Downloads/okvis/build/ceres/src/ceres_external-stamp/ceres_external-gitclone-lastrun.txt'")
endif()

