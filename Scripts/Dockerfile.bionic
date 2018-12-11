FROM ubuntu:18.04
MAINTAINER Chris Ohk <utilforever@gmail.com>

RUN apt-get update -yq && \
    apt-get install -yq build-essential cmake

ADD . /app

WORKDIR /app/build
RUN cmake .. && \
    make -j`nproc` && \
    make install
