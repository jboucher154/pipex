#!/bin/bash
# This script is used to check the diff between two files.
# It is used to check the diff between the sysout and outfile.
# If the diff is empty, then the test passed.
# If the diff is not empty, then the test failed.

RED='\033[0;31m'
GREEN='\033[0;32m'

printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
TESTNUM=$((TESTNUM+1))
printf "\n"
