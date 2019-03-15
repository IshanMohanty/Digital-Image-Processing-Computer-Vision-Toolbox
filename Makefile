CXX= ${CROSS_COMPILE}g++

PROGRAM1= ./bin/colormanip
PROGRAM2= ./bin/cmyk
PROGRAM3= ./bin/bilinear
PROGRAM4= ./bin/TransferFunction
PROGRAM5= ./bin/OilPaint64
PROGRAM6= ./bin/OilPaint512
PROGRAM7= ./bin/FilmEffect
PROGRAM8= ./bin/Denoise
PROGRAM9= ./bin/CDF


CFLAGS=-g -DPRINT_OUTPUT

COMMON_OBJS = 	 
				
PROGRAM1_OBJS= ColorManipulation.o

PROGRAM2_OBJS= CMYK.o

PROGRAM3_OBJS= bilinear_transform.o

PROGRAM4_OBJS= TransferFunction.o

PROGRAM5_OBJS= OilPaint64.o

PROGRAM6_OBJS= OilPaint512.o

PROGRAM7_OBJS= filmeffect.o

PROGRAM8_OBJS= Denoising.o

PROGRAM9_OBJS= CDFbased.o


INCLUDE=  -I ./

LIB= 

LDFLAGS= -lm 

vpath %.cpp ./


all: ${PROGRAM1} ${PROGRAM2} ${PROGRAM3} ${PROGRAM4} ${PROGRAM5} ${PROGRAM6} ${PROGRAM7} ${PROGRAM8} ${PROGRAM9}
  

grayscale    :   		   ${PROGRAM1}
cmyk         :    		   ${PROGRAM2}
bilinear     :   		   ${PROGRAM3}
Transfer     :    		   ${PROGRAM4}
OilPaint_64  :   		   ${PROGRAM5}
OilPaint_512 :    		   ${PROGRAM6}
FilmEffect   :   		   ${PROGRAM7}
Denoising    :    		   ${PROGRAM8}
CDFBASED     :    		   ${PROGRAM9}

.cpp.o:
	${CXX} ${CFLAGS} ${INCLUDE} -c $< ${LIB} -o $@
	
${PROGRAM1}:${COMMON_OBJS} ${PROGRAM1_OBJS} 
	${CXX} ${COMMON_OBJS} ${PROGRAM1_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM2}:${COMMON_OBJS} ${PROGRAM2_OBJS}
	${CXX} ${COMMON_OBJS} ${PROGRAM2_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM3}:${COMMON_OBJS} ${PROGRAM3_OBJS} 
	${CXX} ${COMMON_OBJS} ${PROGRAM3_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM4}:${COMMON_OBJS} ${PROGRAM4_OBJS} 
	${CXX} ${COMMON_OBJS} ${PROGRAM4_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM5}:${COMMON_OBJS} ${PROGRAM5_OBJS} 
	${CXX} ${COMMON_OBJS} ${PROGRAM5_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM6}:${COMMON_OBJS} ${PROGRAM6_OBJS} 
	${CXX} ${COMMON_OBJS} ${PROGRAM6_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM7}:${COMMON_OBJS} ${PROGRAM7_OBJS} 
	${CXX} ${COMMON_OBJS} ${PROGRAM7_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 
	
${PROGRAM8}:${COMMON_OBJS} ${PROGRAM8_OBJS} 
	${CXX} ${COMMON_OBJS} ${PROGRAM8_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM9}:${COMMON_OBJS} ${PROGRAM9_OBJS} 
	${CXX} ${COMMON_OBJS} ${PROGRAM9_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 


clean:
	find . -type f | xargs touch
	rm -rf *.o
	rm -rf ${PROGRAM1} 
	rm -rf ${PROGRAM2} 
	rm -rf ${PROGRAM3} 
	rm -rf ${PROGRAM4} 
	rm -rf ${PROGRAM5} 
	rm -rf ${PROGRAM6} 
	rm -rf ${PROGRAM7} 
	rm -rf ${PROGRAM8} 
	rm -rf ${PROGRAM9} 
