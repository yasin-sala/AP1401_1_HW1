#include "regression.h"

// reading CSV file
Data regression::read_database(std::string filepath)
{
    Data list;
    std::ifstream File(filepath);
    if (File.fail())
        throw std::runtime_error("something bad happend");
    else {
        std::string Line;
        while (std::getline(File, Line)) {
            std::string word;
            std::vector<double> row { 1 };
            std::stringstream line { Line };
            while (std::getline(line, word, ',')) {
                row.push_back(std::stod(word));
            }
            list.push_back(row);
        }
    }
    File.close();
    return list;
}
// how to calculate hypothesis
double regression::hypothesis(std::vector<double> theta, std::vector<double> x)
{
    double hypo {};
    if (theta.size() != x.size()) {
        throw std::logic_error("length must be equal");
    } else {
        for (size_t i {}; i < theta.size(); i++) {
            hypo += theta[i] * x[i];
        }
    }
    return hypo;
}
// calculation of cost function
double regression::cost_function(Data dataset, std::vector<double> theta)
{
    double cost {};
    for (size_t i {}; i < dataset.size(); i++) {
        std::vector<double> X { dataset[i][0], dataset[i][1], dataset[i][2], dataset[i][3] };
        cost += pow((hypothesis(X, theta) - dataset[i][4]), 2);
    }
    return cost / 2;
}
// Update the waights
std::vector<double> regression::update(Data dataset, std::vector<double> theta, double lr)
{
    std::vector<double> upd { 0, 0, 0, 0 };
    std::vector<double> tmp { theta };
    for (size_t jj {}; jj < 4; jj++) {
        for (size_t i {}; i < dataset.size(); i++) {
            std::vector<double> X { dataset[i][0], dataset[i][1], dataset[i][2], dataset[i][3] };
            upd[jj] += (hypothesis(X, theta) - dataset[i][4]) * dataset[i][jj];
        }
        tmp[jj] = tmp[jj] - lr * upd[jj];
    }
    return tmp;
}
// defining linear regression and show the reduced cost function and its iterator
std::vector<double> regression::linear_regression(Data dataset, std::vector<double> init_theta, double lr)
{
    int epoch { 10001 };
    std::vector<double> THETA { init_theta };
    std::vector<double> tmp { cost_function(dataset, THETA), 0 };
    THETA = update(dataset, THETA, lr);
    for (size_t i { 1 }; i < epoch; i++) {
        THETA = update(dataset, THETA, lr);
        cost_function(dataset, THETA);
        if (i > 9980) {
            std::cout << i << "\t--> cost: " << tmp[0] << "\t-- reduced cost: " << tmp[1] - tmp[0] << std::endl;
        }
        tmp[1] = tmp[0];
        tmp[0] = cost_function(dataset, THETA);
    }
    return THETA;
}