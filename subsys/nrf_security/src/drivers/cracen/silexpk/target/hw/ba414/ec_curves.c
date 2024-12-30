/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <silexpk/ec_curves.h>
#include "../../../src/regs_curves.h"
#include "../../target/hw/ba414/regs_commands.h"
#include <silexpk/core.h>
#include <string.h>

#define SX_MAX(p, q) ((p >= q) ? p : q)

static const unsigned char params_nistp192[] = {
	/* q */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	/* n */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x99, 0xde, 0xf8,
	0x36, 0x14, 0x6b, 0xc9, 0xb1, 0xb4, 0xd2, 0x28, 0x31,
	/* gx */
	0x18, 0x8d, 0xa8, 0x0e, 0xb0, 0x30, 0x90, 0xf6, 0x7c, 0xbf, 0x20, 0xeb, 0x43, 0xa1, 0x88,
	0x00, 0xf4, 0xff, 0x0a, 0xfd, 0x82, 0xff, 0x10, 0x12,
	/* gy */
	0x07, 0x19, 0x2b, 0x95, 0xff, 0xc8, 0xda, 0x78, 0x63, 0x10, 0x11, 0xed, 0x6b, 0x24, 0xcd,
	0xd5, 0x73, 0xf9, 0x77, 0xa1, 0x1e, 0x79, 0x48, 0x11,
	/* a */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
	/* b */
	0x64, 0x21, 0x05, 0x19, 0xe5, 0x9c, 0x80, 0xe7, 0x0f, 0xa7, 0xe9, 0xab, 0x72, 0x24, 0x30,
	0x49, 0xfe, 0xb8, 0xde, 0xec, 0xc1, 0x46, 0xb9, 0xb1};

const struct sx_pk_ecurve sx_curve_nistp192 = {.curveflags = PK_OP_FLAGS_PRIME |
							     PK_OP_FLAGS_SELCUR_P192,
					       .sz = 24,
					       .params = (char *)params_nistp192};

static const unsigned char params_nistp224[] = {
	/* q */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	/* n */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x16,
	0xa2, 0xe0, 0xb8, 0xf0, 0x3e, 0x13, 0xdd, 0x29, 0x45, 0x5c, 0x5c, 0x2a, 0x3d,
	/* gx */
	0xb7, 0x0e, 0x0c, 0xbd, 0x6b, 0xb4, 0xbf, 0x7f, 0x32, 0x13, 0x90, 0xb9, 0x4a, 0x03, 0xc1,
	0xd3, 0x56, 0xc2, 0x11, 0x22, 0x34, 0x32, 0x80, 0xd6, 0x11, 0x5c, 0x1d, 0x21,
	/* gy */
	0xbd, 0x37, 0x63, 0x88, 0xb5, 0xf7, 0x23, 0xfb, 0x4c, 0x22, 0xdf, 0xe6, 0xcd, 0x43, 0x75,
	0xa0, 0x5a, 0x07, 0x47, 0x64, 0x44, 0xd5, 0x81, 0x99, 0x85, 0x00, 0x7e, 0x34,
	/* a */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
	/* b */
	0xb4, 0x05, 0x0a, 0x85, 0x0c, 0x04, 0xb3, 0xab, 0xf5, 0x41, 0x32, 0x56, 0x50, 0x44, 0xb0,
	0xb7, 0xd7, 0xbf, 0xd8, 0xba, 0x27, 0x0b, 0x39, 0x43, 0x23, 0x55, 0xff, 0xb4};

const struct sx_pk_ecurve sx_curve_nistp224 = {
	.curveflags = PK_OP_FLAGS_PRIME, .sz = 28, .params = (char *)params_nistp224};

static const unsigned char params_nistp256[] = {
	/* q */
	0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff,
	/* n */
	0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xbc, 0xe6, 0xfa, 0xad, 0xa7, 0x17, 0x9e, 0x84, 0xf3, 0xb9, 0xca, 0xc2, 0xfc, 0x63,
	0x25, 0x51,
	/* gx */
	0x6b, 0x17, 0xd1, 0xf2, 0xe1, 0x2c, 0x42, 0x47, 0xf8, 0xbc, 0xe6, 0xe5, 0x63, 0xa4, 0x40,
	0xf2, 0x77, 0x03, 0x7d, 0x81, 0x2d, 0xeb, 0x33, 0xa0, 0xf4, 0xa1, 0x39, 0x45, 0xd8, 0x98,
	0xc2, 0x96,
	/* gy */
	0x4f, 0xe3, 0x42, 0xe2, 0xfe, 0x1a, 0x7f, 0x9b, 0x8e, 0xe7, 0xeb, 0x4a, 0x7c, 0x0f, 0x9e,
	0x16, 0x2b, 0xce, 0x33, 0x57, 0x6b, 0x31, 0x5e, 0xce, 0xcb, 0xb6, 0x40, 0x68, 0x37, 0xbf,
	0x51, 0xf5,
	/* a */
	0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xfc,
	/* b */
	0x5a, 0xc6, 0x35, 0xd8, 0xaa, 0x3a, 0x93, 0xe7, 0xb3, 0xeb, 0xbd, 0x55, 0x76, 0x98, 0x86,
	0xbc, 0x65, 0x1d, 0x06, 0xb0, 0xcc, 0x53, 0xb0, 0xf6, 0x3b, 0xce, 0x3c, 0x3e, 0x27, 0xd2,
	0x60, 0x4b};

