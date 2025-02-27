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

set(output)
foreach(area ${areas})
math(EXPR tmp_a "${${area}_partition_start}" OUTPUT_FORMAT HEXADECIMAL)
math(EXPR tmp_b "${${area}_partition_size}" OUTPUT_FORMAT HEXADECIMAL)
math(EXPR tmp_c "${${area}_partition_start} + ${${area}_partition_size}" OUTPUT_FORMAT HEXADECIMAL)
#  message(WARNING "que: ${area}: ${tmp_a} for ${tmp_b}")
#  message(WARNING "que: ${area}: ${${area}_partition_start} for ${${area}_partition_size}")
set(output "${output}#define ${area}_PARTITION_PRESENT 1\n")
set(output "${output}#define ${area}_PARTITION_START ${tmp_a}\n")
set(output "${output}#define ${area}_PARTITION_END ${tmp_c}\n")
set(output "${output}#define ${area}_PARTITION_SIZE ${tmp_b}\n")
endforeach()

file(WRITE /tmp/testoutputfile ${output})
