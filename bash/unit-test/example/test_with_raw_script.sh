#!/bin/sh

shopt -s expand_aliases

# Before all
alias mail="echo 'mail' > mailsent;false"
echo 'Test results for diskusage.sh' > test_results

tcnt=0
# Before (arrange)
alias df="echo 'Filesystem Size Used Avail Use% Mounted on';echo '/dev/sda2 100G 89.0G 11.0G 89% /'"
echo 'no mail' > mailsent

# Run code under test (act)
. ./diskusage.sh

# Check result (assert)
((tcnt=tcnt+1))
if [[ $(< mailsent) == 'mail' ]]; then 
echo "$tcnt. FAIL: Expected no mail to be sent for disk usage under 90%" >> test_results
else 
  echo "$tcnt. PASS: No action taken for disk usage under 90%" >> test_results
fi 


# It sends an email notification when disk usage is at 90%

alias df="echo 'Filesystem Size Used Avail Use% Mounted on';echo '/dev/sda1 100G 90.0G 10.0G 90% /'"
echo 'no mail' > mailsent


. ./diskusage.sh

((tcnt=tcnt+1))
if [[ $(< mailsent) == 'mail' ]]; then
  echo "$tcnt. PASS: Notification was sent for disk usage of 90%" >> test_results
else 
  echo "$tcnt. FAIL: Disk usage was 90% but no notification was sent" >> test_results
fi 

# After all
unalias df
unalias mail

# Display test results 
cat test_results