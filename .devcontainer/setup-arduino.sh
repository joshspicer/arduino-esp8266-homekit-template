#!/bin/bash

set -x

# Install arduino CLI
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=/usr/local/bin sh

# Generate shell completions
arduino-cli completion bash > arduino-cli.sh
mv arduino-cli.sh /etc/bash_completion.d/

# Config directories
arduino-cli config init
mkdir /root/arduino-metadata
mkdir /root/arduino-metadata/data /root/arduino-metadata/downloads /root/arduino-metadata/user 
arduino-cli config set directories.data /root/arduino-metadata/data
arduino-cli config set directories.downloads /root/arduino-metadata/downloads
arduino-cli config set directories.user /root/arduino-metadata/user

## -- Add additional board settings and libaries

# ESP8266
arduino-cli config set board_manager.additional_urls http://Arduino.esp8266.com/stable/package_esp8266com_index.json

# Homekit Adapter Library
arduino-cli config set library.enable_unsafe_install true
curl -L https://api.github.com/repos/Mixiaoxiao/Arduino-HomeKit-ESP8266/zipball > homekit.zip
arduino-cli lib install --zip-path homekit.zip

# Dump the current config
arduino-cli config dump

# Update index
arduino-cli core update-index
arduino-cli core upgrade

echo 'Done!'