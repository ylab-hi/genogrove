FROM gcc:12.4
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    ninja-build \
    gdb

# install htslib
RUN wget https://github.com/samtools/htslib/releases/download/1.21/htslib-1.21.tar.bz2
RUN tar -xvf htslib-1.21.tar.bz2 && cd htslib-1.21 && ./configure && make && make install
