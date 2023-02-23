#!/bin/bash

NOCOLOR='\033[0m'
YELLOW='\033[1;33m'
PURPLE='\033[0;35m'
GREEN='\033[0;32m'
BLUE='\033[0;36m'
PINK='\033[0;34m'
RED='\033[0;31m'

TESTNUM=1;

# add tests for files without access
printf "${YELLOW}BASIC TESTS\n${NOCOLOR}"

printf "${PINK}Test %d :no commands "" | "" \n${NOCOLOR}" "$TESTNUM"
./pipex infile "" "" outfile
< infile "" | "" > sysout
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
TESTNUM=$((TESTNUM+1))

printf "${PINK}Test %d :no files or commands "" "" | "" "" \n${NOCOLOR}" "$TESTNUM"
./pipex "" "" "" ""
< "" "" | "" >""
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
TESTNUM=$((TESTNUM+1))

printf "${PINK}Test %d : To few args \n${NOCOLOR}" "$TESTNUM"
./pipex infile "grep a"  outfile
# printf "should be no output"
# printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${PINK}Test %d : To many args \n${NOCOLOR}" "$TESTNUM"
./pipex infile "grep a" "head -1" outfile run
# printf "should be no output"
# printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${PINK}Test %d : outfile without permissions \n${NOCOLOR}" "$TESTNUM"
./pipex infile "ls -l" "wc -l" nopermit_out
< infile ls -l | wc -l > nopermit_out
printf "diff sysout-outfile: "
# DIFF=$(diff sysout outfile)
# if [ -z "$DIFF"]; 
# then
# 	printf "${GREEN}NO${NOCOLOR}"
# else
# 	printf "${RED}YES${NOCOLOR}"
# fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${PINK}Test %d : infile without permissions \n${NOCOLOR}" "$TESTNUM"
./pipex notpermit "ls -l" "wc -l" outfile
< notpermit ls -l | wc -l > sysout
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"

# TESTNUM=1
printf "\n${YELLOW}GOOD INPUT TESTS\n${NOCOLOR}"

printf "${PURPLE}Test %d : grep a | wc -l \n${NOCOLOR}" "$TESTNUM"
./pipex infile "grep a" "wc -l" outfile
< infile grep a | wc -l > sysout
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

printf "${PURPLE}Test %i: ls -l | wc -l \n${NOCOLOR}" "$TESTNUM"
./pipex infile "ls -l" "wc -l" outfile
< infile ls -l | wc -l > sysout
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

printf "${PURPLE}Test %i: /dev/urandom cat | head -1 \n${NOCOLOR}" "$TESTNUM"
./pipex /dev/urandom "cat" "head -1" outfile
< /dev/urandom cat | head -1 > sysout
printf "diff sysout-outfile: DIFF not measured ${GREEN}OKAY${NOCOLOR}"
TESTNUM=$((TESTNUM+1))
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${PURPLE}Test %i: ls -l | awk '{print($3)}' \n${NOCOLOR}" "$TESTNUM"
./pipex infile "ls -l" "awk '{print\$3}'" outfile
< infile ls -l | awk '{print$3}' > sysout
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
TESTNUM=$((TESTNUM+1))

printf "\n${YELLOW}BAD INFILE TESTS\n${NOCOLOR}"
# TESTNUM=1

printf "${GREEN}Test %d : grep a | wc -l \n${NOCOLOR}" "$TESTNUM"
./pipex infil "grep a" "wc -l" outfile
< infil grep a | wc -l > sysout
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${GREEN}Test %i: ls -l | wc -l \n${NOCOLOR}" "$TESTNUM"
./pipex infil "ls -l" "wc -l" outfile
< infil ls -l | wc -l > sysout
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${GREEN}Test %i: ls -l | awk 'print($3)' \n${NOCOLOR}" "$TESTNUM"
./pipex infil "ls -l" "awk '{print\$3}'" outfile
< infil ls -l | awk '{print$3}' > sysout
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

printf "\n${YELLOW}BAD OUTFILE TESTS\n${NOCOLOR}"
# TESTNUM=1

