#!/usr/bin/env python3
#
# Copyright (c) 2025 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause

import os
import struct
from intelhex import IntelHex
import zlib

class KConfig(dict):
    @classmethod
    def from_file(cls, filename):
        """
        Extracts content of '.config' file into a dictionary

        Parameters:
            config_path (str): Path to '.config' file used by a firmware
        Returns:
            cls: A KConfig object where keys are Kconfig option names and values
            are option values, parsed from the config file at config_path.
        """
        configs = cls()
        try:
            with open(filename, 'r') as config:
                for line in config:
                    if not (line.startswith("CONFIG_") or line.startswith("SB_CONFIG_")):
                        continue
                    kconfig, value = line.split("=", 1)
                    configs[kconfig] = value.strip()
                return configs
        except Exception as err :
            raise Exception("Unable to parse .config file") from err

class Defines(dict):
    @classmethod
    def from_file(cls, filename):
        """
        Extracts content of '.config' file into a dictionary

        Parameters:
            config_path (str): Path to '.config' file used by a firmware
        Returns:
            cls: A KConfig object where keys are Kconfig option names and values
            are option values, parsed from the config file at config_path.
        """
        configs = cls()
        try:
            with open(filename, 'r') as config:
                for line in config:
                    if not (line.startswith("#define")):
                        continue
                    kconfig, value = line[8:].split(" ", 1)
                    configs[kconfig] = value.strip()
                return configs
        except Exception as err :
            raise Exception("Unable to parse .config file") from err

def main():
    output = '/tmp/lol'

#    sysbuild_config_path = os.path.abspath(os.path.join(args.bin_path, '..', '..', 'zephyr', '.config'))
#    sysbuild_config_path = os.path.abspath(os.path.join('zephyr', '.config'))
    sysbuild_config_path = os.path.abspath('/tmp/testoutputfile')
#    print(sysbuild_config_path)
#    sysbuild_kconfigs = KConfig.from_file(sysbuild_config_path)
    sysbuild_kconfigs = Defines.from_file(sysbuild_config_path)
#    print(sysbuild_kconfigs)

#    print(sysbuild_kconfigs['SB_CONFIG_FIRMWARE_LOADER_SIZE'])
#    print(sysbuild_kconfigs['SB_CONFIG_SOFTDEVICE_SIZE'])

    images = 0

    if 'firmware_loader_PARTITION_PRESENT' in sysbuild_kconfigs:
        images = images + 1

    if 'softdevice_PARTITION_PRESENT' in sysbuild_kconfigs:
        images = images + 1

#    address_firmware_loader = 0x8f000
#    size_firmware_loader = 0x8000

#    address_softdevice = 0xfc000
#    size_softdevice = 0x3000

#SB_CONFIG_FIRMWARE_LOADER_SIZE=0x8000
#SB_CONFIG_SOFTDEVICE_SIZE=0x0

    metadata_data = struct.pack('<B', images)
    metadata_data += bytes(31 * [0])

    if 'firmware_loader_PARTITION_PRESENT' in sysbuild_kconfigs:
        address_firmware_loader = int(sysbuild_kconfigs['firmware_loader_PARTITION_START'], 16)
        size_firmware_loader = int(sysbuild_kconfigs['firmware_loader_PARTITION_SIZE'], 16)
        metadata_data += struct.pack('<II', address_firmware_loader, size_firmware_loader)
        metadata_data += bytes(56 * [0])

    if 'softdevice_PARTITION_PRESENT' in sysbuild_kconfigs:
        address_softdevice = int(sysbuild_kconfigs['softdevice_PARTITION_START'], 16)
        size_softdevice = int(sysbuild_kconfigs['softdevice_PARTITION_SIZE'], 16)
        metadata_data += struct.pack('<II', address_softdevice, size_softdevice)
        metadata_data += bytes(56 * [0])

    checksum = zlib.crc32(metadata_data)
    metadata_data += struct.pack('<I', checksum)

    metadata_address = int(sysbuild_kconfigs['installer_PARTITION_START'], 16) + int(sysbuild_kconfigs['installer_PARTITION_SIZE'], 16)

    ih = IntelHex()
    ih.frombytes(metadata_data, offset=metadata_address)
    ih.write_hex_file(output)

if __name__ == '__main__':
    main()
