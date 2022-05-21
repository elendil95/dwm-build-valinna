# Install
0. Install the other suckless components (`dmenu`, `st`, `slstatus`)
1. Install needed dependencies: xinerama, x11-dev, xsetroot and xkbdlib
2. Copy all the scripts from "scripts" folder to ~/bin/
3. run `make` and `sudo make install`
4. Consider running `make setup` after the first install, this will create a default autostart file in the right place

## Bar
- install font-awesome to get icons in bar
- install xsetroot if not present
- modify *config.def.h* adding system specific info like what network interface you'd like to get data for, or the file to read CPU temperature from.
- Run `make` and ` sudo make install` and `make clean` to install.

**PS:** For more information on how to bind custom progrmans and commands, refer to my [original dwm build](https://github.com/elendil95/dwm-build)


## Patches Applied
- **dwm-fullgaps** adds gaps between windows and the bar
- **dwm-pertag** allows the user to have different layouts active on different tags/workspaces
- **dwm-autostart** Allows dwm to read the script ~/.dwm/autostart.sh at startup, to launch programs after dwm itself
- **dwm-systray** Adds a simple sistray at the right edge of the bar
- **dwm-attachaside** Open new windows in the (slave) stack instead of opening it as the master window.
- **dwm-rotatestack** allows dwm to move windows along the stack (top of the stack == master window) using Mod+Shift+j/k
- **dwm-statusallmons** Allows the status bar to bw shown on all monitors, thought the systray will only appear on the the focused monitor
- **dwm-showselmon** Visually shows what monitor is currently being focused, by reversing the colors of the status bar on the unfocused monitors.
- **dwm-tagothermonitor** Adds new keybinds to send/focus windows to a specific tag on other monitors
- **dwm-changekbdlayout** A custom patch that adds the ability to switch keyboard layouts with (Mod+Ctrl+Space), that uses X11's XKLib
