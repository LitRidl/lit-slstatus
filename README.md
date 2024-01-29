# lit-slstatus - an updated fork of slstatus (suckless status)
slstatus is a small tool for providing system status information to other
programs over the EWMH property of the root window (used by dwm(1)) or
standard input/output. It is designed to be as efficient as possible by
only issuing the minimum of system calls required.


## Features
- Battery percentage/state/time left
- Volume percentage and mute status that works with PulseAudio and PipeWire
- Cat (read file)
- CPU usage
- CPU frequency
- Custom shell commands
- Date and time
- Disk status (free storage, percentage, total storage and used storage)
- Available entropy
- Username/GID/UID
- Hostname
- IP address (IPv4 and IPv6)
- Kernel version
- Keyboard indicators
- Keymap/Variant, original and uppercased
- Load average
- Network speeds (RX and TX)
- Number of files in a directory (hint: Maildir)
- Memory status (free memory, percentage, total memory and used memory)
- Swap status (free swap, percentage, total swap and used swap)
- Temperature
- Uptime
- WiFi signal percentage and ESSID


## Installation
slstatus is installed into the `/usr/local` namespace by default. If required, edit `config.mk` to match your local setup. 
Next, customize `config.h` and run the following command to build and install slstatus (may require `sudo/doas`):
```
make clean install
```

## Running slstatus
Put `slstatus &` in your `.xinitrc`, preferably before starting DWM.


## Configuration
slstatus can be customized by editing `config.h` and (re)compiling the source code. This keeps it fast, secure and simple. 

`config.h` serves as an example configuration. It reflects how I configured it on one of my laptops, with a bias toward battery efficiency. The update interval is relatively large. In fact, even an update interval of 100-200 ms is perfectly suitable for most systems unless you spawn long-running or CPU/IO-intensive custom scripts.

`config.def.h` is a template for `config.h` provided by the original slstatus, preserving their original values. If you're migrating from the original slstatus, you might find it convenient to use as a reference or template. Simply override `config.h` by running `cp config.def.h config.h` and make your desired edits to `config.h`.