const struct sx_pk_ecurve sx_curve_nistp256 = {.curveflags = PK_OP_FLAGS_PRIME |
							     PK_OP_FLAGS_SELCUR_P256,
					       .sz = 32,
					       .params = (char *)params_nistp256};

static const unsigned char params_nistp384[] = {
	/* q */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
	0xff, 0xff, 0xff,
	/* n */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x63, 0x4d, 0x81, 0xf4, 0x37,
	0x2d, 0xdf, 0x58, 0x1a, 0x0d, 0xb2, 0x48, 0xb0, 0xa7, 0x7a, 0xec, 0xec, 0x19, 0x6a, 0xcc,
	0xc5, 0x29, 0x73,
	/* gx */
	0xaa, 0x87, 0xca, 0x22, 0xbe, 0x8b, 0x05, 0x37, 0x8e, 0xb1, 0xc7, 0x1e, 0xf3, 0x20, 0xad,
	0x74, 0x6e, 0x1d, 0x3b, 0x62, 0x8b, 0xa7, 0x9b, 0x98, 0x59, 0xf7, 0x41, 0xe0, 0x82, 0x54,
	0x2a, 0x38, 0x55, 0x02, 0xf2, 0x5d, 0xbf, 0x55, 0x29, 0x6c, 0x3a, 0x54, 0x5e, 0x38, 0x72,
	0x76, 0x0a, 0xb7,
	/* gy */
	0x36, 0x17, 0xde, 0x4a, 0x96, 0x26, 0x2c, 0x6f, 0x5d, 0x9e, 0x98, 0xbf, 0x92, 0x92, 0xdc,
	0x29, 0xf8, 0xf4, 0x1d, 0xbd, 0x28, 0x9a, 0x14, 0x7c, 0xe9, 0xda, 0x31, 0x13, 0xb5, 0xf0,
	0xb8, 0xc0, 0x0a, 0x60, 0xb1, 0xce, 0x1d, 0x7e, 0x81, 0x9d, 0x7a, 0x43, 0x1d, 0x7c, 0x90,
	0xea, 0x0e, 0x5f,
	/* a */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
	0xff, 0xff, 0xfc,
	/* b */
	0xb3, 0x31, 0x2f, 0xa7, 0xe2, 0x3e, 0xe7, 0xe4, 0x98, 0x8e, 0x05, 0x6b, 0xe3, 0xf8, 0x2d,
	0x19, 0x18, 0x1d, 0x9c, 0x6e, 0xfe, 0x81, 0x41, 0x12, 0x03, 0x14, 0x08, 0x8f, 0x50, 0x13,
	0x87, 0x5a, 0xc6, 0x56, 0x39, 0x8d, 0x8a, 0x2e, 0xd1, 0x9d, 0x2a, 0x85, 0xc8, 0xed, 0xd3,
	0xec, 0x2a, 0xef};

const struct sx_pk_ecurve sx_curve_nistp384 = {.curveflags = PK_OP_FLAGS_PRIME |
							     PK_OP_FLAGS_SELCUR_P384,
					       .sz = 48,
					       .params = (char *)params_nistp384};

