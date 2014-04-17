#!/bin/sh
echo "Compiling program with the command: make clean install"
make clean install
echo "\nCommence automated option testing for myps"
echo "\nExecuting myps"
./myps
echo "\nExecuting myps -p"
./myps -p
echo "\nExecuting myps -p1180"
./myps -p1180
echo "\nExecuting myps -p1180 -cvUSs"
./myps -p1180 -cvUSs
echo "\nExecuting myps -SU"
./myps -SU
echo "\nExecuting myps -s -S -U -vc"
./myps -s -S -U -vc

echo "\nError Handling.\nIf space between p and pid, will state 1180 is invalid and ignore."
echo "Second, invalid options. Will state error and quit."
echo "Third, specifying a pid that does not exist. Will state that the PID doesn't exist."
echo "\nExecuting myps -p 1180"
./myps -p 1180
echo "\nExecuting myps -Lk"
./myps -Lk
echo "\nExecuting myps -p1121 -SU"
./myps -p1121 -SU
