
import FWCore.ParameterSet.Config as cms

source = cms.Source(
	"PoolSource",
	noEventSort = cms.untracked.bool(True),
	duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
	fileNames = cms.untracked.vstring()
)
source.fileNames.extend([
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_0.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_1.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_10.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_11.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_12.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_13.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_14.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_15.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_16.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_17.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_18.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_19.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_2.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_20.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_21.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_22.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_23.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_24.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_25.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_26.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_27.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_28.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_29.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_3.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_30.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_31.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_32.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_33.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_34.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_35.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_36.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_37.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_38.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_39.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_4.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_40.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_5.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_6.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_7.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_8.root',
		'/store/cmst3/user/cmgtools/CMG/VBF_HToTauTau_M-115_7TeV-powheg-pythia6-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM/V2/PAT_CMG_V2_3_0/tree_CMG_9.root',
])
