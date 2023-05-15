#!/bin/bash

pattern="$1"

for file in *
do
  if [[ -f "$file" && $(grep -q "$pattern" "$file" ; echo $?) -eq 0 ]]; then
    echo "$file: Pattern found"
  else
    echo "$file: Pattern not found"
  fi
done

