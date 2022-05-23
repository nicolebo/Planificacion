FROM ubuntu:18.04
RUN apt-get update && apt-get -y install \
    build-essential libpcre3 libpcre3-dev zlib1g zlib1g-dev libssl-dev wget libqt4-dev libqt4-qt3support flex bison vim
ADD Qplanif home/Qplanif/
RUN cd home/Qplanif/src && bison input.y
RUN cd home/Qplanif/ && make
RUN cd home/Qplanif/bin && qmake && make
RUN cp home/Qplanif/bin/bin home/qplanif
