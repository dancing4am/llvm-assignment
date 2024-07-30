#ifndef LLVM_ASSIGNMENT_OBFUSCATOR_H
#define LLVM_ASSIGNMENT_OBFUSCATOR_H

#include "llvm/IR/PassManager.h"

struct Obfuscator : public llvm::PassInfoMixin<Obfuscator> {
  llvm::PreservedAnalyses run(llvm::Function &F, llvm::FunctionAnalysisManager &);

  static bool isRequired() { return true; }
};

#endif
