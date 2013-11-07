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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/AdditionalMethods.o \
	${OBJECTDIR}/DMA.o \
	${OBJECTDIR}/DataObject.o \
	${OBJECTDIR}/DimReductionMethod.o \
	${OBJECTDIR}/DistanceMetrics.o \
	${OBJECTDIR}/Feature.o \
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
	${OBJECTDIR}/ShufleObjects.o \
	${OBJECTDIR}/Statistics.o \
	${OBJECTDIR}/arff.o \
	${OBJECTDIR}/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f6 \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f4 \
	${TESTDIR}/TestFiles/f5 \
	${TESTDIR}/TestFiles/f3

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=--coverage
CXXFLAGS=--coverage

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=alglib/libalglib.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/damis

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/damis: alglib/libalglib.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/damis: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/damis ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/AdditionalMethods.o: AdditionalMethods.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/AdditionalMethods.o AdditionalMethods.cpp

${OBJECTDIR}/DMA.o: DMA.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/DMA.o DMA.cpp

${OBJECTDIR}/DataObject.o: DataObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/DataObject.o DataObject.cpp

${OBJECTDIR}/DimReductionMethod.o: DimReductionMethod.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/DimReductionMethod.o DimReductionMethod.cpp

${OBJECTDIR}/DistanceMetrics.o: DistanceMetrics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/DistanceMetrics.o DistanceMetrics.cpp

${OBJECTDIR}/Feature.o: Feature.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/Feature.o Feature.cpp

${OBJECTDIR}/HPCMethod.o: HPCMethod.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/HPCMethod.o HPCMethod.cpp

${OBJECTDIR}/MDS.o: MDS.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/MDS.o MDS.cpp

${OBJECTDIR}/ObjectMatrix.o: ObjectMatrix.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/ObjectMatrix.o ObjectMatrix.cpp

${OBJECTDIR}/PCA.o: PCA.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/PCA.o PCA.cpp

${OBJECTDIR}/Projection.o: Projection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/Projection.o Projection.cpp

${OBJECTDIR}/SAMANN.o: SAMANN.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/SAMANN.o SAMANN.cpp

${OBJECTDIR}/SDS.o: SDS.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/SDS.o SDS.cpp

${OBJECTDIR}/SMACOF.o: SMACOF.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/SMACOF.o SMACOF.cpp

${OBJECTDIR}/SMACOFZEIDEL.o: SMACOFZEIDEL.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/SMACOFZEIDEL.o SMACOFZEIDEL.cpp

${OBJECTDIR}/SOM.o: SOM.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/SOM.o SOM.cpp

${OBJECTDIR}/ShufleObjects.o: ShufleObjects.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/ShufleObjects.o ShufleObjects.cpp

${OBJECTDIR}/Statistics.o: Statistics.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/Statistics.o Statistics.cpp

${OBJECTDIR}/arff.o: arff.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/arff.o arff.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g --coverage -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f6: ${TESTDIR}/tests/gutmanTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f6 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/pcatestclass.o ${TESTDIR}/tests/pcatestrunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} `cppunit-config --libs` `cppunit-config --libs`   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/ReadARFFtestclass.o ${TESTDIR}/tests/ReadARFFtestrunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   

${TESTDIR}/TestFiles/f4: ${TESTDIR}/tests/smacofTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f4 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f5: ${TESTDIR}/tests/smacofTestParallel.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f5 $^ ${LDLIBSOPTIONS} 

${TESTDIR}/TestFiles/f3: ${TESTDIR}/tests/smacofZeidelTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS} `cppunit-config --libs`   


${TESTDIR}/tests/gutmanTest.o: tests/gutmanTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. --coverage -MMD -MP -MF $@.d -o ${TESTDIR}/tests/gutmanTest.o tests/gutmanTest.cpp


${TESTDIR}/tests/pcatestclass.o: tests/pcatestclass.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g --coverage `cppunit-config --cflags` -MMD -MP -MF $@.d -o ${TESTDIR}/tests/pcatestclass.o tests/pcatestclass.cpp


