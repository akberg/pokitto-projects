FROM ubuntu:18.04

RUN apt update && \
		apt install -y -qq --no-install-recommends \
		git \
		vim \
		build-essential \
        cmake \
		libsdl2-dev \
		libsdl2-net-dev \
		libsdl2-image-dev \
		wget && \
		rm -rf /var/lib/apt/lists/*

RUN groupadd -g 1000 pokitto
RUN useradd -d /home/pokitto -s /bin/bash -m pokitto -u 1000 -g 1000
USER pokitto
ENV HOME /home/pokitto


RUN cd /home/pokitto && \
		git config --global http.sslVerify false && \
		git clone https://github.com/felipemanga/PokittoEmu.git && \
		cd PokittoEmu && \
		make -j ${nproc} && \
		ls BUILD/PokittoEmu

RUN cd /home/pokitto && \
		wget --no-check-certificate -nv https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2 && \
		tar -xjf gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2

RUN cd /home/pokitto && \
		git clone https://github.com/pokitto/PokittoLib.git && \
		cd PokittoLib && \
		git reset --hard 4db8133bda37c3f086d3a9bde4f37e1916cb09e5

RUN cd /home/pokitto && \
		git clone https://github.com/renato-grottesi/pokitto.git && \
		export PATH=/home/pokitto/gcc-arm-none-eabi-9-2019-q4-major/bin/:$PATH && \
		arm-none-eabi-gcc --version && \
		cd pokitto/Platformer/ && \
		rm -fr BUILD && \
		make clean && \
		make POKITTO_LIB_PATH="/home/pokitto/PokittoLib/Pokitto" -j ${nproc} -k

RUN git clone --recursive https://github.com/google/bloaty.git && \
    cd bloaty && \
    cmake . && \
    make -j6 && \
    mv bloaty /usr/bin/bloaty
