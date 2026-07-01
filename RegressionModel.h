#pragma once

#include <iostream>
using namespace std;

class LinearRegressionModel
{
private:
    double slope;
    double intercept;
    double meanSquaredError;
    double averageGrowth;
    bool trained;

    double makePositive(double value) const
    {
        if (value < 0.0)
        {
            return value * -1.0;
        }

        return value;
    }

public:
    LinearRegressionModel()
    {
        slope = 0.0;
        intercept = 0.0;
        meanSquaredError = 0.0;
        averageGrowth = 0.0;
        trained = false;
    }

    bool train(const double xValues[], const double yValues[], int count)
    {
        if (count < 2)
        {
            trained = false;
            slope = 0.0;
            intercept = 0.0;
            meanSquaredError = 0.0;
            averageGrowth = 0.0;
            return false;
        }

        double sumX = 0.0;
        double sumY = 0.0;
        double sumXY = 0.0;
        double sumXSquare = 0.0;
        double growthTotal = 0.0;

        for (int i = 0; i < count; i++)
        {
            sumX = sumX + xValues[i];
            sumY = sumY + yValues[i];
            sumXY = sumXY + (xValues[i] * yValues[i]);
            sumXSquare = sumXSquare + (xValues[i] * xValues[i]);

            if (i > 0)
            {
                growthTotal = growthTotal + (yValues[i] - yValues[i - 1]);
            }
        }

        double denominator = ((double)count * sumXSquare) - (sumX * sumX);

        if (denominator == 0.0)
        {
            trained = false;
            return false;
        }

        slope = (((double)count * sumXY) - (sumX * sumY)) / denominator;
        intercept = (sumY - (slope * sumX)) / (double)count;
        averageGrowth = growthTotal / (double)(count - 1);

        double errorSquareTotal = 0.0;

        for (int i = 0; i < count; i++)
        {
            double predictedValue = intercept + (slope * xValues[i]);
            double errorValue = yValues[i] - predictedValue;
            errorSquareTotal = errorSquareTotal + (errorValue * errorValue);
        }

        meanSquaredError = errorSquareTotal / (double)count;
        trained = true;
        return true;
    }

    double predictLinear(double xValue) const
    {
        if (trained == false)
        {
            return 0.0;
        }

        return intercept + (slope * xValue);
    }

    double predict(double xValue) const
    {
        return predictLinear(xValue);
    }

    double predictTrend(double lastValue) const
    {
        if (trained == false)
        {
            return lastValue;
        }

        return lastValue + averageGrowth;
    }

    double predictFinal(double xValue, double lastValue) const
    {
        if (trained == false)
        {
            return lastValue;
        }

        double linearValue = predictLinear(xValue);
        double trendValue = predictTrend(lastValue);
        return (0.70 * linearValue) + (0.30 * trendValue);
    }

    double calculateError(double actualValue, double predictedValue) const
    {
        return actualValue - predictedValue;
    }

    double calculateAbsoluteError(double actualValue, double predictedValue) const
    {
        return makePositive(actualValue - predictedValue);
    }

    double calculateRecommendedOrder(double predictedDemand, double safeDays, double currentQuantity) const
    {
        double orderQuantity = (predictedDemand * safeDays) - currentQuantity;

        if (orderQuantity < 0.0)
        {
            orderQuantity = 0.0;
        }

        return orderQuantity;
    }

    double getSlope() const
    {
        return slope;
    }

    double getIntercept() const
    {
        return intercept;
    }

    double getMeanSquaredError() const
    {
        return meanSquaredError;
    }

    double getAverageGrowth() const
    {
        return averageGrowth;
    }

    bool isTrained() const
    {
        return trained;
    }

    void showFormula() const
    {
        if (trained == false)
        {
            cout << "Linear Regression Formula: not trained yet" << endl;
            return;
        }

        cout << "Linear Regression Formula: y = " << intercept << " + (" << slope << " * x)" << endl;
    }

    void showSixMathematicalFormulas() const
    {
        /*cout << "Six Mathematical Regression Formulas Used" << endl;
        cout << "M1. Slope: b = (n * sum(xy) - sum(x) * sum(y)) / (n * sum(x^2) - sum(x)^2)" << endl;
        cout << "M2. Intercept: a = (sum(y) - b * sum(x)) / n" << endl;
        cout << "M3. Linear Prediction: yHat = a + b * x" << endl;
        cout << "M4. Prediction Error: error = actualValue - predictedValue" << endl;
        cout << "M5. Mean Squared Error: mse = sum(error^2) / n" << endl;
        cout << "M6. Final Demand Prediction: final = (0.70 * linearPrediction) + (0.30 * trendPrediction)" << endl;*/ 
    }
};

class LogisticRegressionModel
{
private:
    double bias;
    double firstWeight;
    double secondWeight;
    double thirdWeight;
    double fourthWeight;
    double fifthWeight;
    double decisionThreshold;

    double makeSafeProbability(double probability) const
    {
        if (probability < 0.000001)
        {
            return 0.000001;
        }

        if (probability > 0.999999)
        {
            return 0.999999;
        }

        return probability;
    }

