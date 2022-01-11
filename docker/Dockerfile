# Pull base image
FROM ubuntu:22.04
MAINTAINER Nguyen Ba Ngoc <ngocnb@soict.hust.edu.vn>

# Install packages
RUN apt-get update && \
    apt-get -y install gcc g++ gdb cmake ninja-build valgrind vim time && \
    rm -rf /var/lib/apt/lists/*

# Setup user and work place
RUN useradd -ms /bin/bash  bangoc