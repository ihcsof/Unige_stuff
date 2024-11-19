FROM alpine:latest

RUN apk update && apk add g++ make

COPY questions.cpp /app/
COPY dc.txt /app/
COPY ssdm.txt /app/
COPY itpm.txt /app/
COPY fstt.txt /app/
COPY MAS.txt /app/
COPY ADM.txt /app/
COPY DECS.txt /app/

WORKDIR /app

RUN g++ -o app questions.cpp

VOLUME /app/err

CMD ["./app"]
