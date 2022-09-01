
set(SRC_LIST
    ./chatserver.cpp
    ./chatservice.cpp
    ./model/usermodel.cpp
    ./model/offlinemessage.cpp
    ./model/friendmodel.cpp
    ./model/groupmodel.cpp
    ./redis.cpp
    ./mysql.cpp)

add_executable(chatServer ./main.cpp ${SRC_LIST})
target_link_libraries(chatServer mymuduo pthread protobuf mysqlclient hiredis)
