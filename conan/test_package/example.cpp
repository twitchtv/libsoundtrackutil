
// Copyright Twitch Interactive, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: MIT

#include <libsoundtrackutil/SoundtrackIPC.h>

using namespace Twtch::Audio;

int main()
{
    SoundtrackIPC soundtrackIPC({[]() {}, []() {}, [](TwitchAudioPacket audioPacket) {}});
}