static const unsigned char params_nistp521[] = {
	/* q */
	0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	/* n */
	0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xfa, 0x51, 0x86, 0x87, 0x83, 0xbf, 0x2f, 0x96, 0x6b, 0x7f, 0xcc, 0x01,
	0x48, 0xf7, 0x09, 0xa5, 0xd0, 0x3b, 0xb5, 0xc9, 0xb8, 0x89, 0x9c, 0x47, 0xae, 0xbb, 0x6f,
	0xb7, 0x1e, 0x91, 0x38, 0x64, 0x09,
	/* gx */
	0x00, 0xc6, 0x85, 0x8e, 0x06, 0xb7, 0x04, 0x04, 0xe9, 0xcd, 0x9e, 0x3e, 0xcb, 0x66, 0x23,
	0x95, 0xb4, 0x42, 0x9c, 0x64, 0x81, 0x39, 0x05, 0x3f, 0xb5, 0x21, 0xf8, 0x28, 0xaf, 0x60,
	0x6b, 0x4d, 0x3d, 0xba, 0xa1, 0x4b, 0x5e, 0x77, 0xef, 0xe7, 0x59, 0x28, 0xfe, 0x1d, 0xc1,
	0x27, 0xa2, 0xff, 0xa8, 0xde, 0x33, 0x48, 0xb3, 0xc1, 0x85, 0x6a, 0x42, 0x9b, 0xf9, 0x7e,
	0x7e, 0x31, 0xc2, 0xe5, 0xbd, 0x66,
	/* gy */
	0x01, 0x18, 0x39, 0x29, 0x6a, 0x78, 0x9a, 0x3b, 0xc0, 0x04, 0x5c, 0x8a, 0x5f, 0xb4, 0x2c,
	0x7d, 0x1b, 0xd9, 0x98, 0xf5, 0x44, 0x49, 0x57, 0x9b, 0x44, 0x68, 0x17, 0xaf, 0xbd, 0x17,
	0x27, 0x3e, 0x66, 0x2c, 0x97, 0xee, 0x72, 0x99, 0x5e, 0xf4, 0x26, 0x40, 0xc5, 0x50, 0xb9,
	0x01, 0x3f, 0xad, 0x07, 0x61, 0x35, 0x3c, 0x70, 0x86, 0xa2, 0x72, 0xc2, 0x40, 0x88, 0xbe,
	0x94, 0x76, 0x9f, 0xd1, 0x66, 0x50,
	/* a */
	0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
	/* b */
	0x00, 0x51, 0x95, 0x3e, 0xb9, 0x61, 0x8e, 0x1c, 0x9a, 0x1f, 0x92, 0x9a, 0x21, 0xa0, 0xb6,
	0x85, 0x40, 0xee, 0xa2, 0xda, 0x72, 0x5b, 0x99, 0xb3, 0x15, 0xf3, 0xb8, 0xb4, 0x89, 0x91,
	0x8e, 0xf1, 0x09, 0xe1, 0x56, 0x19, 0x39, 0x51, 0xec, 0x7e, 0x93, 0x7b, 0x16, 0x52, 0xc0,
	0xbd, 0x3b, 0xb1, 0xbf, 0x07, 0x35, 0x73, 0xdf, 0x88, 0x3d, 0x2c, 0x34, 0xf1, 0xef, 0x45,
	0x1f, 0xd4, 0x6b, 0x50, 0x3f, 0x00};

const struct sx_pk_ecurve sx_curve_nistp521 = {.curveflags = PK_OP_FLAGS_PRIME |
							     PK_OP_FLAGS_SELCUR_P521,
					       .sz = 66,
					       .params = (char *)params_nistp521};

static const char params_ed25519[32 * 6] =
	/* q */
	"\xed\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
	"\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x7f"
	/* l */
	"\xED\xD3\xF5\x5C\x1A\x63\x12\x58\xD6\x9C\xF7\xA2\xDE\xF9\xDE\x14"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x10"
	/* bx (aka Gx) */
	"\x1a\xd5\x25\x8f\x60\x2d\x56\xc9\xb2\xa7\x25\x95\x60\xc7\x2c\x69"
	"\x5c\xdc\xd6\xfd\x31\xe2\xa4\xc0\xfe\x53\x6e\xcd\xd3\x36\x69\x21"
	/* by (aka Gy */
	"\x58\x66\x66\x66\x66\x66\x66\x66\x66\x66\x66\x66\x66\x66\x66\x66"
	"\x66\x66\x66\x66\x66\x66\x66\x66\x66\x66\x66\x66\x66\x66\x66\x66"
	/* d */
	"\xA3\x78\x59\x13\xCA\x4D\xEB\x75\xAB\xD8\x41\x41\x4D\x0A\x70\x00"
	"\x98\xE8\x79\x77\x79\x40\xC7\x8C\x73\xFE\x6F\x2B\xEE\x6C\x03\x52"
	/* i */
	"\xB0\xA0\x0E\x4A\x27\x1B\xEE\xC4\x78\xE4\x2F\xAD\x06\x18\x43\x2F"
	"\xA7\xD7\xFB\x3D\x99\x00\x4D\x2B\x0B\xDF\xC1\x4F\x80\x24\x83\x2B";
const struct sx_pk_ecurve sx_curve_ed25519 = {
	.curveflags = PK_OP_FLAGS_SELCUR_ED25519, .sz = 32, .params = params_ed25519};

