
set(RPC_LIST 
        rpcApplication.cc
        rpcConfig.cc
        rpcProvider.cc
        zookeeperUtil.cc
        logger.cc
        rpcHeader.pb.cc
        rpcChannel.cc
        rpcController.cc
)

message(${RPC_LIST})

set(RPC_LIB
        mymuduo
        zookeeper_mt
        )

add_library(rpc SHARED ${RPC_LIST})
target_link_libraries(rpc ${RPC_LIB})
