/*
 * Copyright (c) 2025 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/kernel.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/logging/log.h>
//#include <bootutil/image.h>
#include <zephyr/sys/crc.h>

LOG_MODULE_REGISTER(todo, LOG_LEVEL_DBG);

struct image_data {
	uint32_t start_address;
	uint32_t image_size;
	uint8_t reserved[56];
};

struct image_data_array {
	uint8_t image_count;
	uint8_t reserved[31];
	struct image_data images[];
};

static const uint8_t test_data[] = {
#include "lol.inc"
};

static const struct image_data_array *lol = (struct image_data_array *)test_data;

int main(void)
{
	uint8_t i = 0;
	uint32_t checksum_calculated;
	uint32_t checksum_expected;

	checksum_expected = crc32_ieee(test_data, (sizeof(struct image_data) * lol->image_count) + 32);
	memcpy(&checksum_calculated, (test_data + (sizeof(struct image_data) * lol->image_count) + 32), sizeof(checksum_calculated));

	LOG_ERR("checksum (calculated): %u", checksum_calculated);
	LOG_ERR("checksum (expected): %u", checksum_expected);

	if (checksum_calculated == checksum_expected) {
		LOG_ERR("Images: %d", lol->image_count);

		while (i < lol->image_count) {
			LOG_ERR("Image %d:", i);
			LOG_ERR("\tStart address: 0x%x:", lol->images[i].start_address);
			LOG_ERR("\tSize: 0x%x:", lol->images[i].image_size);
			++i;
		}
	} else {
		LOG_ERR("Checksum mismatch");
	}

	return 0;
}
