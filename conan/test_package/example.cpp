#include <libsoundtrackutil/SoundtrackIPC.h>

using namespace Twtch::Audio;

int main()
{
    SoundtrackIPC soundtrackIPC({[]() {}, []() {}, [](TwitchAudioPacket audioPacket) {}});
}
