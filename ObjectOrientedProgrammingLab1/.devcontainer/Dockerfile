# Используем базовый образ с GCC
FROM gcc:14.2.0


# Устанавливаем зависимости для Google Test и CMake
RUN apt-get update && apt-get install -y \
    cmake \
    fish \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*


# Компиляция Google Test (libgtest-dev поставляется только с исходным кодом)
RUN cd /usr/src/gtest && cmake . && make && mv lib/*.a /usr/lib


# Устанавливаем рабочую директорию по умолчанию
WORKDIR /workspaces/ObjectOrientedProgrammingLab1

# Открываем порт для отладки (необязательно)
# EXPOSE 8080
