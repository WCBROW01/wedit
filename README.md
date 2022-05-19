# wedit

A text editor written in C. This is mainly for educational purposes, and is not meant to be a good text editor. Although, who knows its future fate?

It is not in a usable state yet, and barely renders text.

## Build Instructions

First, you must grab the build dependencies. You can run `make build-deps` to acquire these, or grab them manually.
The build dependencies are currently [enchanced-cstrings](https://github.com/WCBROW01/enhanced-cstrings) and [cvector](https://github.com/WCBROW01/cvector), which are both my own projects.

If you have problems building related to these, try reaquiring them. The `clean-deps` rule should remove them.

Afterwards, the build build process consists of just running `make`! You must have a compiler with GNU extensions to compile this project.
