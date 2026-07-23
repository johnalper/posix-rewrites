# POSIX Rewrites

A bare-metal, dependency-free implementation of POSIX core utilities from scratch in C, focused on system calls and manual memory management.

---

## Utilities

### `ls` — List Directory Contents

A raw C re-implementation of `ls` built over low-level BSD/POSIX system routines (`opendir`, `readdir`, `lstat`).

#### Options
* **`-a`**: Unmasks dotfiles (entries starting with `.`).
* **`-l`**: Renders long-format file attributes:
  * File type flag (`d`, `l`, `c`, `b`, `p`, `s`, `-`) and permission bitmask (`rwxrwxrwx`).
  * Link count (`st_nlink`), owner (`getpwuid`), group (`getgrgid`), size (`st_size`), and modification time (`strftime`).

#### Implementation Details
* **Link Resolution**: Uses `lstat()` to inspect symlink metadata directly without traversing targets.
* **Bitwise Permission Parsing**: Manual string bitmask construction mapping `mode_t` flags (`S_IRUSR`, `S_ISDIR`, etc.).
* **Pathing**: Accepts optional positional path argument; defaults to `.` via `getopt`.

#### Technical Notes
* **Platform Target**: Written against Darwin/BSD interfaces (references `st_mtimespec`; replace with `st_mtim` for Linux kernel headers).
* **Buffer Allocation**: Fixed **1024-byte** stack buffer for fullpath string formatting.

---

## Building

```bash
gcc -O2 -Wall -Wextra -o ls ls.c
./ls -al /path/to/dir
