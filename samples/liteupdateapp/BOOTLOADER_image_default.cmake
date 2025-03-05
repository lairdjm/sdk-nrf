# Copyright (c) 2023-2025 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause

# This sysbuild CMake file sets the sysbuild controlled settings as properties
# on Zephyr MCUboot / bootloader image.

if(SB_CONFIG_FIRMWARE_LOADER_SIZE GREATER 0)
  set_config_bool(${ZCMAKE_APPLICATION} CONFIG_BOOT_FIRMWARE_LOADER y)
else()
  set_config_bool(${ZCMAKE_APPLICATION} CONFIG_SINGLE_APPLICATION_SLOT y)
endif()

set(keytypes CONFIG_BOOT_SIGNATURE_TYPE_NONE
             CONFIG_BOOT_SIGNATURE_TYPE_RSA
             CONFIG_BOOT_SIGNATURE_TYPE_ECDSA_P256
             CONFIG_BOOT_SIGNATURE_TYPE_ED25519)

if(SB_CONFIG_BOOT_SIGNATURE_TYPE_NONE)
  set(keytype CONFIG_BOOT_SIGNATURE_TYPE_NONE)
elseif(SB_CONFIG_BOOT_SIGNATURE_TYPE_RSA)
  set(keytype CONFIG_BOOT_SIGNATURE_TYPE_RSA)
elseif(SB_CONFIG_BOOT_SIGNATURE_TYPE_ECDSA_P256)
  set(keytype CONFIG_BOOT_SIGNATURE_TYPE_ECDSA_P256)
elseif(SB_CONFIG_BOOT_SIGNATURE_TYPE_ED25519)
  set(keytype CONFIG_BOOT_SIGNATURE_TYPE_ED25519)
endif()

foreach(loopkeytype ${keytypes})
  if("${loopkeytype}" STREQUAL "${keytype}")
    set_config_bool(${ZCMAKE_APPLICATION} ${loopkeytype} y)
  else()
    set_config_bool(${ZCMAKE_APPLICATION} ${loopkeytype} n)
  endif()
endforeach()

# todo: entrance
set_config_bool(${ZCMAKE_APPLICATION} CONFIG_BOOT_FIRMWARE_LOADER_NO_APPLICATION y)
