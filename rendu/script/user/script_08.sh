#!/bin/bash
#Trouve tous les fichiers avec l'extension ".log"
find /var/log -name '*.log' | tar cv --files-from=-
#ou Trouve tous les fichiers avec l'extension ".log" et en fait une archive en bzip
find /var/log -name '*.log' | tar cv --files-from=- | bzip2 > log.tar.bz2
