FROM gcc:12

RUN apt-get update && \
    apt-get install -y cmake libpqxx-dev wget && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN wget https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h -O /usr/local/include/httplib.h

RUN mkdir -p build && cd build && cmake .. && make

CMD ["./build/time_app"]