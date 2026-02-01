savedcmd_gpio.mod := printf '%s\n'   gpio.o | awk '!x[$$0]++ { print("./"$$0) }' > gpio.mod
