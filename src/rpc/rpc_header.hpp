#pragma once

#include <cstdint>
#include <stdexcept>
#include "util/buffer_serializer.hpp"

namespace rosefinch {
namespace rpc {

enum class msg_type :uint8_t {
    request_vote_request = 1,
    request_vote_response = 2,
    append_entries_request = 3,
    append_entries_response = 4,
    client_request = 5,
    add_server_request = 6,
    add_server_response = 7,
    remove_server_request = 8,
    remove_server_response = 9,
    sync_log_request = 10,
    sync_log_response = 11,
    join_cluster_request = 12,
    join_cluster_response = 13,
    leave_cluster_request = 14,
    leave_cluster_response = 15,
    install_snapshot_request = 16,
    install_snapshot_response = 17,
    ping_request = 18,
    ping_response = 19,
    pre_vote_request = 20,
    pre_vote_response = 21,
    other_request = 22,
    other_response = 23,
    priority_change_request = 24,
    priority_change_response = 25,
    reconnect_request = 26,
    reconnect_response = 27,
    custom_notification_request = 28,
    custom_notification_response = 29,
};

// request header:
//     msg_type        type                (1),
//     int32_t         src_id              (4),
//     int32_t         dst_id              (4),
//     uint64_t        term                (8),
//     uint64_t        last_log_term       (8),
//     uint64_t        last_log_idx        (8),
//     uint64_t        commit_idx          (8),
//     uint32_t        log_data_size       (4),
//     ---------------------------------------
//                     total               (45)
constexpr auto rpc_req_header_size = 1 + 4 * 3 + 8 * 4;

struct req_header {
    msg_type type;
    int32_t src_id;
    int32_t dst_id;
    uint64_t term;
    uint64_t last_log_term;
    uint64_t last_log_idx;
    uint64_t commit_idx;
    uint32_t log_data_size;

    bool operator==(const req_header&) const = default;
};

inline void serialize(const req_header& h, char* buf, size_t len) {
    if (len < rpc_req_header_size) {
        throw std::runtime_error("serialize buf size < rpc_req_header_size");
    }

    serialize::serializer se(buf, len);
    se.put_integer(static_cast<uint8_t>(h.type));
    se.put_integer(h.src_id);
    se.put_integer(h.dst_id);
    se.put_integer(h.term);
    se.put_integer(h.last_log_term);
    se.put_integer(h.last_log_idx);
    se.put_integer(h.commit_idx);
    se.put_integer(h.log_data_size);
}

inline void deserialize(req_header& h, const char* buf, size_t len) {
    if (len < rpc_req_header_size) {
        throw std::runtime_error("serialize buf size < rpc_req_header_size");
    }

    serialize::serializer de(const_cast<char*>(buf), len);
    h.type = static_cast<msg_type>(de.get_integer<uint8_t>());
    h.src_id = de.get_integer<int32_t>();
    h.dst_id = de.get_integer<int32_t>();
    h.term = de.get_integer<uint64_t>();
    h.last_log_term = de.get_integer<uint64_t>();
    h.last_log_idx = de.get_integer<uint64_t>();
    h.commit_idx = de.get_integer<uint64_t>();
    h.log_data_size = de.get_integer<uint32_t>();
}

// response header:
//     msg_type        type                (1),
//     int32_t         src_id              (4),
//     int32_t         dst_id              (4),
//     uint64_t        term                (8),
//     uint64_t        next_idx            (8),
//     uint8_t         accepted            (1),
//     uint32_t        ctx_data_size       (4),
//     --------------------------------------
//                     total               (30)
constexpr auto rpc_res_header_size = 1 * 2 + 4 * 3 + 8 * 2;

struct res_header {
    msg_type type;
    int32_t src_id;
    int32_t dst_id;
    uint64_t term;
    uint64_t next_idx;
    uint8_t accepted;
    uint32_t ctx_data_size;

    bool operator==(const res_header&) const = default;
};

inline void serialize(const res_header& h, char* buf, size_t len) {
    if (len < rpc_res_header_size) {
        throw std::runtime_error("serialize buf size < rpc_res_header_size");
    }

    serialize::serializer se(buf, len);
    se.put_integer(static_cast<uint8_t>(h.type));
    se.put_integer(h.src_id);
    se.put_integer(h.dst_id);
    se.put_integer(h.term);
    se.put_integer(h.next_idx);
    se.put_integer(h.accepted);
    se.put_integer(h.ctx_data_size);
}

inline void deserialize(res_header& h, const char* buf, size_t len) {
    if (len < rpc_res_header_size) {
        throw std::runtime_error("serialize buf size < rpc_res_header_size");
    }

    serialize::serializer de(const_cast<char*>(buf), len);
    h.type = static_cast<msg_type>(de.get_integer<uint8_t>());
    h.src_id = de.get_integer<int32_t>();
    h.dst_id = de.get_integer<int32_t>();
    h.term = de.get_integer<uint64_t>();
    h.next_idx = de.get_integer<uint64_t>();
    h.accepted = de.get_integer<uint8_t>();
    h.ctx_data_size = de.get_integer<uint32_t>();
}

}
}



