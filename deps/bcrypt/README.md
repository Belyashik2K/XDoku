# bcrypt (vendored)

Source: https://github.com/trusch/libbcrypt (MIT License, see `LICENSE`).

Vendored here so XDoku doesn't depend on a system-installed `libbcrypt` package,
which isn't reliably available across Linux distros, macOS, and Windows.
The upstream `src/main.cpp` demo executable was removed; everything else is
unmodified. The `x86.S` assembly is only compiled in on 32-bit x86 targets
(`#ifdef __i386__`); on every other architecture (x86_64, ARM, ...) it's an
empty translation unit, so this builds fine on Apple Silicon and ARM Linux too.
