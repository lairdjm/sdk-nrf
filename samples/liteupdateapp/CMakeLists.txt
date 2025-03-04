#
# Copyright (c) 2024 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(mcuboot_update)

# This project uses orginal sdk-zephyr C source code
target_sources(app PRIVATE src/main.c)
#zephyr_link_libraries(MCUBOOT_BOOTUTIL)

set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)

  generate_inc_file_for_target(
    app
    /tmp/dummyinput.bin
    ${gen_dir}/dummyinput.inc
    )
