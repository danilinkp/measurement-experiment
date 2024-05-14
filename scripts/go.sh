#!/bin/bash

./clean.sh

./build_apps.sh
./update_data.sh 30

python3 make_preproc.py
./make_postproc.sh