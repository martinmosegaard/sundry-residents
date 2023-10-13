#!/usr/bin/env bash

# Check for git diffs in all subdirectories.

for dir in ./*/; do
  # Enable echo to see dirs processed
  #echo $dir

  if [ -d $dir/.git ]
  then
    echo --- $dir
  else
    echo --- $dir --- skipped: Not a git repo
    continue
  fi

  pushd . >/dev/null
  cd $dir
  if [[ ! -z $(git status --porcelain) ]];
  then
    echo Changes in $(pwd)
  fi

  git branch | grep '*' | egrep -q 'main|master' || echo Branch is not main or master in $(pwd)
  popd >/dev/null
done

