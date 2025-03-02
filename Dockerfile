FROM ubuntu
ENV DEBIAN_FRONTEND=noninteractive
RUN apt update -y && apt install -y build-essential cmake python3 git

# docker build . --platform linux/amd64 -t gdlibretro
# docker run -it --platform linux/amd64 -v `pwd`:/app -w /app gdlibretro ./build_gdlibretro.sh 