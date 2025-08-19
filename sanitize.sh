#!/bin/bash
# SPDX-License-Identifier: MPL-2.0

count=0

while read l; do
	count=$((count + 1))
done

if ! [ "$count" = 16 ]; then
	echo "Too few lines!"
	exit 1
fi
