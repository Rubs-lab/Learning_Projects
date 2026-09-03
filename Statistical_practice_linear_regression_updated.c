#include <stdio.h>
#include <math.h>

double mean(double data[], int size);
double variance(double data_[], int size);
double standard_deviation(double data[], int size);
double covariance(double data_x[], double data_y[], int size);
double correlation_coefficient(double data_x[], double data_y[], int size);
double slope(double data_x[], double data_y[], int size);
double intercept(double data_x[], double data_y[], int size);
double predict(double x, double slope_value, double intercept_value);

int main() {
    int n;
    printf("How many data points do you want to enter?\n");
    scanf("%d", &n);

    while (n<=0) { // Check if the number of data points is less than or equal to 0
        printf("Seriously!!? Try again.\n");
        printf("PLease enter a valid number of data points greater than 0.\n");
        scanf("%d", &n);
        if (n > 0) {
            printf("Yay!! You did it!\n");
        }
    }

    double data_x[n]; // Declare an array to hold the x data points
    double data_y[n]; // Declare an array to hold the y data points

    for (int i = 0; i < n; i++) { // Loop to get the x data points from the user
        printf("Enter data x[%d]: ", i);
        scanf("%lf", &data_x[i]);
    }

    for (int i = 0; i < n; i++) { // Loop to get the y data points from the user
        printf("Enter data y[%d]: ", i);
        scanf("%lf", &data_y[i]);
    }
    
    double average_x = mean(data_x, n);
    double average_y = mean(data_y, n);

    double var_x = variance(data_x, n);
    double var_y = variance(data_y, n);

    double std_dev_x = standard_deviation(data_x, n);
    double std_dev_y = standard_deviation(data_y, n);

    double corr = correlation_coefficient(data_x, data_y, n);

    double slope_value = slope(data_x, data_y, n);
    double intercept_value = intercept(data_x, data_y, n);
    

    for (int i = 0; i < n; i++) {
        printf("Data x number of n is %d and its value is %.2f\n", i, data_x[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("Data y number of n is %d and its value is %.2f\n", i, data_y[i]);
    }

    printf("The mean of data x is %.2f\n", average_x);
    printf("The variance of data x is %.2f\n", var_x);
    printf("The standard deviation of data x is %.2f\n", std_dev_x);
    printf("The mean of data y is %.2f\n", average_y);
    printf("The variance of data y is %.2f\n", var_y);
    printf("The standard deviation of data y is %.2f\n", std_dev_y);

    double cov = covariance(data_x, data_y, n); // Calculate the covariance of data x and y
    if (cov > 0) {
        printf("The covariance of data x and y is %.2f, and thus Positive \n", cov);
    } else if (cov < 0) {
        printf("The covariance of data x and y is %.2f, and thus Negative \n", cov);
    } else {
        printf("The covariance of data x and y is %.2f, and thus Zero \n", cov);
    }

    if (corr > 0) { // Check if the correlation coefficient is positive
        printf("The correlation coefficient of data x and y is %.2f, and thus the data sets of x and y have a strong tendency to move in a positive linear direction.\n", corr);
    } else if (corr < 0) {
        printf("The correlation coefficient of data x and y is %.2f\n and thus the data sets of x and y have a strong tendency to move in a negative linear direction.\n", corr);
    } else {
        printf("The correlation coefficient of data x and y is %.2f\n and thus Zero which indicates no linea10r relationship", corr);
    }


    printf("The slope of the regression line is %.2f\n", slope_value);
    printf("The intercept of the regression line is %.2f\n", intercept_value);

    int number_of_predictions; // Variable to hold the number of predictions the user wants to make
    printf("How many x values would you like to predict?\n");
    scanf("%d", &number_of_predictions);

    while (number_of_predictions <= 0) {
        printf("Seriously!!? Try again.\n");
        printf("Please enter a valid number of predictions greater than 0.\n");
        scanf("%d", &number_of_predictions);    
    }
     
     double user_x[number_of_predictions];

     for (int i = 0; i < number_of_predictions; i++) { // Loop to get the x values from the user for prediction
        printf("Enter x value %d: ", i + 1);
        scanf("%lf", &user_x[i]);
    }
    printf("\nPredicted y values:\n");
    for (int i = 0; i < number_of_predictions; i++) {
        double predicted_y = predict(user_x[i], slope_value, intercept_value);
        printf("The predicted value for the given x[%d] is %.2f\n", i, predicted_y);
    }

    printf("\nThank you for using the program! Goodbye!\n");

    return 0;}

double mean(double data[], int size) { // Function to calculate the mean of an array of data
    if (size <= 0) {
        return 0.0;
    }


    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }

    return sum / size;
}

double variance(double data[], int size) { // Function to calculate the variance of an array of data
    if (size <= 0) {
        return 0.0;
    }

    double avg = mean(data, size);
    double sumSquaredDiffs = 0.0;

    for (int i = 0; i < size; i++) {
        double diff = data[i] - avg;
        sumSquaredDiffs += diff * diff;
    }

    return sumSquaredDiffs / size;
}

double standard_deviation(double data[], int size) { // Function to calculate the standard deviation of an array of data
    if (size <= 0) {
        return 0.0;
    }

    double var = variance(data, size);
    return sqrt(var);
}

double covariance(double data_x[], double data_y[], int size) { // Function to calculate the covariance of two arrays of data
    if (size <= 0) {
        return 0.0;
    }

    double mean_x = mean(data_x, size);
    double mean_y = mean(data_y, size);
    double sumCovariance = 0.0;

    for (int i = 0; i < size; i++) {
        sumCovariance += (data_x[i] - mean_x) * (data_y[i] - mean_y);
    }

    return sumCovariance / size;
}

double correlation_coefficient(double data_x[], double data_y[], int size) { // Function to calculate the correlation coefficient of two arrays of data
    if (size <= 0) {
        return 0.0;
    }

    double cov = covariance(data_x, data_y, size);
    double std_dev_x = standard_deviation(data_x, size);
    double std_dev_y = standard_deviation(data_y, size);

    if (std_dev_x == 0 || std_dev_y == 0) {
        return 0.0;
    }

    return cov / (std_dev_x * std_dev_y);
}

double slope(double data_x[], double data_y[], int size) { // Function to calculate the slope of the regression line for two arrays of data
    if (size <= 0) {
        return 0.0;
    }

    double cov = covariance(data_x, data_y, size);
    double var_x = variance(data_x, size);

    if (var_x == 0.0) {
        return 0.0;
    }

    return cov / var_x;
}

double intercept(double data_x[], double data_y[], int size) { // Function to calculate the intercept of the regression line for two arrays of data
    if (size <= 0) {
        return 0.0;
    }

    double mean_x = mean(data_x, size);
    double mean_y = mean(data_y, size);
    double slope_value = slope(data_x, data_y, size);

    return mean_y - slope_value * mean_x;
}

double predict(double data_x, double slope, double intercept) { // Function to predict the y value for a given x value using the regression line equation
    return slope * data_x + intercept;
    }