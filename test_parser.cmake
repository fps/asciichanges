
execute_process(COMMAND "${MY_COMMAND}" INPUT_FILE "${INPUT_FILE}" RESULT_VARIABLE RESULT TIMEOUT 1)

if (NOT RESULT STREQUAL "0")
    message(FATAL_ERROR "exit_failure")
else()
    message(INFO "exit_success")
endif()
