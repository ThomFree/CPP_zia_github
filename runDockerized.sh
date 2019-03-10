#!/bin/bash

# Exit when any command fails
set -e

echo -e "===== \033[35;1mBuilding\033[0m Docker images, \033[33;1mplease wait\033[0m... =====\n\n"

docker build -t "zia-image" .

echo -e "\n\n===== Zia is \033[32;1mready\033[0m! \033[34;1mPress any button\033[0m to launch. =====\n"
read -n1

docker run --network host zia-image
