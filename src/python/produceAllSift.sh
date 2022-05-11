#!/bin/bash


python3 sift.py data/*.JPG
python3 sift.py data/*/*.JPG
zip sift_data.zip data/* data/*/*

exit 0
