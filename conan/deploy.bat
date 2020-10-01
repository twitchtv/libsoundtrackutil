
rem Copyright Twitch Interactive, Inc. or its affiliates. All Rights Reserved.
rem SPDX-License-Identifier: MIT

set SOUNDTRACKUTIL_CONAN_LIB_NAME=libsoundtrackutil
set SOUNDTRACKUTIL_CONAN_LIB_VERSION=
set TMP_VERSION=

notepad conanfile.py || goto fail

for /F "delims=" %%i in ('findstr /C:"version = " conanfile.py') do set TMP_VERSION=%%i
set SOUNDTRACKUTIL_CONAN_LIB_VERSION=%TMP_VERSION:~15,-1%
if "%SOUNDTRACKUTIL_CONAN_LIB_VERSION%"=="" goto fail

conan export .
conan install %SOUNDTRACKUTIL_CONAN_LIB_NAME%/%SOUNDTRACKUTIL_CONAN_LIB_VERSION% -s build_type=Release -s compiler.runtime=MT --build=missing
conan install %SOUNDTRACKUTIL_CONAN_LIB_NAME%/%SOUNDTRACKUTIL_CONAN_LIB_VERSION% -s build_type=Debug -s compiler.runtime=MTd --build=missing
rem conan upload %SOUNDTRACKUTIL_CONAN_LIB_NAME%/%SOUNDTRACKUTIL_CONAN_LIB_VERSION% || goto fail

goto end

:fail
echo --- failure ---
goto end

:end