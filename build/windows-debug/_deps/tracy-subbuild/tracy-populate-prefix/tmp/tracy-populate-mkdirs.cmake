# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Programming/WilloEngine/build/windows-debug/_deps/tracy-src"
  "D:/Programming/WilloEngine/build/windows-debug/_deps/tracy-build"
  "D:/Programming/WilloEngine/build/windows-debug/_deps/tracy-subbuild/tracy-populate-prefix"
  "D:/Programming/WilloEngine/build/windows-debug/_deps/tracy-subbuild/tracy-populate-prefix/tmp"
  "D:/Programming/WilloEngine/build/windows-debug/_deps/tracy-subbuild/tracy-populate-prefix/src/tracy-populate-stamp"
  "D:/Programming/WilloEngine/build/windows-debug/_deps/tracy-subbuild/tracy-populate-prefix/src"
  "D:/Programming/WilloEngine/build/windows-debug/_deps/tracy-subbuild/tracy-populate-prefix/src/tracy-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Programming/WilloEngine/build/windows-debug/_deps/tracy-subbuild/tracy-populate-prefix/src/tracy-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Programming/WilloEngine/build/windows-debug/_deps/tracy-subbuild/tracy-populate-prefix/src/tracy-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
