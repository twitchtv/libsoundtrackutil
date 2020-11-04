
# Copyright Twitch Interactive, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: MIT

from conans import ConanFile, CMake, tools
import os

#TODO change name of function
class LibSoundtrackUtilConan(ConanFile):
    name = "libsoundtrackutil"
    version = "0.0.7"
    license = "None"
    url = "https://github.com/twitchtv/libsoundtrackutil"
    description = ""
    # set build specific options here
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    #requirements that will propagated to users of the library
    requires = ("twitch-native-ipc/3.1.1",
    "ms-gsl/2.0.0",
    )

    #set package specific options here
    options = {"shared": [True, False]}

    default_options = "shared=False"

    exports_sources = ("../cmakeUtils*",
        "../libsoundtrackutil*",
        "../CMakeLists.txt",
    )


    @property
    def _is_win(self):
        return self.settings.os == "Windows"

    @property
    def _is_mac(self):
        return self.settings.os == "Macos"

    @property
    def _is_linux(self):
        return self.settings.os == "Linux"

    # use requirements function for things that need to be conditionally added
    #def requirements(self):

    def _configure_cmake(self):
        cmake_build_type = self.settings.build_type
        if cmake_build_type == "Release":
            cmake_build_type = "RelWithDebInfo"
        cmake = CMake(self, build_type=cmake_build_type)
        cmake.definitions["ENABLE_CODE_FORMATTING"] = False
        cmake.definitions["BUILD_TESTING"] = False
        cmake.definitions["BUILD_SHARED_LIBS"] = self.options.shared

        # enable when automated builds have fixed the issue on windows
        #if self.settings.build_type == "Release":
        #    cmake.definitions["CMAKE_INTERPROCEDURAL_OPTIMIZATION"] = True

        if self._is_win:
            cmake.definitions["MSVC_DYNAMIC_RUNTIME"] = True
            if self.settings.compiler.runtime in ["MT", "MTd"]:
                cmake.definitions["MSVC_DYNAMIC_RUNTIME"] = False

        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
