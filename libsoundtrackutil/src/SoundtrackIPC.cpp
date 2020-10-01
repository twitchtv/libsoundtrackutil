
// Copyright Twitch Interactive, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT

#include "libsoundtrackutil/SoundtrackIPC.h"

namespace Twitch::Audio {

SoundtrackIPC::SoundtrackIPC(IPCCallbacks ipcCallbacks)
    : _ipcCallbacks(std::move(ipcCallbacks))
{
    _ipc = Twitch::IPC::ConnectionFactory::newClientConnection(kOutboundAudioIpcEndpoint);
    if(_ipcCallbacks.onConnect) {
        _ipc->onConnect(_ipcCallbacks.onConnect);
    }
    if(_ipcCallbacks.onDisconnect) {
        _ipc->onDisconnect(_ipcCallbacks.onDisconnect);
    }
    _ipc->onReceived([this](Twitch::IPC::Payload data) {
        if(_ipcCallbacks.onReceived) {
            auto optionalPacket = TwitchAudioPacket::deserialize(data);
            if(!optionalPacket) {
                return;
            }
            _ipcCallbacks.onReceived(*optionalPacket);
        }
    });

    _ipc->connect();
}

SoundtrackIPC::~SoundtrackIPC()
{
    _ipc->disconnect();
}

} // namespace Twitch::Audio
