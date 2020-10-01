
// Copyright Twitch Interactive, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include "TwitchAudioPacket.h"
#include "nativeipc/ConnectionFactory.h"
#include <memory>

namespace Twitch::Audio {

static const std::string kOutboundAudioIpcEndpoint = "twitch-outbound-audio-capture";

struct IPCCallbacks {
    std::function<void()> onConnect;
    std::function<void()> onDisconnect;
    std::function<void(TwitchAudioPacket audioPacket)> onReceived;
};

class SoundtrackIPC {
public:
    SoundtrackIPC(IPCCallbacks ipcCallbacks);
    ~SoundtrackIPC();

private:
    IPCCallbacks _ipcCallbacks;
    std::unique_ptr<Twitch::IPC::IConnection> _ipc;
};

} // namespace Twitch::Audio
