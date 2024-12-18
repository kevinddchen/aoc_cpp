#!/bin/bash
set -euo pipefail

show_help () {
    echo
    echo "To run a day: ./$(basename $0) 24day1"
    echo
}

if [[ $# -ne 1 ]]; then
    show_help
    exit 1
fi

DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

make bin/$1
./bin/$1
