/*
 * Copyright (c) 2024 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <errno.h>
#include <zephyr/types.h>
#include <bl_crypto.h>
#include "bl_crypto_internal.h"
#include <psa/crypto.h>
#include <psa/crypto_types.h>
#include <cracen_psa_kmu.h>

#define LOG_LEVEL LOG_LEVEL_DBG
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(smp_sample);

/* List of KMU stored key ids available for NSIB */
#define MAKE_PSA_KMU_KEY_ID(id) PSA_KEY_HANDLE_FROM_CRACEN_KMU_SLOT(CRACEN_KMU_KEY_USAGE_SCHEME_RAW, id)

static psa_key_id_t kmu_key_ids[] =  {
	MAKE_PSA_KMU_KEY_ID(226),
	MAKE_PSA_KMU_KEY_ID(228),
	MAKE_PSA_KMU_KEY_ID(230)
};

#define KMU_KEY_COUNT (sizeof(kmu_key_ids)/sizeof(kmu_key_ids[0]))

int bl_ed25519_validate(const uint8_t *data, uint32_t data_len, const uint8_t *public_key,
			const uint8_t *signature)
{
	ARG_UNUSED(public_key);
	psa_status_t status = PSA_ERROR_BAD_STATE;

	if (!data || (data_len == 0) || public_key || !signature) {
LOG_ERR("e1");
		return -EINVAL;
	}

	/* Initialize PSA Crypto */
	status = psa_crypto_init();

	if (status != PSA_SUCCESS) {
LOG_ERR("e2");
//		BOOT_LOG_ERR("PSA crypto init failed %d", status);
		return -EIO;
	}

	status = PSA_ERROR_BAD_STATE;

	for (int i = 0; i < KMU_KEY_COUNT; ++i) {
		psa_key_id_t kid = kmu_key_ids[i];

LOG_ERR("check key %d", i);
		status = psa_verify_message(kid, PSA_ALG_PURE_EDDSA, data, data_len, signature,
					    CONFIG_SB_SIGNATURE_LEN);

LOG_ERR(" = %d", status);

		if (status == PSA_SUCCESS) {
			return 0;
		}

//		BOOT_LOG_ERR("ED25519 signature verification failed %d", status);
	}

	return -ESIGINV;
}
