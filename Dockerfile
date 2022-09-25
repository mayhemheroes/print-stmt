FROM debian:bookworm as builder

RUN apt update && \
    DEBIAN_FRONTEND=noninteractive apt install build-essential clang -y

ADD . /print-stmt
WORKDIR /print-stmt/fuzz

RUN make

FROM debian:bookworm
COPY --from=builder /print-stmt/fuzz/print-fuzzer /
