#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_GenerateDataset_clicked()
{
    QString numNumbersStr = ui->lineEdit->text();
    bool ok;
    int numNumbers = numNumbersStr.toInt(&ok);

    if (!ok || numNumbers <= 0) {

        return;
    }
    QVector<int> randomNumbers;
    QString outputString;

    for (int i = 0; i < numNumbers; ++i) {
        int rand_num = QRandomGenerator::global()->bounded(0, 101);
        randomNumbers.append(rand_num);
        outputString += QString::number(rand_num) + "\n";
    }


    ui->plainTextEdit->setPlainText(outputString);
    for (int num : randomNumbers) {

    }
}


void merge(QVector<int>& numbers, int left, int mid, int right);
void mergeSort(QVector<int>& numbers, int left, int right);

void MainWindow::on_mergeSort_clicked()
{

    QString numbersText = ui->plainTextEdit->toPlainText();
    QStringList numberStrings = numbersText.split("\n", Qt::SkipEmptyParts);
    QVector<int> numbers;

    for (const QString& numberString : numberStrings) {
        bool ok;
        int number = numberString.toInt(&ok);
        if (ok) {
            numbers.append(number);
        }
    }

    mergeSort(numbers, 0, numbers.size() - 1);


    QString outputString = "Sorted numbers:\n";
    for (int number : numbers) {
        outputString += QString::number(number) + "\n";
    }


    ui->plainTextEdit->setPlainText(outputString);
}

void merge(QVector<int>& numbers, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    QVector<int> leftArray(n1);
    QVector<int> rightArray(n2);

    for (int i = 0; i < n1; ++i) {
        leftArray[i] = numbers[left + i];
    }

    for (int j = 0; j < n2; ++j) {
        rightArray[j] = numbers[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            numbers[k] = leftArray[i];
            ++i;
        } else {
            numbers[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        numbers[k] = leftArray[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        numbers[k] = rightArray[j];
        ++j;
        ++k;
    }
}

void mergeSort(QVector<int>& numbers, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(numbers, left, mid);
        mergeSort(numbers, mid + 1, right);

        merge(numbers, left, mid, right);
    }
}



#include <chrono>


int binarySearch(const QVector<int>& numbers, int target)
{
    int left = 0;
    int right = numbers.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (numbers[mid] == target) {
            return mid;
        } else if (numbers[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}


void MainWindow::on_FindIt_clicked()
{
    if(ns==true){
    QString numberToSearchStr = ui->lineEdit_2->text();
    bool ok;
    int numberToSearch = numberToSearchStr.toInt(&ok);

    if (!ok) {

        return;
    }

    QString numbersText = ui->plainTextEdit->toPlainText();
    QStringList numberStrings = numbersText.split("\n", Qt::SkipEmptyParts);
    QVector<int> numbers;

    for (const QString& numberString : numberStrings) {
        bool ok;
        int number = numberString.toInt(&ok);
        if (ok) {
            numbers.append(number);
        }
    }


    auto startTime = std::chrono::high_resolution_clock::now();


    bool found = false;
    int index = -1;

    for (int i = 0; i < numbers.size(); ++i) {
        if (numbers[i] == numberToSearch) {
            found = true;
            index = i;
            break;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    QString outputString;
    if (found) {
        outputString = "Number " + QString::number(numberToSearch) + " found at index " + QString::number(index) + "\n";
    } else {
        outputString = "Number " + QString::number(numberToSearch) + " not found\n";
    }

    outputString += "Elapsed time: " + QString::number(duration) + " nanoseconds";


    ui->plainTextEdit->appendPlainText(outputString);
    }
    if(bs==true){
        QString numberToSearchStr = ui->lineEdit_2->text();
        bool ok;
        int numberToSearch = numberToSearchStr.toInt(&ok);

        if (!ok) {

            return;
        }

        QString numbersText = ui->plainTextEdit->toPlainText();
        QStringList numberStrings = numbersText.split("\n", Qt::SkipEmptyParts);
        QVector<int> numbers;

        for (const QString& numberString : numberStrings) {
            bool ok;
            int number = numberString.toInt(&ok);
            if (ok) {
                numbers.append(number);
            }
        }

        auto startTime = std::chrono::high_resolution_clock::now();

        int index = binarySearch(numbers, numberToSearch);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

        QString outputString;
        if (index != -1) {
            outputString = "Number " + QString::number(numberToSearch) + " found at index " + QString::number(index) + "\n";
        } else {
            outputString = "Number " + QString::number(numberToSearch) + " not found\n";
        }

        outputString += "Elapsed time: " + QString::number(duration) + " nanoseconds";


        ui->plainTextEdit->appendPlainText(outputString);
    }
}

void MainWindow::on_NormalSearch_clicked()
{
    bs=false;
    ns=true;
    ui->searchMethod->setText("Normal Search");
}


void MainWindow::on_BinarySearch_clicked()
{
    bs=true;
    ns=false;
    ui->searchMethod->setText("Binary Search");
}


void MainWindow::on_stlSort_clicked()
{
    QString numbersText = ui->plainTextEdit->toPlainText();
       QStringList numberStrings = numbersText.split("\n", Qt::SkipEmptyParts);
       QVector<int> numbers;

       for (const QString& numberString : numberStrings) {
           bool ok;
           int number = numberString.toInt(&ok);
           if (ok) {
               numbers.append(number);
           }
       }

       std::sort(numbers.begin(), numbers.end());

       QString outputString = "Sorted numbers:\n";
       for (int number : numbers) {
           outputString += QString::number(number) + "\n";
       }

       ui->plainTextEdit->setPlainText(outputString);
}

