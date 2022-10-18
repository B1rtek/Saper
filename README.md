# Saper

Minesweeper that can be played in terminal. This code is very old, I wrote it in 2019 or something like that and never published it, the original version was made for Windows and it sucks because cmd refreshes slower than I can redraw the whole screen on a piece of paper. The Linux version was made very recently and suffers from some minor visual bugs, it's literally the windows version but with all calls to functions that apply color to the terminal output changed to the Linux ones. It works much faster because Linux is superior.

## How to play
By default, the key bindings are:
- wasd - move around
- m - sweep
- n - flag

The binds can be changed in the settings to arrow keys + s and d.
You can press u to give up.
The board should be centered in the console (assuming that it's 120 characters wide) and contains a title bar inspired by the look of the original Windows minesweeper for Windows 3.1

## Building
On Windows, you'll need MSVC compiler or an old weird version of MinGW distributed with Dev C++, on Linux you'll need either the curses or the ncurses library (if you're using ncurses change the include in saperLinux.cpp and linker argument in CMakeLists.txt)

```shell
git clone https://github.com/B1rtek/Saper
cd Saper
mkdir build && cd build
cmake ..
cmake --build .
```
