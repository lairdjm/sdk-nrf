#
# Copyright (c) 2025 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

math(EXPR mcuboot_partition_size "${SB_CONFIG_MCUBOOT_SIZE}" OUTPUT_FORMAT DECIMAL)
math(EXPR file_system_partition_size "${SB_CONFIG_FILE_SYSTEM_SIZE}" OUTPUT_FORMAT DECIMAL)
math(EXPR metadata_partition_size "${SB_CONFIG_METADATA_SIZE}" OUTPUT_FORMAT DECIMAL)
math(EXPR firmware_loader_partition_size "${SB_CONFIG_FIRMWARE_LOADER_SIZE}" OUTPUT_FORMAT DECIMAL)
math(EXPR softdevice_partition_size "${SB_CONFIG_SOFTDEVICE_SIZE}" OUTPUT_FORMAT DECIMAL)
math(EXPR installer_partition_size "${SB_CONFIG_INSTALLER_SIZE}" OUTPUT_FORMAT DECIMAL)
math(EXPR flash_size "${SB_CONFIG_FLASH_SIZE}" OUTPUT_FORMAT DECIMAL)
set(flash_size_remaining ${flash_size})
set(areas)

if(metadata_partition_size GREATER "0")
  math(EXPR flash_size_remaining "${flash_size_remaining} - ${metadata_partition_size}")
  math(EXPR metadata_partition_start "${flash_size} - ${metadata_partition_size}")
  list(APPEND areas metadata)
endif()

if(softdevice_partition_size GREATER "0")
  math(EXPR flash_size_remaining "${flash_size_remaining} - ${softdevice_partition_size}")
  math(EXPR softdevice_partition_start "${flash_size_remaining} - ${metadata_partition_size}")
  list(APPEND areas softdevice)
endif()

if(mcuboot_partition_size GREATER "0")
  if(firmware_loader_partition_size GREATER "0")
    # Firmware loader present
    math(EXPR flash_size_remaining "${flash_size_remaining} - ${firmware_loader_partition_size}")
    math(EXPR firmware_loader_partition_start "${flash_size_remaining} - ${firmware_loader_partition_size}")
    list(APPEND areas firmware_loader)
  endif()

  # MCUboot present
  math(EXPR flash_size_remaining "${flash_size_remaining} - ${mcuboot_partition_size}")
  set(mcuboot_partition_start 0)
  list(APPEND areas mcuboot)
endif()

set(app_partition_start ${mcuboot_partition_size})

if(file_system_partition_size GREATER "0")
  math(EXPR flash_size_remaining "${flash_size_remaining} - ${file_system_partition_size}")
  math(EXPR file_system_partition_start "${app_partition_start} + ${flash_size_remaining}")
  list(APPEND areas file_system)
endif()

set(app_partition_size ${flash_size_remaining})
list(APPEND areas app)

math(EXPR tmp_a "${app_partition_start}" OUTPUT_FORMAT HEXADECIMAL)
math(EXPR tmp_b "${flash_size_remaining}" OUTPUT_FORMAT HEXADECIMAL)
set_config_bool(liteupdateapp CONFIG_BLAH3 y)
set_config_int(liteupdateapp CONFIG_BLAH1 ${tmp_a})
set_config_int(liteupdateapp CONFIG_BLAH2 ${tmp_b})

if(firmware_loader_partition_size GREATER "0")
  math(EXPR installer_partition_start "${app_partition_start}")
  list(APPEND areas installer)
endif()

if(app_partition_size LESS "4096")
  math(EXPR tmp_a "0 - ${app_partition_size}" OUTPUT_FORMAT HEXADECIMAL)
  message(WARNING "Partitioning is not valid, non-volatile overlay: ${tmp_a} bytes")
else()
  set(output)

  foreach(area ${areas})
    math(EXPR tmp_a "${${area}_partition_start}" OUTPUT_FORMAT HEXADECIMAL)
    math(EXPR tmp_b "${${area}_partition_size}" OUTPUT_FORMAT HEXADECIMAL)
    math(EXPR tmp_c "${${area}_partition_start} + ${${area}_partition_size}" OUTPUT_FORMAT HEXADECIMAL)
    string(TOUPPER "${area}" tmp_d)
    set(output "${output}#define ${tmp_d}_PARTITION_PRESENT 1\n")
    set(output "${output}#define ${tmp_d}_PARTITION_START ${tmp_a}\n")
    set(output "${output}#define ${tmp_d}_PARTITION_END ${tmp_c}\n")
    set(output "${output}#define ${tmp_d}_PARTITION_SIZE ${tmp_b}\n")
  endforeach()

  file(WRITE /tmp/testoutputfile ${output})
endif()

if(SB_CONFIG_BOOTLOADER_MCUBOOT)
  # Remove Zephyr supplied bootloader configuration script and replace with our own
  get_property(tmp_conf_scripts TARGET mcuboot PROPERTY IMAGE_CONF_SCRIPT)
  set(default_bootloader_script "${CMAKE_SOURCE_DIR}/image_configurations/BOOTLOADER_image_default.cmake")

  if(default_bootloader_script IN_LIST tmp_conf_scripts)
    list(REMOVE_ITEM tmp_conf_scripts ${default_bootloader_script})
  endif()

  list(APPEND tmp_conf_scripts "${CMAKE_CURRENT_LIST_DIR}/BOOTLOADER_image_default.cmake")
  set_target_properties(mcuboot PROPERTIES IMAGE_CONF_SCRIPT "${tmp_conf_scripts}")
endif()
