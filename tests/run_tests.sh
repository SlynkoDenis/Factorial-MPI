#!/bin/bash

BUILD_DIR=$1
if [ -d ${BUILD_DIR} ]; then
    echo "Build directory's path was not provided, taking current directory"
    BUILD_DIR=.
fi

for NP in 1 2 4; do
    echo "=== Running with ${NP} processes ==="

    for NUMBER in 1 2 5 13 56 100; do
        echo "Checking ${NUMBER}!"

        mpirun -np ${NP} ${BUILD_DIR}/bin/tests ${NUMBER}
        STATUS=$?
        if [ "${STATUS}" != "0" ]; then
            echo "FAILED ${NUMBER}! on ${NP} processes (exit code ${STATUS})"
        fi
    done
done
