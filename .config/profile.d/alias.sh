# alias file

# general
alias \
    c="clear" \
    v="nvim"
    cp="cp -iv" \
    mv="mv -iv" \
    rm="rm -vI" \
    bc="bc -ql" \

# list files
alias \
    l="exa -lg --group-directories-first" \
    la="exa -lga --group-directories-first" \
    las="exa -lga --group-directories-first -s $1" 

# doas shorthands
alias \
    poweroff="doas /sbin/poweroff" \
    savescreen="xscreensaver-command -activate && sleep 5 && doas sh -c 'sleep 3 && echo deep | tee /sys/power/mem_sleep && echo mem | tee /sys/power/state'" \
    reboot="doas /sbin/reboot"
