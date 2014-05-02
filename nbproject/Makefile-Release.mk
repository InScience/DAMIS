#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=mpic++
CXX=mpic++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/ARFF.o \
	${OBJECTDIR}/AdditionalMethods.o \
	${OBJECTDIR}/DMA.o \
	${OBJECTDIR}/DataObject.o \
	${OBJECTDIR}/DimReductionMethod.o \
	${OBJECTDIR}/DistanceMetrics.o \
	${OBJECTDIR}/HPCMethod.o \
	${OBJECTDIR}/MDS.o \
	${OBJECTDIR}/ObjectMatrix.o \
	${OBJECTDIR}/PCA.o \
	${OBJECTDIR}/Projection.o \
	${OBJECTDIR}/SAMANN.o \
	${OBJECTDIR}/SDS.o \
	${OBJECTDIR}/SMACOF.o \
	${OBJECTDIR}/SMACOFZEIDEL.o \
	${OBJECTDIR}/SOM.o \
	${OBJECTDIR}/SOMMDS.o \
	${OBJECTDIR}/ShufleObjects.o \
	${OBJECTDIR}/Statistics.o \
	${OBJECTDIR}/alglib/alglibinternal.o \
	${OBJECTDIR}/alglib/alglibmisc.o \
	${OBJECTDIR}/alglib/ap.o \
	${OBJECTDIR}/alglib/dataanalysis.o \
	${OBJECTDIR}/alglib/diffequations.o \
	${OBJECTDIR}/alglib/fasttransforms.o \
	${OBJECTDIR}/alglib/integration.o \
	${OBJECTDIR}/alglib/interpolation.o \
	${OBJECTDIR}/alglib/linalg.o \
	${OBJECTDIR}/alglib/optimization.o \
	${OBJECTDIR}/alglib/solvers.o \
	${OBJECTDIR}/alglib/specialfunctions.o \
	${OBJECTDIR}/alglib/statistics.o \
	${OBJECTDIR}/cmdLineParser/CommandLineParser.o \
	${OBJECTDIR}/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f6 \
	${TESTDIR}/TestFiles/f7

# C Compiler Flags
CFLAGS=`cppunit-config --cflags` 

# CC Compiler Flags
CCFLAGS=`cppunit-config --cflags` 
CXXFLAGS=`cppunit-config --cflags` 

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=libalglib.so `cppunit-config --libs` `cppunit-config --libs`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${TESTDIR}/TestFiles/f4.exe

${TESTDIR}/TestFiles/f4.exe: libalglib.so

${TESTDIR}/TestFiles/f4.exe: ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f4 ${OBJECTFILES} ${LDLIBSOPTIONS} -L$HOME

${OBJECTDIR}/ARFF.o: ARFF.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ARFF.o ARFF.cpp

${OBJECTDIR}/AdditionalMethods.o: AdditionalMethods.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AdditionalMethods.o AdditionalMethods.cpp

${OBJECTDIR}/DMA.o: DMA.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DMA.o DMA.cpp

${OBJECTDIR}/DataObject.o: DataObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DataObject.o DataObject.cpp

${OBJECTDIR}/DimReductionMethod.o: DimReductionMethod.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DimReductionMethod.o DimReductionMethod.cpp

${OBJECTDIR}/DistanceMetrics.o: DistanceMetrics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DistanceMetrics.o DistanceMetrics.cpp

${OBJECTDIR}/HPCMethod.o: HPCMethod.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/HPCMethod.o HPCMethod.cpp

${OBJECTDIR}/MDS.o: MDS.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MDS.o MDS.cpp

${OBJECTDIR}/ObjectMatrix.o: ObjectMatrix.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ObjectMatrix.o ObjectMatrix.cpp

${OBJECTDIR}/PCA.o: PCA.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PCA.o PCA.cpp

${OBJECTDIR}/Projection.o: Projection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Projection.o Projection.cpp

${OBJECTDIR}/SAMANN.o: SAMANN.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SAMANN.o SAMANN.cpp

${OBJECTDIR}/SDS.o: SDS.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SDS.o SDS.cpp

${OBJECTDIR}/SMACOF.o: SMACOF.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SMACOF.o SMACOF.cpp

${OBJECTDIR}/SMACOFZEIDEL.o: SMACOFZEIDEL.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SMACOFZEIDEL.o SMACOFZEIDEL.cpp

${OBJECTDIR}/SOM.o: SOM.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SOM.o SOM.cpp

${OBJECTDIR}/SOMMDS.o: SOMMDS.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SOMMDS.o SOMMDS.cpp

