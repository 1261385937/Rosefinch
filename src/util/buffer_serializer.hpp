#pragma once

#include <cstdint>
#include <bit>

namespace rosefinch {
namespace serialize {

constexpr bool little_end = (std::endian::native == std::endian::little);

template <typename T>
concept integral_8bit = std::is_same_v<T, uint8_t> || std::is_same_v<T, int8_t>;

template <typename T>
concept integral_16bit = std::is_same_v<T, uint16_t> || std::is_same_v<T, int16_t>;

template <typename T>
concept integral_32bit = std::is_same_v<T, uint32_t> || std::is_same_v<T, int32_t>;

template <typename T>
concept integral_64bit = std::is_same_v<T, uint64_t> || std::is_same_v<T, int64_t>;


class serializer {
private:
    size_t pos_ = 0;
    uint8_t* begin_ = nullptr;
    size_t len_ = 0;

public:
    serializer(char* data, size_t len)
        : begin_(reinterpret_cast<uint8_t*>(data)), len_(len) {}

private:
    serializer(const serializer&) = delete;
    serializer& operator=(const serializer&) = delete;

public:
    /**
     * Put 1-byte integer.
     *
     * @param val 1-byte integer.
     */
    template<typename Integer>
        requires integral_8bit<Integer>
    void put_integer(Integer val) {
        uint8_t* ptr = begin_ + pos_;
        ptr[0] = val;
        pos_ += sizeof(Integer);
    }

    /**
     * Put 2-byte integer.
     *
     * @param val 2-byte integer.
     */
    template<typename Integer>
        requires integral_16bit<Integer>
    void put_integer(Integer val) {
        uint8_t* ptr = begin_ + pos_;
        if constexpr (little_end) {
            ptr[0] = (val >> 0) & 0xff;
            ptr[1] = (val >> 8) & 0xff;
        }
        else {
            ptr[1] = (val >> 0) & 0xff;
            ptr[0] = (val >> 8) & 0xff;
        }
        pos_ += sizeof(Integer);
    }

    /**
     * Put 4-byte integer.
     *
     * @param val 4-byte integer.
     */
    template<typename Integer>
        requires integral_32bit<Integer>
    void put_integer(Integer val) {
        uint8_t* ptr = begin_ + pos_;
        if constexpr (little_end) {
            ptr[0] = (val >> 0) & 0xff;
            ptr[1] = (val >> 8) & 0xff;
            ptr[2] = (val >> 16) & 0xff;
            ptr[3] = (val >> 24) & 0xff;
        }
        else {
            ptr[3] = (val >> 0) & 0xff;
            ptr[2] = (val >> 8) & 0xff;
            ptr[1] = (val >> 16) & 0xff;
            ptr[0] = (val >> 24) & 0xff;
        }
        pos_ += sizeof(Integer);
    }

    /**
     * Put 8-byte integer.
     *
     * @param val 8-byte integer.
     */
    template<typename Integer>
        requires integral_64bit<Integer>
    void put_integer(Integer val) {
        uint8_t* ptr = begin_ + pos_;
        if constexpr (little_end) {
            ptr[0] = (val >> 0) & 0xff;
            ptr[1] = (val >> 8) & 0xff;
            ptr[2] = (val >> 16) & 0xff;
            ptr[3] = (val >> 24) & 0xff;
            ptr[4] = (val >> 32) & 0xff;
            ptr[5] = (val >> 40) & 0xff;
            ptr[6] = (val >> 48) & 0xff;
            ptr[7] = (val >> 56) & 0xff;
        }
        else {
            ptr[7] = (val >> 0) & 0xff;
            ptr[6] = (val >> 8) & 0xff;
            ptr[5] = (val >> 16) & 0xff;
            ptr[4] = (val >> 24) & 0xff;
            ptr[3] = (val >> 32) & 0xff;
            ptr[2] = (val >> 40) & 0xff;
            ptr[1] = (val >> 48) & 0xff;
            ptr[0] = (val >> 56) & 0xff;
        }
        pos_ += sizeof(Integer);
    }

    /**
     * Get 1-byte integer.
     *
     * @return 1-byte integer.
     */
    template<typename Integer>
        requires integral_8bit<Integer>
    Integer get_integer() {
        uint8_t* ptr = begin_ + pos_;
        Integer ret = static_cast<Integer>(ptr[0]);
        pos_ += sizeof(Integer);
        return ret;
    }

    /**
     * Get 2-byte integer.
     *
     * @return 2-byte integer.
     */
    template<typename Integer>
        requires integral_16bit<Integer>
    Integer get_integer() {
        uint8_t* ptr = begin_ + pos_;
        Integer ret = 0;
        if constexpr (little_end) {
            uint16_t tmp = ptr[1];
            tmp <<= 8;
            tmp |= ptr[0];
            ret = static_cast<Integer>(tmp);
        }
        else {
            uint16_t tmp = ptr[0];
            tmp <<= 8;
            tmp |= ptr[1];
            ret = static_cast<Integer>(tmp);
        }
        pos_ += sizeof(Integer);
        return ret;
    }

    /**
     * Get 4-byte integer.
     *
     * @return 4-byte integer.
     */
    template<typename Integer>
        requires integral_32bit<Integer>
    Integer get_integer() {
        uint8_t* ptr = begin_ + pos_;
        Integer ret = 0;
        if constexpr (little_end) {
            uint32_t tmp = ptr[3];
            tmp <<= 8;
            tmp |= ptr[2];
            tmp <<= 8;
            tmp |= ptr[1];
            tmp <<= 8;
            tmp |= ptr[0];
            ret = static_cast<Integer>(tmp);
        }
        else {
            uint32_t tmp = ptr[0];
            tmp <<= 8;
            tmp |= ptr[1];
            tmp <<= 8;
            tmp |= ptr[2];
            tmp <<= 8;
            tmp |= ptr[3];
            ret = static_cast<Integer>(tmp);
        }
        pos_ += sizeof(Integer);
        return ret;
    }

    /**
     * Get 8-byte integer.
     *
     * @return 8-byte integer.
     */
    template<typename Integer>
        requires integral_64bit<Integer>
    Integer get_integer() {
        uint8_t* ptr = begin_ + pos_;
        Integer ret = 0;
        if constexpr (little_end) {
            uint64_t tmp = ptr[7];
            tmp <<= 8;
            tmp |= ptr[6];
            tmp <<= 8;
            tmp |= ptr[5];
            tmp <<= 8;
            tmp |= ptr[4];
            tmp <<= 8;
            tmp |= ptr[3];
            tmp <<= 8;
            tmp |= ptr[2];
            tmp <<= 8;
            tmp |= ptr[1];
            tmp <<= 8;
            tmp |= ptr[0];
            ret = static_cast<Integer>(tmp);
        }
        else {
            uint64_t tmp = ptr[0]; 
            tmp <<= 8;
            tmp |= ptr[1]; 
            tmp <<= 8;
            tmp |= ptr[2]; 
            tmp <<= 8;
            tmp |= ptr[3]; 
            tmp <<= 8;
            tmp |= ptr[4]; 
            tmp <<= 8;
            tmp |= ptr[5]; 
            tmp <<= 8;
            tmp |= ptr[6];
            tmp <<= 8;
            tmp |= ptr[7];
            ret = static_cast<Integer>(tmp);
        }
        pos_ += sizeof(Integer);
        return ret;
    }
};

}
}

