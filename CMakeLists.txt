cmake_minimum_required(VERSION 3.17)
project(SafeFlushProject C)

set(CMAKE_C_STANDARD 99)

add_executable(SafeFlushProject main.c FlushAPI/Sources/flush.c FlushAPI/Headers/flush.h SafeFlushAPI/Sources/safe_flush.c SafeFlushAPI/Headers/safe_flush.h FlushAPI/Sources/tools.c FlushAPI/Headers/tools.h)
