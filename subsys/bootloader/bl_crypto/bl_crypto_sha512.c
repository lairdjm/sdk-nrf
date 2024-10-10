/*
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/types.h>
#include <bl_crypto.h>
#include <bl_storage.h>
#include <fw_info.h>
#include <psa/crypto.h>

int bl_sha512_init(bl_sha512_ctx_t * const ctx)
{
	*ctx = psa_hash_operation_init();
	return (int)psa_hash_setup(ctx, PSA_ALG_SHA_512);
}

int bl_sha512_update(bl_sha512_ctx_t *ctx, const uint8_t *data, uint32_t data_len)
{
	return (int)psa_hash_update(ctx, data, data_len);
}

int bl_sha512_finalize(bl_sha512_ctx_t *ctx, uint8_t *output)
{
	size_t hash_length = 0;
	/* Assumes the output buffer is at least the expected size of the hash */
	return (int)psa_hash_finish(ctx, output, PSA_HASH_LENGTH(PSA_ALG_SHA_512), &hash_length);
}

int get_hash(uint8_t *hash, const uint8_t *data, uint32_t data_len, bool external)
{
	bl_sha512_ctx_t ctx;
	int rc;

	rc = bl_sha512_init(&ctx);

	if (rc != 0) {
		return rc;
	}

	rc = bl_sha512_update(&ctx, data, data_len);

	if (rc != 0) {
		return rc;
	}

	rc = bl_sha512_finalize(&ctx, hash);
	return rc;
}

#if 0
#ifndef CONFIG_BL_ROT_VERIFY_EXT_API_REQUIRED
#include <assert.h>
#include <ocrypto_constant_time.h>
#include "bl_crypto_internal.h"

static int verify_truncated_hash(const uint8_t *data, uint32_t data_len, const uint8_t *expected,
				 uint32_t hash_len)
{
	uint8_t hash[CONFIG_SB_HASH_LEN];
	int rc;

	rc = get_hash(hash, data, data_len, false);

	if (rc != 0) {
		return rc;
	} else if (!ocrypto_constant_time_equal(expected, hash, hash_len)) {
		return -EHASHINV;
	}

	return 0;
}

static int verify_signature(const uint8_t *data, uint32_t data_len, const uint8_t *signature,
			    const uint8_t *public_key)
{
	uint8_t hash1[CONFIG_SB_HASH_LEN];
	uint8_t hash2[CONFIG_SB_HASH_LEN];
	int rc;

	rc = get_hash(hash1, data, data_len, false);

	if (rc != 0) {
		return rc;
	}

	rc = get_hash(hash2, hash1, CONFIG_SB_HASH_LEN, false);

	if (rc != 0) {
		return rc;
	}

	return bl_secp256r1_validate(hash2, CONFIG_SB_HASH_LEN, public_key, signature);
}

/* Base implementation, with 'external' parameter. */
//int root_of_trust_verify(
//		const uint8_t *public_key, const uint8_t *public_key_hash,
//		const uint8_t *signature, const uint8_t *firmware,
//		const uint32_t firmware_len, bool external);

/* For use by the bootloader. */
int bl_root_of_trust_verify(const uint8_t *public_key, const uint8_t *public_key_hash,
			    const uint8_t *signature, const uint8_t *firmware,
			    const uint32_t firmware_len)
{
	__ASSERT(public_key && public_key_hash && signature && firmware,
			"A parameter was NULL.");
	int rc = verify_truncated_hash(public_key, CONFIG_SB_PUBLIC_KEY_LEN, public_key_hash,
					   SB_PUBLIC_KEY_HASH_LEN);

	if (rc != 0) {
		return rc;
	}

	return verify_signature(firmware, firmware_len, signature, public_key);
}
#endif
#endif
