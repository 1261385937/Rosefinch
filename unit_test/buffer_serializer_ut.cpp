#include "gtest/gtest.h"
#include "util/buffer_serializer.hpp"
#include "rpc/rpc_header.hpp"

TEST(serializer, case1) {
    char data[32]{};
    rosefinch::serialize::serializer in(data, 32);

    uint8_t ud8 = 1;
    in.put_integer(ud8);
    int16_t d16 = -2;
    in.put_integer(d16);
    uint32_t ud32 = 3;
    in.put_integer(ud32);
    int64_t d64 = -4;
    in.put_integer(d64);

    int8_t d8 = -1;
    in.put_integer(d8);
    uint16_t ud16 = 2;
    in.put_integer(ud16);
    int32_t d32 = -3;
    in.put_integer(d32);
    uint64_t ud64 = 4;
    in.put_integer(ud64);

    rosefinch::serialize::serializer out(data, 32);

    EXPECT_EQ(ud8, out.get_integer<uint8_t>());
    EXPECT_EQ(d16, out.get_integer<int16_t>());
    EXPECT_EQ(ud32, out.get_integer<uint32_t>());
    EXPECT_EQ(d64, out.get_integer<int64_t>());

    EXPECT_EQ(d8, out.get_integer<int8_t>());
    EXPECT_EQ(ud16, out.get_integer<uint16_t>());
    EXPECT_EQ(d32, out.get_integer<int32_t>());
    EXPECT_EQ(ud64, out.get_integer<uint64_t>());
}

TEST(serializer, req_header) {
    namespace rpc = rosefinch::rpc;
    char data[rpc::rpc_req_header_size]{};
    rpc::req_header h{};
    h.type = rpc::msg_type::add_server_request;
    h.src_id = -1;
    h.dst_id = -3;
    h.term = 1;
    h.last_log_term = 2;
    h.last_log_idx = 3;
    h.commit_idx = 4;
    h.log_data_size = 5;
    rpc::serialize(h, data, rpc::rpc_req_header_size);

    rpc::req_header new_head;
    rpc::deserialize(new_head, data, rpc::rpc_req_header_size);
    EXPECT_EQ(new_head, h);
}

TEST(serializer, res_header) {
    namespace rpc = rosefinch::rpc;
    char data[rpc::rpc_res_header_size]{};
    rpc::res_header h{};
    h.type = rpc::msg_type::add_server_request;
    h.src_id = -1;
    h.dst_id = -3;
    h.term = 1;
    h.next_idx = 956809568;
    h.accepted = 1;
    h.ctx_data_size = 498579476;
    rpc::serialize(h, data, rpc::rpc_res_header_size);

    rpc::res_header new_head;
    rpc::deserialize(new_head, data, rpc::rpc_res_header_size);
    EXPECT_EQ(new_head, h);
}