FROM ubuntu:22.04 AS builder
RUN apt-get update && apt-get install -y g++ make
WORKDIR /build
COPY . .
RUN make

FROM ubuntu:22.04
RUN apt-get update && apt-get install -y valgrind && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY --from=builder /build/myshell /app/myshell
ENTRYPOINT ["./myshell"]