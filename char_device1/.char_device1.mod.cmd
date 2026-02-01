savedcmd_char_device1.mod := printf '%s\n'   char_device1.o | awk '!x[$$0]++ { print("./"$$0) }' > char_device1.mod
