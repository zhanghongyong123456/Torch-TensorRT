#pragma once
#include <memory>
#include "torch/csrc/jit/ir/ir.h"

namespace trtorch {
namespace core {
namespace lowering {

struct LowerInfo {
  // Internal flag to ensure torch.jit.Module does not get freezed in lowering.cpp. This is required for QAT models.
  bool unfreeze_module;
};

void LowerBlock(torch::jit::Block* b);
void LowerGraph(std::shared_ptr<torch::jit::Graph>& g, bool disable_cse=false);
torch::jit::Module LowerModule(const torch::jit::script::Module& mod);
std::pair<std::shared_ptr<torch::jit::Graph>, std::vector<torch::jit::IValue>> Lower(
    const torch::jit::script::Module& mod,
    std::string method_name,
    LowerInfo lower_info);

} // namespace lowering
} // namespace core
} // namespace trtorch
