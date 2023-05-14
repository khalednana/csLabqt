#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_GenerateDataset_clicked();

    void on_mergeSort_clicked();

    void on_FindIt_clicked();

    void on_NormalSearch_clicked();

    void on_BinarySearch_clicked();

    void on_stlSort_clicked();

private:
    Ui::MainWindow *ui;
    bool bs;
    bool ns;
};
#endif // MAINWINDOW_H