${TESTDIR}/tests/pcatestrunner.o: tests/pcatestrunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g --coverage `cppunit-config --cflags` -MMD -MP -MF $@.d -o ${TESTDIR}/tests/pcatestrunner.o tests/pcatestrunner.cpp


${TESTDIR}/tests/ReadARFFtestclass.o: tests/ReadARFFtestclass.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g --coverage `cppunit-config --cflags` -MMD -MP -MF $@.d -o ${TESTDIR}/tests/ReadARFFtestclass.o tests/ReadARFFtestclass.cpp


${TESTDIR}/tests/ReadARFFtestrunner.o: tests/ReadARFFtestrunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g --coverage `cppunit-config --cflags` -MMD -MP -MF $@.d -o ${TESTDIR}/tests/ReadARFFtestrunner.o tests/ReadARFFtestrunner.cpp


${TESTDIR}/tests/smacofTest.o: tests/smacofTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. --coverage -MMD -MP -MF $@.d -o ${TESTDIR}/tests/smacofTest.o tests/smacofTest.cpp


${TESTDIR}/tests/smacofTestParallel.o: tests/smacofTestParallel.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. --coverage -MMD -MP -MF $@.d -o ${TESTDIR}/tests/smacofTestParallel.o tests/smacofTestParallel.cpp


${TESTDIR}/tests/smacofZeidelTest.o: tests/smacofZeidelTest.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} $@.d
	$(COMPILE.cc) -g -I. --coverage `cppunit-config --cflags` -MMD -MP -MF $@.d -o ${TESTDIR}/tests/smacofZeidelTest.o tests/smacofZeidelTest.cpp


${OBJECTDIR}/AdditionalMethods_nomain.o: ${OBJECTDIR}/AdditionalMethods.o AdditionalMethods.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/AdditionalMethods.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/AdditionalMethods_nomain.o AdditionalMethods.cpp;\
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
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/DMA_nomain.o DMA.cpp;\
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
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/DataObject_nomain.o DataObject.cpp;\
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
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/DimReductionMethod_nomain.o DimReductionMethod.cpp;\
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
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/DistanceMetrics_nomain.o DistanceMetrics.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DistanceMetrics.o ${OBJECTDIR}/DistanceMetrics_nomain.o;\
	fi

${OBJECTDIR}/Feature_nomain.o: ${OBJECTDIR}/Feature.o Feature.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Feature.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Feature_nomain.o Feature.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Feature.o ${OBJECTDIR}/Feature_nomain.o;\
	fi

${OBJECTDIR}/HPCMethod_nomain.o: ${OBJECTDIR}/HPCMethod.o HPCMethod.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/HPCMethod.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/HPCMethod_nomain.o HPCMethod.cpp;\
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
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/MDS_nomain.o MDS.cpp;\
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
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ObjectMatrix_nomain.o ObjectMatrix.cpp;\
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
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/PCA_nomain.o PCA.cpp;\
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
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Projection_nomain.o Projection.cpp;\
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
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/SAMANN_nomain.o SAMANN.cpp;\
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
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/SDS_nomain.o SDS.cpp;\
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
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/SMACOF_nomain.o SMACOF.cpp;\
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
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/SMACOFZEIDEL_nomain.o SMACOFZEIDEL.cpp;\
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
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/SOM_nomain.o SOM.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SOM.o ${OBJECTDIR}/SOM_nomain.o;\
	fi

${OBJECTDIR}/ShufleObjects_nomain.o: ${OBJECTDIR}/ShufleObjects.o ShufleObjects.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ShufleObjects.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/ShufleObjects_nomain.o ShufleObjects.cpp;\
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
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/Statistics_nomain.o Statistics.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Statistics.o ${OBJECTDIR}/Statistics_nomain.o;\
	fi

${OBJECTDIR}/arff_nomain.o: ${OBJECTDIR}/arff.o arff.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/arff.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/arff_nomain.o arff.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/arff.o ${OBJECTDIR}/arff_nomain.o;\
	fi

${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} $@.d;\
	    $(COMPILE.cc) -g --coverage -Dmain=__nomain -MMD -MP -MF $@.d -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f6 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f4 || true; \
	    ${TESTDIR}/TestFiles/f5 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/damis

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
