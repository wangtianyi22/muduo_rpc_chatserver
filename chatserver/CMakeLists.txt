set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/chatserver/bin)
include_directories(${PROJECT_SOURCE_DIR}/chatserver/include)



add_subdirectory(chat_server)
add_subdirectory(chat_client)