#!/bin/bash
# SPDX-License-Identifier: MPL-2.0

clear

IFS=''
while read -r l; do
	for ((i=0;i<8;i++)); do
#		echo "$i" "${#l}"
		if [ "$i" -ge "${#l}" ]; then
			break;
		fi

		x="${l:$i:1}"
		if [ "$x" = X ]; then
			echo -ne $'\x1b[7m  \x1b[0m'
		else
			echo -ne '  '
		fi
	done
	echo
done
