#!/bin/bash
docker pull nlebovits/entrega-ruben:latest
xhost +
docker run --rm -ti --net=host --ipc=host -e DISPLAY=${DISPLAY} -v /tmp/.X11-unix:/tmp/.X11-unix --env="QT_X11_NO_MITSHM=1" -w /home nlebovits/entrega-ruben:latest sh -c ./qplanif
