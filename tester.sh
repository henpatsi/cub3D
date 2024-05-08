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

HEADER_COLOR=$LCYAN

# Output storage
LEAKS_LOG=leaks.log
TRASH_LOG=trash.log

CUB3D=./cub3D

INVALID_MAP_DIR=./maps/invalid/

printf ${HEADER_COLOR}"\n\n----- INVALID -----\n\n"${NC}

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

$CUB3D file_that_does_not_exist.cub
EXIT_CODE=$( echo $? )
if [ ${EXIT_CODE} -eq 1 ]; then
	echo -e ${GREEN}"file_that_does_not_exist.cub: [OK]"${NC}
else
	echo -e ${RED}"file_that_does_not_exist.cub: [KO]"${NC}
fi
echo ""

mkdir dir.cub
$CUB3D dir.cub
EXIT_CODE=$( echo $? )
if [ ${EXIT_CODE} -eq 1 ]; then
	echo -e ${GREEN}"dir.cub: [OK]"${NC}
else
	echo -e ${RED}"dir.cub: [KO]"${NC}
fi
echo ""
rm -rf dir.cub

$CUB3D ./maps/map0.cub "123"
EXIT_CODE=$( echo $? )
if [ ${EXIT_CODE} -eq 1 ]; then
	echo -e ${GREEN}"extraarg: [OK]"${NC}
else
	echo -e ${RED}"extraarg: [KO]"${NC}
fi
echo ""

$CUB3D
EXIT_CODE=$( echo $? )
if [ ${EXIT_CODE} -eq 1 ]; then
	echo -e ${GREEN}"noargs: [OK]"${NC}
else
	echo -e ${RED}"noargs: [KO]"${NC}
fi
echo ""

$CUB3D ""
EXIT_CODE=$( echo $? )
if [ ${EXIT_CODE} -eq 1 ]; then
	echo -e ${GREEN}"emptyarg: [OK]"${NC}
else
	echo -e ${RED}"emptyarg: [KO]"${NC}
fi
echo ""

$CUB3D " "
EXIT_CODE=$( echo $? )
if [ ${EXIT_CODE} -eq 1 ]; then
	echo -e ${GREEN}"spacearg: [OK]"${NC}
else
	echo -e ${RED}"spacearg: [KO]"${NC}
fi
echo ""


printf ${HEADER_COLOR}"\n\n----- LEAKS -----\n\n"${NC}

EXPECTED_LINES=4
for file in $INVALID_MAP_DIR*; do
	leaks --atExit -q -- $CUB3D $file 1>$LEAKS_LOG 2>$TRASH_LOG
	LEAKS=$( grep "total leaked bytes" $LEAKS_LOG | awk '{print $3}' )
	if [ $LEAKS -eq 0 ]; then
		echo -e ${GREEN}"$( basename $file ): [OK]"${NC}
	else
		echo -e ${RED}"$( basename $file ): [KO]"${NC}
	fi
done

rm -rf $LEAKS_LOG
rm -rf $TRASH_LOG


printf ${HEADER_COLOR}"\n\n ----- \n\n"${NC}