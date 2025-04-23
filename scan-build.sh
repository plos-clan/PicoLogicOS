#!/usr/bin/sh

scan-build --use-cc=cc --use-c++=c++ -analyze-headers ./build.py
