# Используем базовый образ с поддержкой C++
FROM mcr.microsoft.com/devcontainers/cpp:0-ubuntu-20.04

# Устанавливаем зависимости для Google Test и CMake
RUN apt-get update && apt-get install -y \
    cmake \
    g++ \
    git \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Установка Google Test
RUN git clone https://github.com/google/googletest.git /usr/src/gtest && \
    cd /usr/src/gtest && \
    cmake . && \
    make && \
    cp ./lib/*.a /usr/lib && \
    cd .. && rm -rf googletest

# Устанавливаем рабочую директорию
WORKDIR /workspace

COPY . .

# Открываем порт для отладки (необязательно)
EXPOSE 8080
