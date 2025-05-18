#!/bin/bash

if [ ! -f $CERTIFICATE_OUT ]; then
    openssl req \
    -newkey rsa:2048 \
    -nodes \
    -keyout $CERTIFICATE_KEYOUT \
    -x509 \
    -days 365 \
    -out $CERTIFICATE_OUT \
    -subj "/C=TR/ST=KOCAELI/L=GEBZE/O=42Kocaeli/CN=$DOMAIN_NAME";
fi

exec "$@"