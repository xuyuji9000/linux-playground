#!/bin/sh

POSITIONAL=()

function usage {
  echo "Help information:
--arg1 This is first argument
--arg2 This is second argument
  "
}

while [[ $# -gt 0 ]]
do 
key="$1"

case $key in
  --arg1)
  ARG1="$2"
  shift
  shift 
  ;;
  --arg2)
  ARG1="$2"
  shift
  shift 
  ;;
  -h)
  usage
  exit 0
  ;;
  *)
  echo "Unknow parameter."
  usage
  exit 1
  ;;
esac
done

if test -z "${ARG1}"
then 
  echo "\$ARG1 is empty"
  usage
  exit 1
fi
