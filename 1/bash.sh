#!/bin/bash
DKNAME=$(docker ps --format "{{.Names}}")
docker exec -ti "${DKNAME}" bash
