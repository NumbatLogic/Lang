#!/bin/bash

rm -rf Backup
rm -rf Project/ProjectGen

mkdir Backup
cp -r Project Backup
cp -r Source Backup
cp -r Transpiled Backup
cp -r Shared Backup

#sed -i 's/include\_once dirname(\_\_FILE\_\_) \. \"\/..\/..\/ProjectGen\/ProjectGen\.php\"\;/include\_once dirname(\_\_FILE\_\_) \. \"\/..\/..\/..\/ProjectGen\/ProjectGen\.php\"\;/g' Backup/Project/CPP.php
