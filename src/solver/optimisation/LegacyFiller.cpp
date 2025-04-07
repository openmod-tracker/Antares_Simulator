#include "antares/solver/optimisation/LegacyFiller.h"

#include <chrono>
#include <iostream>

using namespace Antares::Optimisation::LinearProblemApi;

namespace Antares::Optimization
{

LegacyFiller::LegacyFiller(const Antares::Optimization::PROBLEME_SIMPLEXE_NOMME* problemeSimplexe):
    problemeSimplexe_(problemeSimplexe)
{
}

void LegacyFiller::addVariables(ILinearProblem& pb, ILinearProblemData& data, FillContext& ctx)
{
    auto start = std::chrono::system_clock::now();
    // Create the variables and set objective cost.
    CopyVariables(pb);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Legacy variables in " << elapsed_seconds.count() << " seconds." << std::endl;
}

void LegacyFiller::addConstraints(ILinearProblem& pb, ILinearProblemData& data, FillContext& ctx)
{
    auto start = std::chrono::system_clock::now();
    // Create constraints and set coefs
    CopyRows(pb);
    CopyMatrix(pb);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Legacy constraints in " << elapsed_seconds.count() << " seconds." << std::endl;
}

void LegacyFiller::addObjective(ILinearProblem& pb, ILinearProblemData& data, FillContext& ctx)
{
    // nothing to do: objective coefficients are set along with variables definition
}

void LegacyFiller::CopyMatrix(ILinearProblem& pb) const
{
    for (int idxRow = 0; idxRow < problemeSimplexe_->NombreDeContraintes; ++idxRow)
    {
        auto* ct = pb.getConstraint(idxRow);
        int debutLigne = problemeSimplexe_->IndicesDebutDeLigne[idxRow];
        for (int idxCoef = 0; idxCoef < problemeSimplexe_->NombreDeTermesDesLignes[idxRow];
             ++idxCoef)
        {
            int pos = debutLigne + idxCoef;
            auto* var = pb.getVariable(problemeSimplexe_->IndicesColonnes[pos]);
            ct->setCoefficient(var, problemeSimplexe_->CoefficientsDeLaMatriceDesContraintes[pos]);
        }
    }
}

void LegacyFiller::CreateVariable(unsigned idxVar, ILinearProblem& pb) const
{
    const double bMin = problemeSimplexe_->Xmin[idxVar];
    const double bMax = problemeSimplexe_->Xmax[idxVar];
    const int typeVar = problemeSimplexe_->TypeDeVariable[idxVar];

    double min_l = (typeVar == VARIABLE_NON_BORNEE || typeVar == VARIABLE_BORNEE_SUPERIEUREMENT)
                     ? -pb.infinity()
                     : bMin;
    double max_l = (typeVar == VARIABLE_NON_BORNEE || typeVar == VARIABLE_BORNEE_INFERIEUREMENT)
                     ? pb.infinity()
                     : bMax;
    const bool isIntegerVariable = problemeSimplexe_->IntegerVariable(idxVar);

    auto* var = pb.addVariable(min_l, max_l, isIntegerVariable, GetVariableName(idxVar));
    pb.setObjectiveCoefficient(var, problemeSimplexe_->CoutLineaire[idxVar]);
}

void LegacyFiller::CopyVariables(ILinearProblem& pb) const
{
    for (int idxVar = 0; idxVar < problemeSimplexe_->NombreDeVariables; ++idxVar)
    {
        CreateVariable(idxVar, pb);
    }
    std::cout << "Legacy variables : " << problemeSimplexe_->NombreDeVariables << std::endl;
}

void LegacyFiller::UpdateContraints(unsigned idxRow, ILinearProblem& pb) const
{
    double bMin = -pb.infinity(), bMax = pb.infinity();
    switch (problemeSimplexe_->Sens[idxRow])
    {
    case '=':
        bMin = bMax = problemeSimplexe_->SecondMembre[idxRow];
        break;
    case '<':
        bMax = problemeSimplexe_->SecondMembre[idxRow];
        break;
    case '>':
        bMin = problemeSimplexe_->SecondMembre[idxRow];
        break;
    }

    pb.addConstraint(bMin, bMax, GetConstraintName(idxRow));
}

void LegacyFiller::CopyRows(ILinearProblem& pb) const
{
    for (int idxRow = 0; idxRow < problemeSimplexe_->NombreDeContraintes; ++idxRow)
    {
        UpdateContraints(idxRow, pb);
    }
    std::cout << "Legacy constraints : " << problemeSimplexe_->NombreDeContraintes << std::endl;
}

std::string LegacyFiller::GetVariableName(unsigned int index) const
{
    if (!problemeSimplexe_->UseNamedProblems()
        || problemeSimplexe_->VariableNames().at(index).empty())
    {
        return 'x' + std::to_string(index);
    }
    return problemeSimplexe_->VariableNames().at(index);
}

std::string LegacyFiller::GetConstraintName(unsigned int index) const
{
    if (!problemeSimplexe_->UseNamedProblems()
        || problemeSimplexe_->ConstraintNames().at(index).empty())
    {
        return 'c' + std::to_string(index);
    }
    return problemeSimplexe_->ConstraintNames().at(index);
}
} // namespace Antares::Optimization
