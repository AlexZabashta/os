#!/bin/bash
find ../../../ -type f -mtime -3 | ./filter cat
