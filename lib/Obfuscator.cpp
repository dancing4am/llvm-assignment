//=======================================================================
// FILE:
//	Obfuscator.cpp
//
// DESCRIPTION:
//	Splits each basic blocks in a function into two basic blocks,
//	and link them with an unconditional branch.
//
// USAGE:
//	$ opt -load-pass-plugin <BUILD_DIR>/lib//libObfuscator.so `\`
//      -passes=obfuscator -S <INPUT_LLVM_FILE> > <OUTPUT_LLVM_FILE>
//
// License: MIT
//=======================================================================
#include "Obfuscator.h"

#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

void printName(Function &F) {
  errs() << "Obfuscator test running: " << F.getName() << "\n";
}

PreservedAnalyses Obfuscator::run(Function &F,
				  FunctionAnalysisManager &FAM) {
  printName(F);

  std::vector<BasicBlock*> BBs;
  std::transform(F.begin(), F.end(), std::back_inserter(BBs), [](BasicBlock& BB) { return &BB; });

  for (BasicBlock *BB : BBs) {
    Instruction *splitPoint = &*std::next(BB->begin(), BB->size() / 2);
    SplitBlock(BB, splitPoint);
  }

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