    double myExp(double value) const
    {
        if (value < 0.0)
        {
            return 1.0 / myExp(value * -1.0);
        }

        if (value > 20.0)
        {
            value = 20.0;
        }

        double answer = 1.0;
        double term = 1.0;

        for (int i = 1; i <= 30; i++)
        {
            term = term * value / (double)i;
            answer = answer + term;
        }

        return answer;
    }

    double myLog(double value) const
    {
        if (value <= 0.0)
        {
            return 0.0;
        }

        double eValue = 2.718281828459045;
        double answer = 0.0;

        while (value > eValue)
        {
            value = value / eValue;
            answer = answer + 1.0;
        }

        while (value < (1.0 / eValue))
        {
            value = value * eValue;
            answer = answer - 1.0;
        }

        double t = (value - 1.0) / (value + 1.0);
        double term = t;
        double square = t * t;
        double series = 0.0;

        for (int i = 1; i <= 39; i = i + 2)
        {
            series = series + (term / (double)i);
            term = term * square;
        }

        answer = answer + (2.0 * series);
        return answer;
    }

public:
    LogisticRegressionModel()
    {
        bias = -1.50;
        firstWeight = 1.10;
        secondWeight = 0.75;
        thirdWeight = 0.35;
        fourthWeight = 0.20;
        fifthWeight = 0.15;
        decisionThreshold = 0.50;
    }

    LogisticRegressionModel(double b, double w1, double w2, double w3)
    {
        bias = b;
        firstWeight = w1;
        secondWeight = w2;
        thirdWeight = w3;
        fourthWeight = 0.20;
        fifthWeight = 0.15;
        decisionThreshold = 0.50;
    }

    LogisticRegressionModel(double b, double w1, double w2, double w3, double w4, double w5)
    {
        bias = b;
        firstWeight = w1;
        secondWeight = w2;
        thirdWeight = w3;
        fourthWeight = w4;
        fifthWeight = w5;
        decisionThreshold = 0.50;
    }

    void setDecisionThreshold(double threshold)
    {
        if (threshold <= 0.0 || threshold >= 1.0)
        {
            return;
        }

        decisionThreshold = threshold;
    }

    double calculateZ(double firstFeature, double secondFeature, double thirdFeature, double fourthFeature = 0.0, double fifthFeature = 0.0) const
    {
        double zValue = bias;
        zValue = zValue + (firstWeight * firstFeature);
        zValue = zValue + (secondWeight * secondFeature);
        zValue = zValue + (thirdWeight * thirdFeature);
        zValue = zValue + (fourthWeight * fourthFeature);
        zValue = zValue + (fifthWeight * fifthFeature);
        return zValue;
    }

    double predictProbability(double firstFeature, double secondFeature, double thirdFeature, double fourthFeature = 0.0, double fifthFeature = 0.0) const
    {
        double zValue = calculateZ(firstFeature, secondFeature, thirdFeature, fourthFeature, fifthFeature);
        double probability = 1.0 / (1.0 + myExp(zValue * -1.0));
        return makeSafeProbability(probability);
    }

    double calculateOdds(double probability) const
    {
        probability = makeSafeProbability(probability);
        return probability / (1.0 - probability);
    }

    double calculateLogit(double probability) const
    {
        probability = makeSafeProbability(probability);
        return myLog(probability / (1.0 - probability));
    }

    int calculateDecision(double probability) const
    {
        probability = makeSafeProbability(probability);

        if (probability >= decisionThreshold)
        {
            return 1;
        }

        return 0;
    }

    double calculateRiskScore(double probability) const
    {
        probability = makeSafeProbability(probability);
        return probability * 100.0;
    }

    string getRiskLevel(double probability) const
    {
        probability = makeSafeProbability(probability);

        if (probability >= 0.80)
        {
            return "Very High Risk";
        }
        else if (probability >= 0.60)
        {
            return "High Risk";
        }
        else if (probability >= 0.40)
        {
            return "Medium Risk";
        }
        else
        {
            return "Low Risk";
        }
    }

    void showFormula() const
    {
        cout << "Logistic Regression Formula: p = 1 / (1 + e^(-z))" << endl;
        cout << "Where z = " << bias << " + (" << firstWeight << " * x1) + (" << secondWeight << " * x2) + (" << thirdWeight << " * x3) + (" << fourthWeight << " * x4) + (" << fifthWeight << " * x5)" << endl;
    }

    void showSixLogisticFormulas() const
    {
        cout << "Six Logistic Regression Formulas Used" << endl;
        cout << "L1. Weighted Score: z = b0 + b1*x1 + b2*x2 + b3*x3 + b4*x4 + b5*x5" << endl;
        cout << "L2. Probability: p = 1 / (1 + e^(-z))" << endl;
        cout << "L3. Odds: odds = p / (1 - p)" << endl;
        cout << "L4. Logit: logit = ln(p / (1 - p))" << endl;
        cout << "L5. Decision: class = 1 if p >= threshold, otherwise 0" << endl;
        cout << "L6. Risk Score: riskScore = p * 100" << endl;
    }
};

