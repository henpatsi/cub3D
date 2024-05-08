#!/bin/bash

make

# Colors
NC='\033[0m'
GREEN='\033[0;32m'
LGREEN='\033[1;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
LCYAN='\033[1;36m'
YELLOW='\033[0;33m'

CUB3D=./cub3D

INVALID_MAP_DIR=./maps/invalid/

for file in $INVALID_MAP_DIR*; do
	$CUB3D $file
	EXIT_CODE=$( echo $? )
	if [ ${EXIT_CODE} -eq 1 ]; then
		echo -e ${GREEN}"$( basename $file ): [OK]"${NC}
	else
		echo -e ${RED}"$( basename $file ): [KO]"${NC}
	fi
	echo ""
done