const unsigned char params_ed448[57 * 5] = {
	/* q = */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
	/* l = */
	0xf3, 0x44, 0x58, 0xab, 0x92, 0xc2, 0x78, 0x23, 0x55, 0x8f, 0xc5, 0x8d, 0x72, 0xc2, 0x6c,
	0x21, 0x90, 0x36, 0xd6, 0xae, 0x49, 0xdb, 0x4e, 0xc4, 0xe9, 0x23, 0xca, 0x7c, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00,
	/* Bx = */
	0x5e, 0xc0, 0x0c, 0xc7, 0x2b, 0xa8, 0x26, 0x26, 0x8e, 0x93, 0x00, 0x8b, 0xe1, 0x80, 0x3b,
	0x43, 0x11, 0x65, 0xb6, 0x2a, 0xf7, 0x1a, 0xae, 0x12, 0x64, 0xa4, 0xd3, 0xa3, 0x24, 0xe3,
	0x6d, 0xea, 0x67, 0x17, 0x0f, 0x47, 0x70, 0x65, 0x14, 0x9e, 0xda, 0x36, 0xbf, 0x22, 0xa6,
	0x15, 0x1d, 0x22, 0xed, 0x0d, 0xed, 0x6b, 0xc6, 0x70, 0x19, 0x4f, 0x00,
	/* By = */
	0x14, 0xfa, 0x30, 0xf2, 0x5b, 0x79, 0x08, 0x98, 0xad, 0xc8, 0xd7, 0x4e, 0x2c, 0x13, 0xbd,
	0xfd, 0xc4, 0x39, 0x7c, 0xe6, 0x1c, 0xff, 0xd3, 0x3a, 0xd7, 0xc2, 0xa0, 0x05, 0x1e, 0x9c,
	0x78, 0x87, 0x40, 0x98, 0xa3, 0x6c, 0x73, 0x73, 0xea, 0x4b, 0x62, 0xc7, 0xc9, 0x56, 0x37,
	0x20, 0x76, 0x88, 0x24, 0xbc, 0xb6, 0x6e, 0x71, 0x46, 0x3f, 0x69, 0x00,
	/* d = */
	0x56, 0x67, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00};
const struct sx_pk_ecurve sx_curve_ed448 = {
	.curveflags = PK_OP_FLAGS_EDWARDS_448, .sz = 57, .params = (char *)params_ed448};

static const char params_x25519[32 * 2] =
	/* p */
	"\xED\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
	"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x7F"
	/* a */
	"\x06\x6d\x07\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
const struct sx_pk_ecurve sx_curve_x25519 = {
	.curveflags = PK_OP_FLAGS_SELCUR_X25519, .sz = 32, .params = params_x25519};

static const char params_x448[56 * 2] =
	/* p = 2^448 - 2^224 - 1 = */
	"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
	"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFE\xFF\xFF\xFF"
	"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
	"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
	/* a = 156326 = */
	"\xA6\x62\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00";
const struct sx_pk_ecurve sx_curve_x448 = {.curveflags = 0, .sz = 56, .params = params_x448};

static const char params_brainpoolP192r1[] =
	/* q */
	"\xc3\x02\xf4\x1d\x93\x2a\x36\xcd\xa7\xa3\x46\x30\x93\xd1\x8d\xb7\x8f"
	"\xce\x47\x6d\xe1\xa8\x62\x97"
	/* n */
	"\xc3\x02\xf4\x1d\x93\x2a\x36\xcd\xa7\xa3\x46\x2f\x9e\x9e\x91\x6b\x5b"
	"\xe8\xf1\x02\x9a\xc4\xac\xc1"
	/* Gx */
	"\xc0\xa0\x64\x7e\xaa\xb6\xa4\x87\x53\xb0\x33\xc5\x6c\xb0\xf0\x90\x0a"
	"\x2f\x5c\x48\x53\x37\x5f\xd6"
	/* Gy */
	"\x14\xb6\x90\x86\x6a\xbd\x5b\xb8\x8b\x5f\x48\x28\xc1\x49\x00\x02\xe6"
	"\x77\x3f\xa2\xfa\x29\x9b\x8f"
	/* a */
	"\x6a\x91\x17\x40\x76\xb1\xe0\xe1\x9c\x39\xc0\x31\xfe\x86\x85\xc1\xca"
	"\xe0\x40\xe5\xc6\x9a\x28\xef"
	/* b */
	"\x46\x9a\x28\xef\x7c\x28\xcc\xa3\xdc\x72\x1d\x04\x4f\x44\x96\xbc\xca"
	"\x7e\xf4\x14\x6f\xbf\x25\xc9";
const struct sx_pk_ecurve sx_curve_brainpoolP192r1 = {
	.curveflags = PK_OP_FLAGS_PRIME, .sz = 24, .params = params_brainpoolP192r1};

