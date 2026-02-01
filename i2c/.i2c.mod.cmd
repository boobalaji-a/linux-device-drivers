savedcmd_/home/pi/device_drivers/i2c/i2c.mod := printf '%s\n'   i2c.o | awk '!x[$$0]++ { print("/home/pi/device_drivers/i2c/"$$0) }' > /home/pi/device_drivers/i2c/i2c.mod
