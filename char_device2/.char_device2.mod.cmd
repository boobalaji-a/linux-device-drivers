savedcmd_char_device2.mod := printf '%s\n'   char_device2.o | awk '!x[$$0]++ { print("./"$$0) }' > char_device2.mod
