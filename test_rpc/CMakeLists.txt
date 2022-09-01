set(PROTOC_INPUT_PATH ${PROJECT_SOURCE_DIR}/test_rpc)

execute_process(
COMMAND protoc
    --cpp_out=${PROTOC_INPUT_PATH}
    -I=${PROTOC_INPUT_PATH}
    ${PROTOC_INPUT_PATH}/user.proto
)

set(SERVER_LIST 
        service_provider.cc
        user.pb.cc
)

set(CLIENT_LIST 
        call_service.cc
        user.pb.cc
)


add_executable(provider ${SERVER_LIST})
target_link_libraries(provider pthread protobuf rpc)

add_executable(consumer ${CLIENT_LIST})
target_link_libraries(consumer pthread protobuf rpc)