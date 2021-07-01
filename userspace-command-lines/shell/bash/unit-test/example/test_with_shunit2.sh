#!/bin/sh

shopt -s expand_aliases

test_itDoesNotSendNotification_whenUsageIsBelowThreshold() {
    alias df="echo 'Filesystem Size Used Avail Use% Mounted on';echo '/dev/sda2 100G 89.0G 11.0G 89% /'"
    echo 'no mail' > mailsent
    . ./diskusage.sh
    assertTrue "It should not send a notification when disk usage is under 90%" \
            '[[ $(< mailsent) != "mail" ]]'
} 

test_itSendsNotification_whenUsageIsAtOrAboveThreshold() {
    alias df="echo 'Filesystem Size Used Avail Use% Mounted on';echo '/dev/sda1 100G 90.0G 10.0G 90% /'"
    echo 'no mail' > mailsent
    . ./diskusage.sh
    assertTrue "It should send a notification when disk usage is at or above 90%" \
            '[[ $(< mailsent) == "mail" ]]'
} 

oneTimeSetUp() {
    alias mail="echo 'mail' > mailsent;false"
}

oneTimeTearDown() {
    unalias df
    unalias mail
}

. ./shunit2
