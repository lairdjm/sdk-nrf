#!/usr/bin/env python3
#
# Copyright (c) 2025 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause

import struct
from intelhex import IntelHex
import zlib

def main():
    output = '/tmp/lol'

    images = 2

    address_firmware_loader = 0x8f000
    size_firmware_loader = 0x8000

    address_softdevice = 0xfc000
    size_softdevice = 0x3000

    metadata_data = struct.pack('<B', images)
    metadata_data += bytes(31 * [0])

    metadata_data += struct.pack('<II', address_firmware_loader, size_firmware_loader)
    metadata_data += bytes(56 * [0])

    metadata_data += struct.pack('<II', address_softdevice, size_softdevice)
    metadata_data += bytes(56 * [0])

    checksum = zlib.crc32(metadata_data)
    metadata_data += struct.pack('<I', checksum)

    metadata_address = 0x10000

    ih = IntelHex()
    ih.frombytes(metadata_data, offset=metadata_address)
    ih.write_hex_file(output)

if __name__ == '__main__':
    main()

