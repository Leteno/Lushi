#!/bin/bash

sudo apt-get install libsfml-dev
if [ -n "${SFML_PATH}" ]; then \
    echo ""; \
    echo "Please download sfml lib, and setup: SFML_PATH"; \
    echo "  Such as ~/Software/SFML-2.5.1-linux-gcc-64-bit/SFML-2.5.1/lib/"; \
    echo "  Download Link: https://www.sfml-dev.org/download.php"; \
    echo ""; \
    exit 1; \
fi