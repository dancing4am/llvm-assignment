//=======================================================================
// FILE:
//	Obfuscator.cpp
//
// DESCRIPTION:
//	Splits each basic blocks in a function into two basic blocks,
//	and link them with an unconditional branch.
//
// USAGE:
//	opt -load-pass-plugin=
//
//=======================================================================
#include "Obfuscator.h"

#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

void printName(Function &F) {
  errs() << "Obfuscator test running: " << F.getName() << "\n";
}


PreservedAnalyses Obfuscator::run(Function &F,
				  FunctionAnalysisManager &FAM) {
  printName(F);
  return PreservedAnalyses::all();
}

//=======================================================================
// Registration
//=======================================================================
llvm::PassPluginLibraryInfo getObfuscatorPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "Obfuscator", LLVM_VERSION_STRING,
  [](PassBuilder &PB) {
    PB.registerPipelineParsingCallback(
    [](StringRef Name, FunctionPassManager &FPM,
    ArrayRef<PassBuilder::PipelineElement>) {
      if (Name == "obfuscator") {
	FPM.addPass(Obfuscator());
	  return true;
	}
	return false;
      });
  }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
	return getObfuscatorPluginInfo();
}
