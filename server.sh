#!/bin/bash

carpeta=$1
carpetaPrincital=/home/user/ds
hash=1

dowload() {
  echo "server montado"
  cp -r "/home/user/SharedFiles/$carpeta" $carpetaPrincital/
  cd $carpetaPrincital/$carpeta
  make clean
  make
  python -m SimpleHTTPServer 8000 >/dev/null 2>&1
}

dowload &
PID=$!
trap 'echo "Matando servidor $PID"; kill $PID 2>/dev/null' EXIT

while true; do

  newHash=$(find "$carpetaPrincital/$carpeta" -type f -print0 | sort -z | xargs -0 shasum -a 256 | shasum -a 256)
  if [[ $hash != $newHash ]]; then

    hash=$newHash
    rm -rf "$carpetaPrincital/$carpeta"

    actualPWD=$(pwd)

    cp -r "/home/user/SharedFiles/$carpeta" $carpetaPrincital
    cd "$carpetaPrincital/$carpeta"
    echo "------------------------------"
    temp=$(pwd)
    echo $temp
    make clean
    make

    cd $actualPWD

  fi
  sleep 5
done