${OBJECTDIR}/ShufleObjects.o: ShufleObjects.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ShufleObjects.o ShufleObjects.cpp

${OBJECTDIR}/Statistics.o: Statistics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Statistics.o Statistics.cpp

${OBJECTDIR}/alglib/alglibinternal.o: alglib/alglibinternal.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/alglibinternal.o alglib/alglibinternal.cpp

${OBJECTDIR}/alglib/alglibmisc.o: alglib/alglibmisc.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/alglibmisc.o alglib/alglibmisc.cpp

${OBJECTDIR}/alglib/ap.o: alglib/ap.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/ap.o alglib/ap.cpp

${OBJECTDIR}/alglib/dataanalysis.o: alglib/dataanalysis.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/dataanalysis.o alglib/dataanalysis.cpp

${OBJECTDIR}/alglib/diffequations.o: alglib/diffequations.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/diffequations.o alglib/diffequations.cpp

${OBJECTDIR}/alglib/fasttransforms.o: alglib/fasttransforms.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/fasttransforms.o alglib/fasttransforms.cpp

${OBJECTDIR}/alglib/integration.o: alglib/integration.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/integration.o alglib/integration.cpp

${OBJECTDIR}/alglib/interpolation.o: alglib/interpolation.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/interpolation.o alglib/interpolation.cpp

${OBJECTDIR}/alglib/linalg.o: alglib/linalg.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/linalg.o alglib/linalg.cpp

${OBJECTDIR}/alglib/optimization.o: alglib/optimization.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/optimization.o alglib/optimization.cpp

${OBJECTDIR}/alglib/solvers.o: alglib/solvers.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/solvers.o alglib/solvers.cpp

${OBJECTDIR}/alglib/specialfunctions.o: alglib/specialfunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/specialfunctions.o alglib/specialfunctions.cpp

${OBJECTDIR}/alglib/statistics.o: alglib/statistics.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/statistics.o alglib/statistics.cpp

${OBJECTDIR}/cmdLineParser/CommandLineParser.o: cmdLineParser/CommandLineParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/cmdLineParser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cmdLineParser/CommandLineParser.o cmdLineParser/CommandLineParser.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/arffTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} `cppunit-config --libs` `cppunit-config --libs`   

