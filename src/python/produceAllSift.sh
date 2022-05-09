#!/bin/bash


python3 sift.py data/*
python3 sift.py data/*/*
zip sift_data.zip data/* data/*/*

exit 0
