#include <iostream>
#include <vector>

//terms array corresponds to As. binaryCoefficients vector corresponds to Es and should have a size of zero on the most top-level function invocation. sum corresponds to S.
void GenerateAllSolutions(const unsigned long long int* terms, unsigned int termsCount, std::vector<std::vector<unsigned char> >& binaryCoefficients, long long int sum)
{
    if(sum < 0)
    {
        //Since the sum of positive numbers is always positive there exists no solution, so we return.
        return;
    }

    if(termsCount == 1)
    {
        //There is only one term in the summation, so we treat it as a special case.
        if(sum == 0)
        {
            std::vector<unsigned char> temp;
            temp.push_back(0);
            binaryCoefficients.push_back(temp);
            return;
        }
        if(terms[0] == sum)
        {
            std::vector<unsigned char> temp;
            temp.push_back(1);
            binaryCoefficients.push_back(temp);
            return;
        }
        return;
    }

    //We know there are more than one term in the summation, so we find the solutions in a recursive fashion.
    //First we find the solutions that don't include the current term.
    std::vector<std::vector<unsigned char> > solutionsWithoutCurrenTerm;
    GenerateAllSolutions(terms, termsCount - 1, solutionsWithoutCurrenTerm, sum);
    for(unsigned int i = 0; i < solutionsWithoutCurrenTerm.size(); ++i)
    {
        solutionsWithoutCurrenTerm[i].push_back(0);
        binaryCoefficients.push_back(solutionsWithoutCurrenTerm[i]);
    }
    //Then we find the solutions that include the current term.
    std::vector<std::vector<unsigned char> > solutionsWithCurrenTerm;
    GenerateAllSolutions(terms, termsCount - 1, solutionsWithCurrenTerm, sum - terms[termsCount - 1]);
    for(unsigned int i = 0; i < solutionsWithCurrenTerm.size(); ++i)
    {
        solutionsWithCurrenTerm[i].push_back(1);
        binaryCoefficients.push_back(solutionsWithCurrenTerm[i]);
    }
}

//terms array corresponds to As. binaryCoefficients vector corresponds to Es and should have a size of zero on the most top-level function invocation. sum corresponds to S.
void GenerateASingleSolution(const unsigned long long int* terms, unsigned int termsCount, std::vector<std::vector<unsigned char> >& binaryCoefficients, long long int sum)
{
    if(sum < 0)
    {
        //Since the sum of positive numbers is always positive there exists no solution, so we return.
        return;
    }

    if(termsCount == 1)
    {
        //There is only one term in the summation, so we treat it as a special case.
        if(sum == 0)
        {
            std::vector<unsigned char> temp;
            temp.push_back(0);
            binaryCoefficients.push_back(temp);
            return;
        }
        if(terms[0] == sum)
        {
            std::vector<unsigned char> temp;
            temp.push_back(1);
            binaryCoefficients.push_back(temp);
            return;
        }
        return;
    }

    //We know there are more than one term in the summation, so we find the solutions in a recursive fashion.
    //First we try to find a solution that doesn't include the current term.
    GenerateASingleSolution(terms, termsCount - 1, binaryCoefficients, sum);
    if(binaryCoefficients.size() == 1)
    {
        binaryCoefficients[0].push_back(0);
        return;
    }
    //Then we try to find a solution that includes the current term.
    GenerateASingleSolution(terms, termsCount - 1, binaryCoefficients, sum - terms[termsCount - 1]);
    if(binaryCoefficients.size() == 1)
    {
        binaryCoefficients[0].push_back(1);
        return;
    }
}

int main()
{
    char answer;

    std::cout << "Would you like to find all the solutions (y/n)? ";
    std::cin >> answer;

    unsigned int termsCount;

    std::cout << "Enter the number of terms: ";
    std::cin >> termsCount;

    unsigned long long int* terms = new unsigned long long int[termsCount];

    for(unsigned int i = 0; i < termsCount; ++i)
    {
        std::cout << "Enter term " << i + 1 << ": ";
        std::cin >> terms[i];
    }

    long long int sum;

    std::cout << "Enter the sum: ";
    std::cin >> sum;

    std::vector<std::vector<unsigned char> > binaryCoefficients;

    if(answer == 'y')
    {
        GenerateAllSolutions(terms, termsCount, binaryCoefficients, sum);
    }
    else
    {
        GenerateASingleSolution(terms, termsCount, binaryCoefficients, sum);
    }

    if(binaryCoefficients.size() == 0)
    {
        std::cout << "There are no solutions.\n";
    }
    else
    {
        //Printing the solutions:
        if(binaryCoefficients.size() == 1)
        {
            std::cout << "The solution is:\n";
        }
        else
        {
            std::cout << "The solutions are:\n";
        }
        for(unsigned int i = 0; i < binaryCoefficients.size(); ++i)
        {
            std::cout << i + 1 << ".\t";
            for(unsigned int j = 0; j < termsCount; ++j)
            {
                std::cout << static_cast<unsigned int>(binaryCoefficients[i][j]);
            }
            std::cout << std::endl;
        }
    }

    delete[] terms;

    int temp;
    std::cin >> temp;

    return 0;
}
