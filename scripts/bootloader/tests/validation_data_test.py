#
# Copyright (c) 2024 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause

import hashlib
from pathlib import Path

import ecdsa  # type: ignore[import-untyped]

import do_sign
from hash import generate_hash_digest
from keygen import Ed25519KeysGenerator, EllipticCurveKeysGenerator
from validation_data import Ed25519SignatureValidator, EcdsaSignatureValidator


def test_data_validation_for_ec(tmpdir):
    magic_value = '0x281ee6de,0x86518483,79362'
    offset = 0
    private_key_file = tmpdir / 'private.pem'
    public_key_file = tmpdir / 'public.pem'
    message_file = Path(__file__).parent / 'zephyr.hex'
    message_signature_file = tmpdir / 'zephyr.signature'
    output_hex_file = tmpdir / 'output.hex'
    hash_file = tmpdir / 'hash.256'

    keys_generator = EllipticCurveKeysGenerator()
    keys_generator.write_private_key_pem(private_key_file)
    keys_generator.write_public_key_pem(public_key_file)

    hash_file.open('wb').write(generate_hash_digest(str(message_file), 'sha256'))

    do_sign.sign_with_ecdsa(private_key_file, hash_file, message_signature_file)

    public_key = ecdsa.VerifyingKey.from_pem(public_key_file.read())
    EcdsaSignatureValidator(hashfunc=hashlib.sha256).append_validation_data(
        signature_file=message_signature_file,
        input_file=message_file,
        public_key=public_key,
        offset=offset,
        output_hex=output_hex_file.open('w'),
        output_bin=None,
        magic_value=magic_value
    )
    # TODO: check output_hex_file


def test_data_validation_for_ed25519(tmpdir):
    magic_value = '0x281ee6de,0x86518483,79362'
    offset = 0
    private_key_file = tmpdir / 'private.pem'
    message_file = Path(__file__).parent / 'zephyr.hex'
    hash_file = tmpdir / 'hash.sha512'
    message_signature_file = tmpdir / 'zephyr.signature'
    output_hex_file = tmpdir / 'output.hex'

    keys_generator = Ed25519KeysGenerator()
    keys_generator.write_private_key_pem(private_key_file)

    hash_file.open('wb').write(generate_hash_digest(str(message_file), 'sha512'))

    do_sign.sign_with_ed25519(private_key_file, hash_file, message_signature_file)

    Ed25519SignatureValidator(hashfunc=hashlib.sha512).append_validation_data(
        signature_file=message_signature_file,
        input_file=message_file,
        public_key=keys_generator.public_key,
        offset=offset,
        output_hex=output_hex_file.open('w'),
        output_bin=None,
        magic_value=magic_value
    )


def test_data_validation_for_signed_hex_file_with_ed25519(tmpdir):
    magic_value = '0x281ee6de,0x86518483,79362'
    offset = 0
    private_key_file = tmpdir / 'private.pem'
    message_file = Path(__file__).parent / 'zephyr.hex'
    message_signature_file = tmpdir / 'zephyr.signature'
    output_hex_file = tmpdir / 'output.hex'

    keys_generator = Ed25519KeysGenerator()
    keys_generator.write_private_key_pem(private_key_file)

    do_sign.sign_with_ed25519(private_key_file, message_file, message_signature_file)

    # verify signature
    Ed25519SignatureValidator().verify(
        public_key=keys_generator.public_key,
        message_bytes=do_sign.hex_to_binary(str(message_file)),
        signature_bytes=message_signature_file.open('rb').read()
    )

    # create validation data
    Ed25519SignatureValidator().append_validation_data(
        signature_file=message_signature_file,
        input_file=message_file,
        public_key=keys_generator.public_key,
        offset=offset,
        output_hex=output_hex_file.open('w'),
        output_bin=None,
        magic_value=magic_value
    )
