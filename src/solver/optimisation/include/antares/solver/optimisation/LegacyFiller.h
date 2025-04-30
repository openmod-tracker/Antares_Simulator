#pragma once

#include "antares/optimisation/linear-problem-api/linearProblemFiller.h"
#include "antares/solver/utils/named_problem.h"

namespace Antares::Optimization
{
class LegacyFiller: public LinearProblemApi::LinearProblemFiller
{
public:
    explicit LegacyFiller(const Solver::Utils::PROBLEME_SIMPLEXE_NOMME* problemeSimplexe);
    void addVariables(LinearProblemApi::ILinearProblem& pb,
                      LinearProblemApi::ILinearProblemData& data,
                      LinearProblemApi::FillContext& ctx) override;
    void addConstraints(LinearProblemApi::ILinearProblem& pb,
                        LinearProblemApi::ILinearProblemData& data,
                        LinearProblemApi::FillContext& ctx) override;
    void addObjective(LinearProblemApi::ILinearProblem& pb,
                      LinearProblemApi::ILinearProblemData& data,
                      LinearProblemApi::FillContext& ctx) override;

private:
    const Solver::Utils::PROBLEME_SIMPLEXE_NOMME* problemeSimplexe_;

    void CreateVariable(unsigned idxVar, LinearProblemApi::ILinearProblem& pb) const;
    void CopyVariables(LinearProblemApi::ILinearProblem& pb) const;
    void UpdateContraints(unsigned idxRow,
                          LinearProblemApi::ILinearProblem& pb) const;
    void CopyRows(LinearProblemApi::ILinearProblem& pb) const;
    void CopyMatrix(LinearProblemApi::ILinearProblem& pb) const;
    std::string GetVariableName(unsigned index) const;
    std::string GetConstraintName(unsigned index) const;
};
} // namespace Antares::Optimization
