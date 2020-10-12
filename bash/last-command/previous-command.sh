#!/bin/sh

# This script echo the previous command after command execution

trap 'previous_command=$this_command; this_command=$BASH_COMMAND' DEBUG
ls
echo "last command is $previous_command"
