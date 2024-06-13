FROM mcr.microsoft.com/mssql/server:2022-latest

USER root
ENV ACCEPT_EULA=Y
ENV MSSQL_SA_PASSWORD=StrongPassword2022!
RUN apt-get update \
    && apt-get upgrade -y \
    && apt-get install -y git pkg-config ranger sudo unixodbc-dev vim wget \
        clang-format meson ninja-build \
        python3-dbg python3-ipdb python3-pip python3-venv

ARG USER=mssql
RUN sudo mkhomedir_helper $USER \
    && echo "$USER ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/$USER \
    && chmod 0440 /etc/sudoers.d/$USER

USER $USER
ENV HOME=/home/$USER
ARG DIR=npyodbc
WORKDIR $HOME/$DIR
COPY . $HOME/$DIR
RUN sudo chown -R $USER:$USER $HOME/$DIR
RUN python3 -m venv $HOME/venv
ENV PATH=$HOME/venv/bin:$PATH
RUN pip install --upgrade pip
    && pip install .[dev,test]