static const char params_brainpoolP224r1[] =
	/* q */
	"\xd7\xc1\x34\xaa\x26\x43\x66\x86\x2a\x18\x30\x25\x75\xd1\xd7\x87\xb0"
	"\x9f\x07\x57\x97\xda\x89\xf5\x7e\xc8\xc0\xff"
	/* n */
	"\xd7\xc1\x34\xaa\x26\x43\x66\x86\x2a\x18\x30\x25\x75\xd0\xfb\x98\xd1"
	"\x16\xbc\x4b\x6d\xde\xbc\xa3\xa5\xa7\x93\x9f"
	/* Gx */
	"\x0d\x90\x29\xad\x2c\x7e\x5c\xf4\x34\x08\x23\xb2\xa8\x7d\xc6\x8c\x9e"
	"\x4c\xe3\x17\x4c\x1e\x6e\xfd\xee\x12\xc0\x7d"
	/* Gy */
	"\x58\xaa\x56\xf7\x72\xc0\x72\x6f\x24\xc6\xb8\x9e\x4e\xcd\xac\x24\x35"
	"\x4b\x9e\x99\xca\xa3\xf6\xd3\x76\x14\x02\xcd"
	/* a */
	"\x68\xa5\xe6\x2c\xa9\xce\x6c\x1c\x29\x98\x03\xa6\xc1\x53\x0b\x51\x4e"
	"\x18\x2a\xd8\xb0\x04\x2a\x59\xca\xd2\x9f\x43"
	/* b */
	"\x25\x80\xf6\x3c\xcf\xe4\x41\x38\x87\x07\x13\xb1\xa9\x23\x69\xe3\x3e"
	"\x21\x35\xd2\x66\xdb\xb3\x72\x38\x6c\x40\x0b";
const struct sx_pk_ecurve sx_curve_brainpoolP224r1 = {
	.curveflags = PK_OP_FLAGS_PRIME, .sz = 28, .params = params_brainpoolP224r1};

static const char params_brainpoolP256r1[] =
	/* q */
	"\xa9\xfb\x57\xdb\xa1\xee\xa9\xbc\x3e\x66\x0a\x90\x9d\x83\x8d\x72\x6e"
	"\x3b\xf6\x23\xd5\x26\x20\x28\x20\x13\x48\x1d\x1f\x6e\x53\x77"
	/* n */
	"\xa9\xfb\x57\xdb\xa1\xee\xa9\xbc\x3e\x66\x0a\x90\x9d\x83\x8d\x71\x8c"
	"\x39\x7a\xa3\xb5\x61\xa6\xf7\x90\x1e\x0e\x82\x97\x48\x56\xa7"
	/* Gx */
	"\x8b\xd2\xae\xb9\xcb\x7e\x57\xcb\x2c\x4b\x48\x2f\xfc\x81\xb7\xaf\xb9"
	"\xde\x27\xe1\xe3\xbd\x23\xc2\x3a\x44\x53\xbd\x9a\xce\x32\x62"
	/* Gy */
	"\x54\x7e\xf8\x35\xc3\xda\xc4\xfd\x97\xf8\x46\x1a\x14\x61\x1d\xc9\xc2"
	"\x77\x45\x13\x2d\xed\x8e\x54\x5c\x1d\x54\xc7\x2f\x04\x69\x97"
	/* a */
	"\x7d\x5a\x09\x75\xfc\x2c\x30\x57\xee\xf6\x75\x30\x41\x7a\xff\xe7\xfb"
	"\x80\x55\xc1\x26\xdc\x5c\x6c\xe9\x4a\x4b\x44\xf3\x30\xb5\xd9"
	/* b */
	"\x26\xdc\x5c\x6c\xe9\x4a\x4b\x44\xf3\x30\xb5\xd9\xbb\xd7\x7c\xbf\x95"
	"\x84\x16\x29\x5c\xf7\xe1\xce\x6b\xcc\xdc\x18\xff\x8c\x07\xb6";
const struct sx_pk_ecurve sx_curve_brainpoolP256r1 = {
	.curveflags = PK_OP_FLAGS_PRIME, .sz = 32, .params = params_brainpoolP256r1};

