FROM ubuntu:18.04

RUN apt-get update && \
        apt-get -y upgrade && \
        apt-get install -y \
            xinetd \
            iproute2

RUN groupadd -r user && useradd -r -g user user

COPY --chown=root:user ./build/start.sh /home/user/start.sh
COPY --chown=root:root ./build/ctf.conf /etc/xinetd.d/ctf
COPY --chown=root:user ./build/flag /home/user/flag
COPY --chown=root:user ./problem/ShyEEICtan /home/user/ShyEEICtan
COPY --chown=root:user ./problem/libc.so.6 /home/user/libc.so.6

WORKDIR /home/user

RUN chmod 444 ./flag && \
    chmod 555 ./ShyEEICtan && \
    chmod 555 ./libc.so.6 &&\ 
    chmod 555 ./start.sh && \
    chmod 444 /etc/xinetd.d/ctf

USER user
EXPOSE 20000

CMD ["xinetd","-dontfork","-f","/etc/xinetd.d/ctf"]
