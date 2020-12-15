#!/bin/sh

# Mostly copied from internet tutorials

EASYRSA=/usr/share/easy-rsa/easyrsa

# This basic example puts the "root" and "sub" PKI dirs on the same system.

# Build root CA:
EASYRSA_PKI=root ${EASYRSA} init-pki || exit 1
EASYRSA_PKI=root ${EASYRSA} build-ca nopass || exit 1

# Build sub-CA (intermediate CA) request:
EASYRSA_PKI=sub ${EASYRSA} init-pki || exit 1
EASYRSA_PKI=sub ${EASYRSA} build-ca nopass subca || exit 1

# Import the sub-CA request under the short-name "sub" on the root PKI:
EASYRSA_PKI=root ${EASYRSA} import-req sub/reqs/ca.req sub || exit 1
# Then sign it as a CA:
EASYRSA_PKI=root ${EASYRSA} sign-req ca sub || exit 1
# Transport sub-CA cert to sub PKI:
cp root/issued/sub.crt sub/ca.crt

# Generate and sign some requests on the sub-CA.
EASYRSA_PKI=sub ${EASYRSA} gen-req server nopass || exit 1
EASYRSA_PKI=sub ${EASYRSA} gen-req client nopass || exit 1
EASYRSA_PKI=sub ${EASYRSA} sign-req server server || exit 1
EASYRSA_PKI=sub ${EASYRSA} sign-req client client || exit 1

# Finally, create "bundle" files for use at each entity
cat sub/ca.crt sub/issued/server.crt > server-bundle.crt
cat sub/ca.crt sub/issued/client.crt > client-bundle.crt
