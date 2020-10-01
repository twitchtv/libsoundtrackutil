
// Copyright Twitch Interactive, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include <gsl/span>
#include <vector>

namespace Twitch::Utility {
class OutputByteStream {
public:
    void reserve(size_t size)
    {
        _data.reserve(size);
    }

    template<typename ValueType, typename ArgType>
    void write(const ArgType &arg)
    {
        size_t startSize = _data.size();
        size_t valueSize = sizeof(ValueType);
        ValueType value = static_cast<ValueType>(arg);
        _data.resize(startSize + valueSize);
        memcpy(_data.data() + startSize, &value, valueSize);
    }

    void writeBytes(gsl::span<const uint8_t> bytes)
    {
        size_t startSize = _data.size();
        _data.resize(startSize + bytes.size());
        memcpy(_data.data() + startSize, bytes.data(), bytes.size());
    }

    std::vector<uint8_t> consume()
    {
        return std::move(_data);
    }

private:
    std::vector<uint8_t> _data;
};

class InputByteStream {
public:
    InputByteStream(gsl::span<const uint8_t> data)
        : _data(std::move(data))
    {
    }

    template<typename ValueType>
    ValueType read()
    {
        ValueType value;
        size_t valueSize = sizeof(ValueType);
        memcpy(&value, _data.data() + _currentPosition, valueSize);
        _currentPosition += valueSize;
        return value;
    }

    void readBytes(gsl::span<uint8_t> bytes)
    {
        memcpy(bytes.data(), _data.data() + _currentPosition, bytes.size());
        _currentPosition += bytes.size();
    }

    gsl::span<const uint8_t> readBytesView(size_t size)
    {
        gsl::span<const uint8_t> bytesView = _data.subspan(_currentPosition, size);
        _currentPosition += size;
        return bytesView;
    }

    size_t remainingSize() const
    {
        return _data.size() - _currentPosition;
    }

private:
    gsl::span<const uint8_t> _data;
    size_t _currentPosition = 0;
};
} // namespace Twitch::Utility
