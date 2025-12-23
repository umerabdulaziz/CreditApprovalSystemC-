#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onAddApplicant();


private:
    // Widgets
    QLineEdit *nameEdit;
    QSpinBox *ageSpin;
    QDoubleSpinBox *salarySpin;
    QSpinBox *creditSpin;
    QDoubleSpinBox *loanSpin;
    QComboBox *employmentBox;
    QSpinBox *dependentsSpin;
    QComboBox *educationBox;
    QSpinBox *numHousesSpin;
    QDoubleSpinBox *avgHouseSizeSpin;
    QSpinBox *numCarsSpin;
    QDoubleSpinBox *totalCarsWorthSpin;
    QComboBox *maritalBox;
    QSpinBox *activeLoansSpin;
    QSpinBox *latePaymentsSpin;
    QComboBox *criminalBox;
    QDoubleSpinBox *savingsSpin;
    QDoubleSpinBox *spendingPerMonth;

    QTableWidget *table;

    // Helper functions
    QString getBackendPath();
    void runBackend();
};

#endif // MAINWINDOW_H
