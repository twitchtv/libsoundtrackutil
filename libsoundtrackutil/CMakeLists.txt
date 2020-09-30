add_library(libsoundtrackutil STATIC)

target_link_libraries(libsoundtrackutil PUBLIC
  CONAN_PKG::twitch-native-ipc
  CONAN_PKG::ms-gsl
  )

if(MSVC)
  target_compile_definitions(libsoundtrackutil PRIVATE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
    _CRT_SECURE_NO_WARNINGS
    )
endif()

target_include_directories(libsoundtrackutil PUBLIC
  include
  )

target_sources(libsoundtrackutil PRIVATE
  src/SoundtrackIPC.cpp
  include/libsoundtrackutil/ByteStream.h
  include/libsoundtrackutil/SoundtrackIPC.h
  include/libsoundtrackutil/TwitchAudioPacket.h
  )

target_compile_features(libsoundtrackutil PRIVATE cxx_std_17)

install(TARGETS libsoundtrackutil
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}
)

install(DIRECTORY include
  DESTINATION ${CMAKE_INSTALL_PREFIX}
  )

format_code(libsoundtrackutil)