static const char params_brainpoolP320r1[] =
	/* q */
	"\xd3\x5e\x47\x20\x36\xbc\x4f\xb7\xe1\x3c\x78\x5e\xd2\x01\xe0\x65\xf9"
	"\x8f\xcf\xa6\xf6\xf4\x0d\xef\x4f\x92\xb9\xec\x78\x93\xec\x28\xfc\xd4"
	"\x12\xb1\xf1\xb3\x2e\x27"
	/* n */
	"\xd3\x5e\x47\x20\x36\xbc\x4f\xb7\xe1\x3c\x78\x5e\xd2\x01\xe0\x65\xf9"
	"\x8f\xcf\xa5\xb6\x8f\x12\xa3\x2d\x48\x2e\xc7\xee\x86\x58\xe9\x86\x91"
	"\x55\x5b\x44\xc5\x93\x11"
	/* Gx */
	"\x43\xbd\x7e\x9a\xfb\x53\xd8\xb8\x52\x89\xbc\xc4\x8e\xe5\xbf\xe6\xf2"
	"\x01\x37\xd1\x0a\x08\x7e\xb6\xe7\x87\x1e\x2a\x10\xa5\x99\xc7\x10\xaf"
	"\x8d\x0d\x39\xe2\x06\x11"
	/* Gy */
	"\x14\xfd\xd0\x55\x45\xec\x1c\xc8\xab\x40\x93\x24\x7f\x77\x27\x5e\x07"
	"\x43\xff\xed\x11\x71\x82\xea\xa9\xc7\x78\x77\xaa\xac\x6a\xc7\xd3\x52"
	"\x45\xd1\x69\x2e\x8e\xe1"
	/* a */
	"\x3e\xe3\x0b\x56\x8f\xba\xb0\xf8\x83\xcc\xeb\xd4\x6d\x3f\x3b\xb8\xa2"
	"\xa7\x35\x13\xf5\xeb\x79\xda\x66\x19\x0e\xb0\x85\xff\xa9\xf4\x92\xf3"
	"\x75\xa9\x7d\x86\x0e\xb4"
	/* b */
	"\x52\x08\x83\x94\x9d\xfd\xbc\x42\xd3\xad\x19\x86\x40\x68\x8a\x6f\xe1"
	"\x3f\x41\x34\x95\x54\xb4\x9a\xcc\x31\xdc\xcd\x88\x45\x39\x81\x6f\x5e"
	"\xb4\xac\x8f\xb1\xf1\xa6";
const struct sx_pk_ecurve sx_curve_brainpoolP320r1 = {
	.curveflags = PK_OP_FLAGS_PRIME, .sz = 40, .params = params_brainpoolP320r1};

static const char params_brainpoolP384r1[] =
	/* q */
	"\x8c\xb9\x1e\x82\xa3\x38\x6d\x28\x0f\x5d\x6f\x7e\x50\xe6\x41\xdf\x15"
	"\x2f\x71\x09\xed\x54\x56\xb4\x12\xb1\xda\x19\x7f\xb7\x11\x23\xac\xd3"
	"\xa7\x29\x90\x1d\x1a\x71\x87\x47\x00\x13\x31\x07\xec\x53"
	/* n */
	"\x8c\xb9\x1e\x82\xa3\x38\x6d\x28\x0f\x5d\x6f\x7e\x50\xe6\x41\xdf\x15"
	"\x2f\x71\x09\xed\x54\x56\xb3\x1f\x16\x6e\x6c\xac\x04\x25\xa7\xcf\x3a"
	"\xb6\xaf\x6b\x7f\xc3\x10\x3b\x88\x32\x02\xe9\x04\x65\x65"
	/* Gx */
	"\x1d\x1c\x64\xf0\x68\xcf\x45\xff\xa2\xa6\x3a\x81\xb7\xc1\x3f\x6b\x88"
	"\x47\xa3\xe7\x7e\xf1\x4f\xe3\xdb\x7f\xca\xfe\x0c\xbd\x10\xe8\xe8\x26"
	"\xe0\x34\x36\xd6\x46\xaa\xef\x87\xb2\xe2\x47\xd4\xaf\x1e"
	/* Gy */
	"\x8a\xbe\x1d\x75\x20\xf9\xc2\xa4\x5c\xb1\xeb\x8e\x95\xcf\xd5\x52\x62"
	"\xb7\x0b\x29\xfe\xec\x58\x64\xe1\x9c\x05\x4f\xf9\x91\x29\x28\x0e\x46"
	"\x46\x21\x77\x91\x81\x11\x42\x82\x03\x41\x26\x3c\x53\x15"
	/* a */
	"\x7b\xc3\x82\xc6\x3d\x8c\x15\x0c\x3c\x72\x08\x0a\xce\x05\xaf\xa0\xc2"
	"\xbe\xa2\x8e\x4f\xb2\x27\x87\x13\x91\x65\xef\xba\x91\xf9\x0f\x8a\xa5"
	"\x81\x4a\x50\x3a\xd4\xeb\x04\xa8\xc7\xdd\x22\xce\x28\x26"
	/* b */
	"\x04\xa8\xc7\xdd\x22\xce\x28\x26\x8b\x39\xb5\x54\x16\xf0\x44\x7c\x2f"
	"\xb7\x7d\xe1\x07\xdc\xd2\xa6\x2e\x88\x0e\xa5\x3e\xeb\x62\xd5\x7c\xb4"
	"\x39\x02\x95\xdb\xc9\x94\x3a\xb7\x86\x96\xfa\x50\x4c\x11";
const struct sx_pk_ecurve sx_curve_brainpoolP384r1 = {
	.curveflags = PK_OP_FLAGS_PRIME, .sz = 48, .params = params_brainpoolP384r1};

