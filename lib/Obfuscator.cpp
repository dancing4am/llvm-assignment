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
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Constants.h"

using namespace llvm;

static cl::opt<bool> UseBogus("bogus", cl::init(false), cl::desc("Use bogus conditional branch for splitting blocks"));

void printInfo(Function &F) {
  errs() << "Obfuscator test running " << F.getName()
         << (UseBogus ? ", using bogus" : "") << "\n";
}

PreservedAnalyses Obfuscator::run(Function &F,
				  FunctionAnalysisManager &FAM) {
  printInfo(F);

  std::list<BasicBlock*> BBs;
  std::transform(F.begin(), F.end(), std::back_inserter(BBs), [](BasicBlock& BB) { return &BB; });

  if (UseBogus) {
    for (BasicBlock *BB : BBs) {
      Instruction *splitPoint = &*std::next(BB->begin(), BB->size() /2);

      IRBuilder<> Builder(BB);
      ConstantInt *cond = ConstantInt::getTrue(BB->getContext());

      BasicBlock *thenBB = nullptr;
      BasicBlock *elseBB = nullptr;
      SplitBlockAndInsertIfThenElse(cond, splitPoint, &BB, &thenBB, &elseBB);
    }
  }
  else {
    for (BasicBlock *BB : BBs) {
      Instruction *splitPoint = &*std::next(BB->begin(), BB->size() / 2);
      SplitBlock(BB, splitPoint);
    }
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
