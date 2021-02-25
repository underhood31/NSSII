#!/bin/sh

echo ":::START:::"
#read -n 1 -r -s -p $'Make sure that kernel module is NOT inserted. Press enter to continue...'
#echo ""
#echo "Running nmap commands to show sample output without loading the kernel module"
#echo ""
#echo "::nmap Null scan::"
#sudo nmap -sN 10.0.0.2
#echo ""
#echo "--------------------------------------------------"
#echo ""
#echo "::nmap Fin scan::"
#sudo nmap -sF 10.0.0.2
#echo ""
#echo "--------------------------------------------------"
#echo ""
#echo "::nmap Xmas scan::"
#sudo nmap -sX 10.0.0.2
#echo ""
#echo "--------------------------------------------------"
#echo ""
read -n 1 -r -s -p $'Load the kernel module in VM2. Press enter to continue...'
echo ""
echo "::nmap Null scan::"
sudo nmap -sN 10.0.0.2
echo ""
read -n 1 -r -s -p $'Check the syslog on VM2. Press enter to continue...'
echo ""
echo "--------------------------------------------------"
echo ""
echo "::nmap Fin scan::"
sudo nmap -sF 10.0.0.2
echo ""
read -n 1 -r -s -p $'Check the syslog on VM2. Press enter to continue...'
echo ""
echo "--------------------------------------------------"
echo ""
echo "::nmap Xmas scan::"
sudo nmap -sX 10.0.0.2
echo ""
read -n 1 -r -s -p $'Check the syslog on VM2. Press enter to continue...'
echo ""
echo "--------------------------------------------------"
echo ""

