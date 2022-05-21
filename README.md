A fork of my own dwm, with only functional patches applied: the goal is to have the least amoutn of dependencies, and for setup to be as quick as possile on brand new machines
# Install

## Base DWM

- Install [st](https://github.com/elendil95/st-build) and [dmenu](kek)
- Run `make` and ` sudo make install` and `make clean` to install DMW
- Copy *autostart.sh* to new direcoty ~/.dwm, and add all the programs you want to run at startup there (remember to make it executable first)
- If using a display manager like LightDM, copy dwm.desktop to /usr/share/xsessions/

## Bar

- install font-awesome to get icons in bar
- install xsetroot if not present
- modify *config.def.h* adding system specific info like what network interface you'd like to get data for, or the file to read CPU temperature from.
- Run `make` and ` sudo make install` and `make clean` to install.

**PS:** For more information on how to bind custom progrmans and commands, refer to my [original dwm build](https://github.com/elendil95/dwm-build)


#Amogus
dwm-fullgaps adds gaps between windows and the bar
dwm-pertag allows the user to have different layouts active on different tags/workspaces
dwm-autostart Allows dwm to read the script ~/.dwm/autostart.sh at startup, to launch programs after dwm itself
dwm-systray Adds a simple sistray at the right edge of the bar
dwm-attachaside Open new windows in the (slave) stack instead of opening it as the master window.
dwm-rotatestack allows dwm to move windows along the stack (top of the stack == master window) using Mod+Shift+j/k
dwm-statusallmons Allows the status bar to bw shown on all monitors, thought the systray will only appear on the the focused monitor
dwm-showselmon Visually shows what monitor is currently being focused, by reversing the colors of the status bar on the unfocused monitors.
dwm-tagothermonitor Adds new keybinds to send/focus windows to a specific tag on other monitors
dwm-changekbdlayout A custom patch that adds the ability to switch keyboard layouts with (Mod+Ctrl+Space), that uses X11's XKLib
