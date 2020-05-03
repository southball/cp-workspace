# CP-Workspace

This is my workspace that I use for competitive programming.

## Setup

- Copy the `.vimrc` file to `~/.vimrc`.
- Install [CtrlP](https://github.com/kien/ctrlp.vim) according to the [Installation Guide](http://kien.github.io/ctrlp.vim/#installation).
  - if CtrlP is not needed, remove the part that contains CtrlP settings from `~/.vimrc`.
- Edit `./config.sh` if needed, to change the list of files generated.
- You may want to edit `./template.cpp` to change the template used for each file.
- Launch the workspace by executing `./workspace.sh`.
- At the first launch, you may want to run `C-F11` to initialize the workspace.

## Hotkeys (defined by workspace)

- `F5`: compiles the program, runs from input file and checks the output file with the answer file.
- `F6`: compiles the program, and run the program in interactive mode.
- `F7`: opens the input file, the output file, the answer file and the log file for the active `.cpp` file.
- `C-F7`: closes files opened by `F7` for the active `.cpp` file.
- `C-F10`: resets the file by replacing the content with content in `template.cpp`.
- `C-F11`: resets every file in the workspace, defined in `./config.sh`.
- `F12`: copies the file content to system clipboard **in WSL**. Change the `nnoremap` to use `xclip` if you are on Linux.