printf "${BLUE}Test %d : grep a | wc -l \n${NOCOLOR}" "$TESTNUM"
./pipex infile "grep a" "wc -l" ""
< infile grep a | wc -l > ""
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${BLUE}Test %i: ls -l | wc -l \n${NOCOLOR}" "$TESTNUM"
./pipex infile "ls -l" "wc -l" ""
< infile ls -l | wc -l > ""
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${BLUE}Test %i: ls -l | awk 'print($3)' \n${NOCOLOR}" "$TESTNUM"
./pipex infile "ls -l" "awk '{print\$3}'" ""
< infile ls -l | awk '{print$3}' > ""
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "\n${YELLOW}BAD IN AND OUT FILE TESTS\n${NOCOLOR}"
# TESTNUM=1

printf "${PINK}Test %d : grep a | wc -l \n${NOCOLOR}" "$TESTNUM"
./pipex infil "grep a" "wc -l" ""
< infil grep a | wc -l > ""
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${PINK}Test %i: ls -l | wc -l \n${NOCOLOR}" "$TESTNUM"
./pipex infil "ls -l" "wc -l" ""
< infil ls -l | wc -l > ""
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${PINK}Test %i: ls -l | awk 'print($3)' \n${NOCOLOR}" "$TESTNUM"
./pipex infil "ls -l" "awk '{print\$3}'" ""
< infil ls -l | awk '{print$3}' > ""
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "\n${YELLOW}BAD FIRST COMMAND\n${NOCOLOR}"
# TESTNUM=1

printf "${PURPLE}Test %d : grp a | wc -l \n${NOCOLOR}" "$TESTNUM"
./pipex infile "grp a" "wc -l" outfile
< infile grp a | wc -l > sysout
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${PURPLE}Test %i: lw -l | wc -l \n${NOCOLOR}" "$TESTNUM"
./pipex infile "lw -l" "wc -l" outfile
< infile lw -l | wc -l > sysout
printf "diff sysout-outfile: "
diff sysout outfile
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${PURPLE}Test %i: ll -l | awk '{print($3)}' \n${NOCOLOR}" "$TESTNUM"
./pipex infile "ll -l" "awk '{print\$3}'" outfile
< infile ll -l | awk '{print$3}' > sysout
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "\n${YELLOW}BAD SECOND COMMAND\n${NOCOLOR}"
# TESTNUM=1

printf "${GREEN}Test %d : grep a | ww -l \n${NOCOLOR}" "$TESTNUM"
./pipex infile "grep a" "ww -l" outfile
< infile grep a | ww -l > sysout
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${GREEN}Test %i: ls -l | wt -l \n${NOCOLOR}" "$TESTNUM"
./pipex infile "ls -l" "wt -l" outfile
< infile ls -l | wt -l > sysout
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${GREEN}Test %i: ls -l | aw '{print($3)}' \n${NOCOLOR}" "$TESTNUM"
./pipex infile "ls -l" "aw '{print\$3}'" outfile
< infile ls -l | aw '{print$3}' > sysout
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "\n${YELLOW}BOTH BAD COMMAND\n${NOCOLOR}"
# TESTNUM=1

printf "${BLUE}Test %d : grp a | ww -l \n${NOCOLOR}" "$TESTNUM"
./pipex infile "grp a" "ww -l" outfile
< infile grp a | ww -l > sysout
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${BLUE}Test %i: ll -l | wt -l \n${NOCOLOR}" "$TESTNUM"
./pipex infile "ll -l" "wt -l" outfile
< infile ll -l | wt -l > sysout
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))

printf "${BLUE}Test %i: lw -l | aw '{print($3)}' \n${NOCOLOR}" "$TESTNUM"
./pipex infile "lw -l" "aw '{print\$3}'" outfile
< infile lw -l | aw '{print$3}' > sysout
printf "diff sysout-outfile: "
DIFF=$(diff sysout outfile)
if [ -z "$DIFF"]; 
then
	printf "${GREEN}NO${NOCOLOR}"
else
	printf "${RED}YES${NOCOLOR}"
fi
printf "\n"
TESTNUM=$((TESTNUM+1))
