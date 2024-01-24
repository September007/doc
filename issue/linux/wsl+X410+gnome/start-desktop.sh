#!/bin/bash

if [ -z "$DISPLAY" ]; then
    echo "Error: DISPLAY environment variable is not set."
    exit
fi

gnome-shell
