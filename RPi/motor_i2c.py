from smbus import SMBus

addr = 0x8 # bus address
bus = SMBus(1) # indicates /dev/ic2-1

numb = 1

print ("Enter 1 for ON or 0 for OFF")
while numb == 1:

    ledstate = input(" Enter command ")
    print(ledstate)
    if ledstate == 'fwd':
        bus.write_byte(addr, 0x1) # switch it on
        print("Run motor forward")
    elif ledstate == 'rev':
        bus.write_byte(addr, 0x0) # switch it on
        print("Run motor backward")
    else:
        numb = 0
