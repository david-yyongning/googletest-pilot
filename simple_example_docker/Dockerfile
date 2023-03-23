# Get base image to build in
FROM gcc:10-buster as builder
LABEL Description="Build environment"

# Install dependencies
RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    cmake \
    gdb \
    wget \
    software-properties-common

# Copy source code from the docker context
RUN mkdir /app
WORKDIR /app
COPY ./src src
COPY ./tst tst
COPY ./CMakeLists.txt .

RUN mkdir lib
WORKDIR /app/lib
RUN git clone https://github.com/google/googletest/

RUN mkdir /app/build

# Build your source code
WORKDIR /app/build
RUN cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" 
RUN make all

# Use a runtime optimised base image
FROM debian:bullseye-slim

# Install dependencies
# iproute2: ip link for vcan setup
RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    gdb \
    wget \
    software-properties-common \
    gnupg2 \
    iproute2 \
    can-utils \
    procps

# Copy your build artifacts from the builder container to the runtime one
RUN mkdir /app
WORKDIR /app
COPY --from=builder /app/build ./

# Start your built executable
CMD [ "./src/ExampleProject_run" ]
