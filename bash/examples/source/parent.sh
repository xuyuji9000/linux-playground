#!/bin/sh

echo "Parent PID:"

echo $$
echo ""

echo "Child PID with source:"

source ./child.sh

echo "Child PID with execution:"

./child.sh
