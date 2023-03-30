SHELL = /bin/sh

OBJS =  main.o factorial.o hello.o
CFLAG = -Wall -g
CC = g++
INCLUDES = -I./third-party/opentelemetry-cpp/sdk/include\
	   -I./third-party/opentelemetry-cpp/exporters/ostream/include\
	   -I./third-party/opentelemetry-cpp/api/include\
	   -I./third-party/opentelemetry-cpp/exporters/otlp/include
LIBS  = -l:libopentelemetry_exporter_otlp_http.so\
	-l:libopentelemetry_otlp_recordable.so\
	-l:libopentelemetry_trace.so
LIBDIRS = -L./third-party/opentelemetry-cpp/build/exporters/otlp\
	  -L./third-party/opentelemetry-cpp/build/sdk/src/trace

main: main.o
	${CC} main.o ${LIBDIRS} ${LIBS} -o main

main.o:
	${CC} main.cc ${INCLUDES} -c -o main.o