${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/gutmanTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f7: ${TESTDIR}/tests/methodsTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f7 $^ ${LDLIBSOPTIONS} 


${TESTDIR}/tests/arffTest.o: tests/arffTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -I. `cppunit-config --cflags` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/arffTest.o tests/arffTest.cpp


${TESTDIR}/tests/gutmanTest.o: tests/gutmanTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/gutmanTest.o tests/gutmanTest.cpp


${TESTDIR}/tests/methodsTest.o: tests/methodsTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -I. -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/methodsTest.o tests/methodsTest.cpp


${OBJECTDIR}/ARFF_nomain.o: ${OBJECTDIR}/ARFF.o ARFF.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ARFF.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ARFF_nomain.o ARFF.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ARFF.o ${OBJECTDIR}/ARFF_nomain.o;\
	fi

${OBJECTDIR}/AdditionalMethods_nomain.o: ${OBJECTDIR}/AdditionalMethods.o AdditionalMethods.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/AdditionalMethods.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AdditionalMethods_nomain.o AdditionalMethods.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/AdditionalMethods.o ${OBJECTDIR}/AdditionalMethods_nomain.o;\
	fi

${OBJECTDIR}/DMA_nomain.o: ${OBJECTDIR}/DMA.o DMA.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DMA.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DMA_nomain.o DMA.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DMA.o ${OBJECTDIR}/DMA_nomain.o;\
	fi

${OBJECTDIR}/DataObject_nomain.o: ${OBJECTDIR}/DataObject.o DataObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DataObject.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DataObject_nomain.o DataObject.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DataObject.o ${OBJECTDIR}/DataObject_nomain.o;\
	fi

${OBJECTDIR}/DimReductionMethod_nomain.o: ${OBJECTDIR}/DimReductionMethod.o DimReductionMethod.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DimReductionMethod.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DimReductionMethod_nomain.o DimReductionMethod.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DimReductionMethod.o ${OBJECTDIR}/DimReductionMethod_nomain.o;\
	fi

${OBJECTDIR}/DistanceMetrics_nomain.o: ${OBJECTDIR}/DistanceMetrics.o DistanceMetrics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DistanceMetrics.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DistanceMetrics_nomain.o DistanceMetrics.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DistanceMetrics.o ${OBJECTDIR}/DistanceMetrics_nomain.o;\
	fi

${OBJECTDIR}/HPCMethod_nomain.o: ${OBJECTDIR}/HPCMethod.o HPCMethod.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/HPCMethod.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/HPCMethod_nomain.o HPCMethod.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/HPCMethod.o ${OBJECTDIR}/HPCMethod_nomain.o;\
	fi

${OBJECTDIR}/MDS_nomain.o: ${OBJECTDIR}/MDS.o MDS.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/MDS.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MDS_nomain.o MDS.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/MDS.o ${OBJECTDIR}/MDS_nomain.o;\
	fi

${OBJECTDIR}/ObjectMatrix_nomain.o: ${OBJECTDIR}/ObjectMatrix.o ObjectMatrix.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ObjectMatrix.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ObjectMatrix_nomain.o ObjectMatrix.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ObjectMatrix.o ${OBJECTDIR}/ObjectMatrix_nomain.o;\
	fi

${OBJECTDIR}/PCA_nomain.o: ${OBJECTDIR}/PCA.o PCA.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/PCA.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PCA_nomain.o PCA.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/PCA.o ${OBJECTDIR}/PCA_nomain.o;\
	fi

${OBJECTDIR}/Projection_nomain.o: ${OBJECTDIR}/Projection.o Projection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Projection.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Projection_nomain.o Projection.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Projection.o ${OBJECTDIR}/Projection_nomain.o;\
	fi

${OBJECTDIR}/SAMANN_nomain.o: ${OBJECTDIR}/SAMANN.o SAMANN.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SAMANN.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SAMANN_nomain.o SAMANN.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SAMANN.o ${OBJECTDIR}/SAMANN_nomain.o;\
	fi

${OBJECTDIR}/SDS_nomain.o: ${OBJECTDIR}/SDS.o SDS.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SDS.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SDS_nomain.o SDS.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SDS.o ${OBJECTDIR}/SDS_nomain.o;\
	fi

${OBJECTDIR}/SMACOF_nomain.o: ${OBJECTDIR}/SMACOF.o SMACOF.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SMACOF.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SMACOF_nomain.o SMACOF.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SMACOF.o ${OBJECTDIR}/SMACOF_nomain.o;\
	fi

${OBJECTDIR}/SMACOFZEIDEL_nomain.o: ${OBJECTDIR}/SMACOFZEIDEL.o SMACOFZEIDEL.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SMACOFZEIDEL.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SMACOFZEIDEL_nomain.o SMACOFZEIDEL.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SMACOFZEIDEL.o ${OBJECTDIR}/SMACOFZEIDEL_nomain.o;\
	fi

${OBJECTDIR}/SOM_nomain.o: ${OBJECTDIR}/SOM.o SOM.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SOM.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SOM_nomain.o SOM.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SOM.o ${OBJECTDIR}/SOM_nomain.o;\
	fi

${OBJECTDIR}/SOMMDS_nomain.o: ${OBJECTDIR}/SOMMDS.o SOMMDS.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SOMMDS.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SOMMDS_nomain.o SOMMDS.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SOMMDS.o ${OBJECTDIR}/SOMMDS_nomain.o;\
	fi

${OBJECTDIR}/ShufleObjects_nomain.o: ${OBJECTDIR}/ShufleObjects.o ShufleObjects.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ShufleObjects.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ShufleObjects_nomain.o ShufleObjects.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ShufleObjects.o ${OBJECTDIR}/ShufleObjects_nomain.o;\
	fi

${OBJECTDIR}/Statistics_nomain.o: ${OBJECTDIR}/Statistics.o Statistics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Statistics.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Statistics_nomain.o Statistics.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Statistics.o ${OBJECTDIR}/Statistics_nomain.o;\
	fi

${OBJECTDIR}/alglib/alglibinternal_nomain.o: ${OBJECTDIR}/alglib/alglibinternal.o alglib/alglibinternal.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/alglib/alglibinternal.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/alglibinternal_nomain.o alglib/alglibinternal.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/alglib/alglibinternal.o ${OBJECTDIR}/alglib/alglibinternal_nomain.o;\
	fi

${OBJECTDIR}/alglib/alglibmisc_nomain.o: ${OBJECTDIR}/alglib/alglibmisc.o alglib/alglibmisc.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/alglib/alglibmisc.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/alglibmisc_nomain.o alglib/alglibmisc.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/alglib/alglibmisc.o ${OBJECTDIR}/alglib/alglibmisc_nomain.o;\
	fi

${OBJECTDIR}/alglib/ap_nomain.o: ${OBJECTDIR}/alglib/ap.o alglib/ap.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/alglib/ap.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/ap_nomain.o alglib/ap.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/alglib/ap.o ${OBJECTDIR}/alglib/ap_nomain.o;\
	fi

${OBJECTDIR}/alglib/dataanalysis_nomain.o: ${OBJECTDIR}/alglib/dataanalysis.o alglib/dataanalysis.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/alglib/dataanalysis.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/dataanalysis_nomain.o alglib/dataanalysis.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/alglib/dataanalysis.o ${OBJECTDIR}/alglib/dataanalysis_nomain.o;\
	fi

${OBJECTDIR}/alglib/diffequations_nomain.o: ${OBJECTDIR}/alglib/diffequations.o alglib/diffequations.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/alglib/diffequations.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/diffequations_nomain.o alglib/diffequations.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/alglib/diffequations.o ${OBJECTDIR}/alglib/diffequations_nomain.o;\
	fi

${OBJECTDIR}/alglib/fasttransforms_nomain.o: ${OBJECTDIR}/alglib/fasttransforms.o alglib/fasttransforms.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/alglib/fasttransforms.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/fasttransforms_nomain.o alglib/fasttransforms.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/alglib/fasttransforms.o ${OBJECTDIR}/alglib/fasttransforms_nomain.o;\
	fi

${OBJECTDIR}/alglib/integration_nomain.o: ${OBJECTDIR}/alglib/integration.o alglib/integration.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/alglib/integration.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/integration_nomain.o alglib/integration.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/alglib/integration.o ${OBJECTDIR}/alglib/integration_nomain.o;\
	fi

${OBJECTDIR}/alglib/interpolation_nomain.o: ${OBJECTDIR}/alglib/interpolation.o alglib/interpolation.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/alglib/interpolation.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/interpolation_nomain.o alglib/interpolation.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/alglib/interpolation.o ${OBJECTDIR}/alglib/interpolation_nomain.o;\
	fi

${OBJECTDIR}/alglib/linalg_nomain.o: ${OBJECTDIR}/alglib/linalg.o alglib/linalg.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/alglib/linalg.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/linalg_nomain.o alglib/linalg.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/alglib/linalg.o ${OBJECTDIR}/alglib/linalg_nomain.o;\
	fi

${OBJECTDIR}/alglib/optimization_nomain.o: ${OBJECTDIR}/alglib/optimization.o alglib/optimization.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/alglib/optimization.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/optimization_nomain.o alglib/optimization.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/alglib/optimization.o ${OBJECTDIR}/alglib/optimization_nomain.o;\
	fi

${OBJECTDIR}/alglib/solvers_nomain.o: ${OBJECTDIR}/alglib/solvers.o alglib/solvers.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/alglib/solvers.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/solvers_nomain.o alglib/solvers.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/alglib/solvers.o ${OBJECTDIR}/alglib/solvers_nomain.o;\
	fi

${OBJECTDIR}/alglib/specialfunctions_nomain.o: ${OBJECTDIR}/alglib/specialfunctions.o alglib/specialfunctions.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/alglib/specialfunctions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/specialfunctions_nomain.o alglib/specialfunctions.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/alglib/specialfunctions.o ${OBJECTDIR}/alglib/specialfunctions_nomain.o;\
	fi

${OBJECTDIR}/alglib/statistics_nomain.o: ${OBJECTDIR}/alglib/statistics.o alglib/statistics.cpp 
	${MKDIR} -p ${OBJECTDIR}/alglib
	@NMOUTPUT=`${NM} ${OBJECTDIR}/alglib/statistics.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alglib/statistics_nomain.o alglib/statistics.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/alglib/statistics.o ${OBJECTDIR}/alglib/statistics_nomain.o;\
	fi

${OBJECTDIR}/cmdLineParser/CommandLineParser_nomain.o: ${OBJECTDIR}/cmdLineParser/CommandLineParser.o cmdLineParser/CommandLineParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/cmdLineParser
	@NMOUTPUT=`${NM} ${OBJECTDIR}/cmdLineParser/CommandLineParser.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cmdLineParser/CommandLineParser_nomain.o cmdLineParser/CommandLineParser.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/cmdLineParser/CommandLineParser.o ${OBJECTDIR}/cmdLineParser/CommandLineParser_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -I. -I. -I. -I. -I. -I. -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f6 || true; \
	    ${TESTDIR}/TestFiles/f7 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${TESTDIR}/TestFiles/f4.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
