#pragma once

#include "antares/optimisation/linear-problem-api/linearProblemFiller.h"
#include "antares/solver/utils/named_problem.h"

namespace Antares::Optimization
{
class LegacyFiller: public Optimization::LinearProblemApi::LinearProblemFiller
{
public:
    explicit LegacyFiller(const PROBLEME_SIMPLEXE_NOMME* problemeSimplexe);
    void addVariables(Optimization::LinearProblemApi::ILinearProblem& pb,
                      Optimization::LinearProblemApi::ILinearProblemData& data,
                      Optimization::LinearProblemApi::FillContext& ctx) override;
    void addConstraints(Optimization::LinearProblemApi::ILinearProblem& pb,
                        Optimization::LinearProblemApi::ILinearProblemData& data,
                        Optimization::LinearProblemApi::FillContext& ctx) override;
    void addObjective(Optimization::LinearProblemApi::ILinearProblem& pb,
                      Optimization::LinearProblemApi::ILinearProblemData& data,
                      Optimization::LinearProblemApi::FillContext& ctx) override;

private:
    const PROBLEME_SIMPLEXE_NOMME* problemeSimplexe_;

    void CreateVariable(unsigned idxVar, Optimization::LinearProblemApi::ILinearProblem& pb) const;
    void CopyVariables(Optimization::LinearProblemApi::ILinearProblem& pb) const;
    void UpdateContraints(unsigned idxRow,
                          Optimization::LinearProblemApi::ILinearProblem& pb) const;
    void CopyRows(Optimization::LinearProblemApi::ILinearProblem& pb) const;
    void CopyMatrix(Optimization::LinearProblemApi::ILinearProblem& pb) const;
    std::string GetVariableName(unsigned index) const;
    std::string GetConstraintName(unsigned index) const;
};
} // namespace Antares::Optimization
