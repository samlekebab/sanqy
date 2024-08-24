# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.4.1)
project(sanqy)
# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add_library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

add_library( # Specifies the name of the library.
             sanqy

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
		../../cpp/././src/daily_status.cpp
		../../cpp/././src/db.cpp
		../../cpp/././src/deck.cpp
		../../cpp/././src/heap.cpp
		../../cpp/././src/lut.cpp
		../../cpp/././src/random_pool.cpp
		../../cpp/././src/sanqy.cpp
		../../cpp/././src/status.cpp
		../../cpp/././lib/src/Backup.cpp
		../../cpp/././lib/src/Column.cpp
		../../cpp/././lib/src/Database.cpp
		../../cpp/././lib/src/Exception.cpp
		../../cpp/././lib/src/Savepoint.cpp
		../../cpp/././lib/src/Statement.cpp
		../../cpp/././lib/src/Transaction.cpp
		../../cpp/././lib/sqlite3/sqlite3.c)

include_directories(
		../../cpp/././header/
		../../cpp/././lib/header/
		../../cpp/././lib/sqlite3/header/
		../../cpp/././include/
		../../cpp/././lib/include/
		../../cpp/././lib/sqlite3/include/
		../../cpp/././
		../../cpp/././lib/
		../../cpp/././lib/sqlite3/
		../../cpp/./usr/include/
		../../cpp/././lib/include/SQLiteCpp)

set_target_properties(sanqy PROPERTIES LINKER_LANGUAGE CXX)
