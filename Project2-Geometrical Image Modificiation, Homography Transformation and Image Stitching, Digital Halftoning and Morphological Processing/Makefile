CXX= ${CROSS_COMPILE}g++


PROGRAM10 = ./bin/shrink
PROGRAM11 = ./bin/thin
PROGRAM12 = ./bin/skel
PROGRAM13 = ./bin/count
PROGRAM14 = ./bin/uniquecount
PROGRAM15 = ./bin/dither
PROGRAM16 = ./bin/fourleveldither
PROGRAM17 = ./bin/errordiff
PROGRAM18 = ./bin/separablediff
PROGRAM19 = ./bin/MBVQ
PROGRAM20 = ./bin/warp
PROGRAM21 = ./bin/Homography

CFLAGS=-std=c++11 -g

COMMON_OBJS = 	 
				

PROGRAM10_OBJS= STK.o shrink_Main.o
PROGRAM11_OBJS= STK.o thin_Main.o
PROGRAM12_OBJS= STK.o skel_Main.o
PROGRAM13_OBJS= counting_game.o counting_Main.o
PROGRAM14_OBJS= unique_counting.o unique_counting_Main.o
PROGRAM15_OBJS= DitherFunc.o DitheringMain.o
PROGRAM16_OBJS= four_level_dither_func.o four_level_dither_Main.o
PROGRAM17_OBJS= ErrorDiffusionFunc.o ErrorDiffusionMain.o
PROGRAM18_OBJS= Separable_Diffusion.o Separable_DiffusionMain.o
PROGRAM19_OBJS= MBVQ.o MBVQ_Main.o
PROGRAM20_OBJS= Dewarping.o
PROGRAM21_OBJS= HomographyStitching.o HomographyMain.o




INCLUDE=  -I ./

LIB= 

LDFLAGS= -lm 

vpath %.cpp ./


all: ${PROGRAM10} ${PROGRAM11} ${PROGRAM12} ${PROGRAM13} ${PROGRAM14} ${PROGRAM15} \
     ${PROGRAM16} ${PROGRAM17} ${PROGRAM18} ${PROGRAM19} ${PROGRAM20} ${PROGRAM21}

shrink          : ${PROGRAM10}
thin            : ${PROGRAM11}
skel            : ${PROGRAM12}
count 			: ${PROGRAM13}
unique_count    : ${PROGRAM14}
dither          : ${PROGRAM15}
fourleveldither : ${PROGRAM16}
errordiffusion  : ${PROGRAM17}
separableDiff   : ${PROGRAM18}
MBVQ            : ${PROGRAM19}
warp            : ${PROGRAM20}
homography      : ${PROGRAM21}

.cpp.o:
	${CXX} ${CFLAGS} ${INCLUDE} -c $< ${LIB} -o $@
	
${PROGRAM10}:${COMMON_OBJS} ${PROGRAM10_OBJS}
	${CXX} ${COMMON_OBJS} ${PROGRAM10_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM11}:${COMMON_OBJS} ${PROGRAM11_OBJS}
	${CXX} ${COMMON_OBJS} ${PROGRAM11_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM12}:${COMMON_OBJS} ${PROGRAM12_OBJS}
	${CXX} ${COMMON_OBJS} ${PROGRAM12_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM13}:${COMMON_OBJS} ${PROGRAM13_OBJS}
	${CXX} ${COMMON_OBJS} ${PROGRAM13_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM14}:${COMMON_OBJS} ${PROGRAM14_OBJS}
	${CXX} ${COMMON_OBJS} ${PROGRAM14_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM15}:${COMMON_OBJS} ${PROGRAM15_OBJS}
	${CXX} ${COMMON_OBJS} ${PROGRAM15_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM16}:${COMMON_OBJS} ${PROGRAM16_OBJS}
	${CXX} ${COMMON_OBJS} ${PROGRAM16_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM17}:${COMMON_OBJS} ${PROGRAM17_OBJS}
	${CXX} ${COMMON_OBJS} ${PROGRAM17_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM18}:${COMMON_OBJS} ${PROGRAM18_OBJS}
	${CXX} ${COMMON_OBJS} ${PROGRAM18_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM19}:${COMMON_OBJS} ${PROGRAM19_OBJS}
	${CXX} ${COMMON_OBJS} ${PROGRAM19_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM20}:${COMMON_OBJS} ${PROGRAM20_OBJS}
	${CXX} ${COMMON_OBJS} ${PROGRAM20_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 

${PROGRAM21}:${COMMON_OBJS} ${PROGRAM21_OBJS}
	${CXX} ${COMMON_OBJS} ${PROGRAM21_OBJS} ${CFLAGS} ${INCLUDE} -o $@ $(LIB) ${LDFLAGS} 


clean:
	find . -type f | xargs touch
	rm -rf *.o
	rm -fr ${PROGRAM10}
	rm -fr ${PROGRAM11}
	rm -fr ${PROGRAM12}
	rm -fr ${PROGRAM13}
	rm -fr ${PROGRAM14}
	rm -fr ${PROGRAM15}
	rm -fr ${PROGRAM16}
	rm -fr ${PROGRAM17}
	rm -fr ${PROGRAM18}
	rm -fr ${PROGRAM19}
	rm -fr ${PROGRAM20}
	rm -fr ${PROGRAM21}
