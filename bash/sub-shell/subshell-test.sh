#!/bin/bash
# subshell-test.sh

# (
# Inside parentheses, and therefore a subshell . . .
while [ 1 ]   # Endless loop.
do
  sleep 1
  echo "Subshell running . . ."
done
# )

#  Script will run forever,
#+ or at least until terminated by a Ctl-C.

exit $?  # End of script (but will never get here).