static const char params_brainpoolP512r1[] =
	/* q */
	"\xaa\xdd\x9d\xb8\xdb\xe9\xc4\x8b\x3f\xd4\xe6\xae\x33\xc9\xfc\x07\xcb"
	"\x30\x8d\xb3\xb3\xc9\xd2\x0e\xd6\x63\x9c\xca\x70\x33\x08\x71\x7d\x4d"
	"\x9b\x00\x9b\xc6\x68\x42\xae\xcd\xa1\x2a\xe6\xa3\x80\xe6\x28\x81\xff"
	"\x2f\x2d\x82\xc6\x85\x28\xaa\x60\x56\x58\x3a\x48\xf3"
	/* n */
	"\xaa\xdd\x9d\xb8\xdb\xe9\xc4\x8b\x3f\xd4\xe6\xae\x33\xc9\xfc\x07\xcb"
	"\x30\x8d\xb3\xb3\xc9\xd2\x0e\xd6\x63\x9c\xca\x70\x33\x08\x70\x55\x3e"
	"\x5c\x41\x4c\xa9\x26\x19\x41\x86\x61\x19\x7f\xac\x10\x47\x1d\xb1\xd3"
	"\x81\x08\x5d\xda\xdd\xb5\x87\x96\x82\x9c\xa9\x00\x69"
	/* Gx */
	"\x81\xae\xe4\xbd\xd8\x2e\xd9\x64\x5a\x21\x32\x2e\x9c\x4c\x6a\x93\x85"
	"\xed\x9f\x70\xb5\xd9\x16\xc1\xb4\x3b\x62\xee\xf4\xd0\x09\x8e\xff\x3b"
	"\x1f\x78\xe2\xd0\xd4\x8d\x50\xd1\x68\x7b\x93\xb9\x7d\x5f\x7c\x6d\x50"
	"\x47\x40\x6a\x5e\x68\x8b\x35\x22\x09\xbc\xb9\xf8\x22"
	/* Gy */
	"\x7d\xde\x38\x5d\x56\x63\x32\xec\xc0\xea\xbf\xa9\xcf\x78\x22\xfd\xf2"
	"\x09\xf7\x00\x24\xa5\x7b\x1a\xa0\x00\xc5\x5b\x88\x1f\x81\x11\xb2\xdc"
	"\xde\x49\x4a\x5f\x48\x5e\x5b\xca\x4b\xd8\x8a\x27\x63\xae\xd1\xca\x2b"
	"\x2f\xa8\xf0\x54\x06\x78\xcd\x1e\x0f\x3a\xd8\x08\x92"
	/* a */
	"\x78\x30\xa3\x31\x8b\x60\x3b\x89\xe2\x32\x71\x45\xac\x23\x4c\xc5\x94"
	"\xcb\xdd\x8d\x3d\xf9\x16\x10\xa8\x34\x41\xca\xea\x98\x63\xbc\x2d\xed"
	"\x5d\x5a\xa8\x25\x3a\xa1\x0a\x2e\xf1\xc9\x8b\x9a\xc8\xb5\x7f\x11\x17"
	"\xa7\x2b\xf2\xc7\xb9\xe7\xc1\xac\x4d\x77\xfc\x94\xca"
	/* b */
	"\x3d\xf9\x16\x10\xa8\x34\x41\xca\xea\x98\x63\xbc\x2d\xed\x5d\x5a\xa8"
	"\x25\x3a\xa1\x0a\x2e\xf1\xc9\x8b\x9a\xc8\xb5\x7f\x11\x17\xa7\x2b\xf2"
	"\xc7\xb9\xe7\xc1\xac\x4d\x77\xfc\x94\xca\xdc\x08\x3e\x67\x98\x40\x50"
	"\xb7\x5e\xba\xe5\xdd\x28\x09\xbd\x63\x80\x16\xf7\x23";
const struct sx_pk_ecurve sx_curve_brainpoolP512r1 = {
	.curveflags = PK_OP_FLAGS_PRIME, .sz = 64, .params = params_brainpoolP512r1};

static const char params_secp192k1[] =
	/* q */
	"\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff"
	"\xff\xff\xfe\xff\xff\xee\x37"
	/* n */
	"\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xfe&\xf2\xfc\x17\x0fiFjt\xde\xfd\x8d"
	/* Gx */
	"\xdb\x4f\xf1\x0e\xc0\x57\xe9\xae\x26\xb0\x7d\x02\x80\xb7\xf4\x34\x1d"
	"\xa5\xd1\xb1\xea\xe0\x6c\x7d"
	/* gy */
	"\x9b\x2f\x2f\x6d\x9c\x56\x28\xa7\x84\x41\x63\xd0\x15\xbe\x86\x34\x40"
	"\x82\xaa\x88\xd9\x5e\x2f\x9d"
	/* a */
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00"
	/* b */
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x03";
const struct sx_pk_ecurve sx_curve_secp192k1 = {
	.curveflags = PK_OP_FLAGS_PRIME, .sz = 24, .params = params_secp192k1};

