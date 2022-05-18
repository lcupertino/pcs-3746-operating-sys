#!/bin/zsh
DKNAME=$(docker ps --format "{{.Names}}")
docker kill "${DKNAME}"
