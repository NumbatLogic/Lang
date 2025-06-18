#!/bin/bash

rm -rf Backup
rm -rf Project/ProjectGen

mkdir Backup
cp -r Project Backup
cp -r Source Backup
cp -r Transpiled Backup
cp -r Shared Backup
cp LangShared.package-list Backup

sed -i 's/LangShared\//..\/LangShared\//g' Backup/Project/CLI/CS/Build.sh
sed -i 's/LangShared\//..\/LangShared\//g' Backup/Project/Test/CS/Build.sh