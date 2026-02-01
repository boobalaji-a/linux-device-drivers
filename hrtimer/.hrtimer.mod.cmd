savedcmd_hrtimer.mod := printf '%s\n'   hrtimer.o | awk '!x[$$0]++ { print("./"$$0) }' > hrtimer.mod
