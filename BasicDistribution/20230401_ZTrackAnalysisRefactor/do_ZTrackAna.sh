#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh

CMSSWDir=/afs/cern.ch/user/p/pchou/CMSSW_12_5_2_patch1/src

cd $CMSSWDir

cmsenv

source /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/SetupAnalysis.sh

cd /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/BasicDistribution/20230401_ZTrackAnalysisRefactor

mkdir -p log

if [ $1 -eq 0 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputData_v12/ --Output GraphDataSignal_v12.root --Fraction 1
elif [ $1 -eq 1 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDatabkg_v12/ --Output GraphDataBackground_v12.root --Fraction 1
elif [ $1 -eq 2 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v12/ --Output GraphMCSignal_v12.root --Fraction 1
elif [ $1 -eq 3 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackground_v12/ --Output GraphMCBackground_v12.root --Fraction 1
elif [ $1 -eq 4 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v12/ --Output GraphPPMC_v12.root --IgnoreCentrality true --Fraction 1
elif [ $1 -eq 5 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v12/ --Output GraphPPMC0Sub_v12.root --IgnoreCentrality true --OnlyZeroSub true --Fraction 1
elif [ $1 -eq 6 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v12/ --Output GraphMCSignalGen_v12.root --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 7 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v12/ --Output GraphMCSignalGen0Sub_v12.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 8 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGen_v12/ --Output GraphMCBackgroundGen_v12.root --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 9 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCbkgGen_v12/ --Output GraphMCBackgroundGen0Sub_v12.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 10 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v12/ --Output GraphPPMCGen_v12.root --IgnoreCentrality true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 11 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v12/ --Output GraphPPMCGen0Sub_v12.root --IgnoreCentrality true  --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 12 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v12/ --Output GraphMCSignal0Sub_v12.root --OnlyZeroSub true --Fraction 1
elif [ $1 -eq 13 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPData_v12/ --Output GraphPPData_v12.root --IgnoreCentrality true --Fraction 1
else
	echo "Input number exceeded"
fi