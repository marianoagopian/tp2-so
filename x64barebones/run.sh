#!/bin/bash

# if you have windows or ubuntu use this
# qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 #-soundhw pcspk
# if you have macOs use this
qemu-system-x86_64 -hda Image/x64BareBonesImage.qcow2 -m 512 -audiodev coreaudio,id=audio0 -machine pcspk-audiodev=audio0 #if it doesnt work change sdl for coreaudio
