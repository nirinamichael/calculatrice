#pragma once

// Include
#include <math.h>

/**
 * @brief The core class
 * implement the calculator functionnality
 */
class core
{
public:
    /**
     * @brief The operators enum
     * Define some id for pointing the avalaible operations
     */
    enum operators : unsigned int
    {
        ADDITION,
        DIVISION,
        SUBSTRACTION,
        MULTIPLICATION
    };

    /**< Define an invalid result */
    static constexpr double invalid = 0;
public:
    /**
     * @brief mainframe
     * Constructor which instanciates the app
     */
    core(){}

public:
    /**
     * @brief compute performs a given operation btw two input values A and B
     * @param[in] pOperation : type of operation
     * @param[in] pValueA : operand A
     * @param[in] pValueB : operand B
     * @return The result of the operation
     */
    double compute(operators pOperation, double pValueA, double pValueB) const;

private:
    /**
     * @brief addition
     * @param[in] pValueA : operand A
     * @param[in] pValueB : operand B
     * @return The result of the operation
     */
    double addition(double pValueA, double pValueB) const;

};