static const char params_secp256k1[] =
	/* q */
	"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"
	"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFE\xFF\xFF\xFC\x2F"
	/* n */
	"\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xfe"
	"\xba\xae\xdc\xe6\xaf\x48\xa0\x3b\xbf\xd2\x5e\x8c\xd0\x36\x41\x41"
	/* Gx */
	"\x79\xbe\x66\x7e\xf9\xdc\xbb\xac\x55\xa0\x62\x95\xce\x87\x0b\x07"
	"\x02\x9b\xfc\xdb\x2d\xce\x28\xd9\x59\xf2\x81\x5b\x16\xf8\x17\x98"
	/* gy */
	"\x48\x3a\xda\x77\x26\xa3\xc4\x65\x5d\xa4\xfb\xfc\x0e\x11\x08\xa8"
	"\xfd\x17\xb4\x48\xa6\x85\x54\x19\x9c\x47\xd0\x8f\xfb\x10\xd4\xb8"
	/* a */
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	/* b */
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x07";

const struct sx_pk_ecurve sx_curve_secp256k1 = {
	.curveflags = PK_OP_FLAGS_PRIME, .sz = 32, .params = params_secp256k1};

static const unsigned char param_fp256[] = {
	/* p */
	0x85, 0x42, 0xD6, 0x9E, 0x4C, 0x04, 0x4F, 0x18, 0xE8, 0xB9, 0x24, 0x35, 0xBF, 0x6F, 0xF7,
	0xDE, 0x45, 0x72, 0x83, 0x91, 0x5C, 0x45, 0x51, 0x7D, 0x72, 0x2E, 0xDB, 0x8B, 0x08, 0xF1,
	0xDF, 0xC3,
	/* n */
	0x85, 0x42, 0xD6, 0x9E, 0x4C, 0x04, 0x4F, 0x18, 0xE8, 0xB9, 0x24, 0x35, 0xBF, 0x6F, 0xF7,
	0xDD, 0x29, 0x77, 0x20, 0x63, 0x04, 0x85, 0x62, 0x8D, 0x5A, 0xE7, 0x4E, 0xE7, 0xC3, 0x2E,
	0x79, 0xB7,
	/* gx */
	0x42, 0x1D, 0xEB, 0xD6, 0x1B, 0x62, 0xEA, 0xB6, 0x74, 0x64, 0x34, 0xEB, 0xC3, 0xCC, 0x31,
	0x5E, 0x32, 0x22, 0x0B, 0x3B, 0xAD, 0xD5, 0x0B, 0xDC, 0x4C, 0x4E, 0x6C, 0x14, 0x7F, 0xED,
	0xD4, 0x3D,
	/* gy */
	0x06, 0x80, 0x51, 0x2B, 0xCB, 0xB4, 0x2C, 0x07, 0xD4, 0x73, 0x49, 0xD2, 0x15, 0x3B, 0x70,
	0xC4, 0xE5, 0xD7, 0xFD, 0xFC, 0xBF, 0xA3, 0x6E, 0xA1, 0xA8, 0x58, 0x41, 0xB9, 0xE4, 0x6E,
	0x09, 0xA2,
	/* a */
	0x78, 0x79, 0x68, 0xB4, 0xFA, 0x32, 0xC3, 0xFD, 0x24, 0x17, 0x84, 0x2E, 0x73, 0xBB, 0xFE,
	0xFF, 0x2F, 0x3C, 0x84, 0x8B, 0x68, 0x31, 0xD7, 0xE0, 0xEC, 0x65, 0x22, 0x8B, 0x39, 0x37,
	0xE4, 0x98,
	/* b */
	0x63, 0xE4, 0xC6, 0xD3, 0xB2, 0x3B, 0x0C, 0x84, 0x9C, 0xF8, 0x42, 0x41, 0x48, 0x4B, 0xFE,
	0x48, 0xF6, 0x1D, 0x59, 0xA5, 0xB1, 0x6B, 0xA0, 0x6E, 0x6E, 0x12, 0xD1, 0xDA, 0x27, 0xC5,
	0x24, 0x9A};

const struct sx_pk_ecurve curve_fp256 = {
	.curveflags = PK_OP_FLAGS_PRIME, .sz = 32, .params = (char *)param_fp256};

int sx_pk_count_curve_params(const struct sx_pk_ecurve *curve)
{
	if (curve->curveflags & PK_OP_FLAGS_SELCUR_MASK) {
		/* Predefined curves have curve parameters hardcoded in hardware
		 */
		return 0;
	}
	if (curve->params == NULL) {
		return 0;
	}
	if (curve->params == params_x448) {
		return 2;
	}
	if (curve->params == (char *)params_ed448) {
		return 5;
	}
	return 6;
}
