
# 指定生成可执行文件
add_executable(chatClient ./client.cpp)
# 指定可执行文件链接时需要依赖的库文件
target_link_libraries(chatClient pthread)