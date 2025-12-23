#include "../Headers/mainwindow.h"
#include <QDir>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>
#include <QProcess>
#include <QCoreApplication>

// =================== Constructor ===================
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    setWindowTitle("Credit Approval - Data Entry (PKR)");
    resize(1000, 700);

    // ===== INPUT WIDGETS =====
    nameEdit = new QLineEdit;

    ageSpin = new QSpinBox; ageSpin->setRange(18, 100);
    salarySpin = new QDoubleSpinBox; salarySpin->setRange(0, 1e9); salarySpin->setDecimals(2);
    creditSpin = new QSpinBox; creditSpin->setRange(300, 900);
    loanSpin = new QDoubleSpinBox; loanSpin->setRange(0, 1e9); loanSpin->setDecimals(2);

    employmentBox = new QComboBox;
    employmentBox->addItems({"Private", "Government", "Self-Employed", "Unemployed", "Student"});

    dependentsSpin = new QSpinBox; dependentsSpin->setRange(0, 20);
    educationBox = new QComboBox;
    educationBox->addItems({"Matric", "Intermediate", "Bachelor", "Master", "PhD"});

    numHousesSpin = new QSpinBox; numHousesSpin->setRange(0, 50);
    avgHouseSizeSpin = new QDoubleSpinBox; avgHouseSizeSpin->setRange(0, 1e6); avgHouseSizeSpin->setDecimals(1);

    numCarsSpin = new QSpinBox; numCarsSpin->setRange(0, 50);
    totalCarsWorthSpin = new QDoubleSpinBox; totalCarsWorthSpin->setRange(0, 1e9); totalCarsWorthSpin->setDecimals(2);

    maritalBox = new QComboBox; maritalBox->addItems({"Single", "Married", "Divorced"});
    activeLoansSpin = new QSpinBox; activeLoansSpin->setRange(0, 50);
    latePaymentsSpin = new QSpinBox; latePaymentsSpin->setRange(0, 100);

    criminalBox = new QComboBox; criminalBox->addItems({"None", "Minor", "Serious"});

    savingsSpin = new QDoubleSpinBox; savingsSpin->setRange(0, 1e9); savingsSpin->setDecimals(2);
    spendingPerMonth = new QDoubleSpinBox; spendingPerMonth->setRange(0, 1e9); spendingPerMonth->setDecimals(2);

    // ===== FORM LAYOUT =====
    QGroupBox *formBox = new QGroupBox("Applicant Information");
    QGridLayout *g = new QGridLayout;
    int r = 0;

    g->addWidget(new QLabel("Name"), r, 0); g->addWidget(nameEdit, r, 1);
    g->addWidget(new QLabel("Age"), r, 2); g->addWidget(ageSpin, r, 3); r++;

    g->addWidget(new QLabel("Monthly Salary (PKR)"), r, 0); g->addWidget(salarySpin, r, 1);
    g->addWidget(new QLabel("Credit Score"), r, 2); g->addWidget(creditSpin, r, 3); r++;

    g->addWidget(new QLabel("Requested Loan (PKR)"), r, 0); g->addWidget(loanSpin, r, 1);
    g->addWidget(new QLabel("Employment Type"), r, 2); g->addWidget(employmentBox, r, 3); r++;

    g->addWidget(new QLabel("Dependents"), r, 0); g->addWidget(dependentsSpin, r, 1);
    g->addWidget(new QLabel("Education"), r, 2); g->addWidget(educationBox, r, 3); r++;

    g->addWidget(new QLabel("Number of Houses"), r, 0); g->addWidget(numHousesSpin, r, 1);
    g->addWidget(new QLabel("Average House Size"), r, 2); g->addWidget(avgHouseSizeSpin, r, 3); r++;

    g->addWidget(new QLabel("Number of Cars"), r, 0); g->addWidget(numCarsSpin, r, 1);
    g->addWidget(new QLabel("Total Cars Worth"), r, 2); g->addWidget(totalCarsWorthSpin, r, 3); r++;

    g->addWidget(new QLabel("Marital Status"), r, 0); g->addWidget(maritalBox, r, 1);
    g->addWidget(new QLabel("Active Loans"), r, 2); g->addWidget(activeLoansSpin, r, 3); r++;

    g->addWidget(new QLabel("Late Payments"), r, 0); g->addWidget(latePaymentsSpin, r, 1);
    g->addWidget(new QLabel("Criminal Record"), r, 2); g->addWidget(criminalBox, r, 3); r++;

    g->addWidget(new QLabel("Savings"), r, 0); g->addWidget(savingsSpin, r, 1);
    g->addWidget(new QLabel("Monthly Spending"), r, 2); g->addWidget(spendingPerMonth, r, 3); r++;

    formBox->setLayout(g);

    QPushButton *addBtn = new QPushButton("Add Applicant & Check Loan");
    connect(addBtn, SIGNAL(clicked()), this, SLOT(onAddApplicant()));

    table = new QTableWidget(0, 19);
    table->setHorizontalHeaderLabels({
        "Name","Age","Salary","Credit","Loan","Employment","Dependents","Education",
        "Houses","HouseSize","Cars","CarsWorth","Marital","ActiveLoans","LatePayments",
        "Criminal","Savings","Spending","Time"
    });

    QVBoxLayout *mainL = new QVBoxLayout;
    mainL->addWidget(formBox);
    mainL->addWidget(addBtn);
    mainL->addWidget(table);
    central->setLayout(mainL);

    // ===== CSV HEADER =====
    QFile file(getBackendPath() + "applicants.csv");
    if (!file.exists() && file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << table->horizontalHeaderItem(0)->text();
        for (int i = 1; i < table->columnCount(); i++)
            out << "," << table->horizontalHeaderItem(i)->text();
        out << "\n";
        file.close();
    }
}

// =================== BACKEND PATH ===================
QString MainWindow::getBackendPath()
{
    QDir dir(QCoreApplication::applicationDirPath());
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();
    dir.cd("backend");
    return dir.absolutePath() + "/";
}

// =================== ADD APPLICANT ===================
void MainWindow::onAddApplicant()
{
    if (nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Name required!");
        return;
    }

    QStringList row = {
        nameEdit->text(),
        QString::number(ageSpin->value()),
        QString::number(salarySpin->value()),
        QString::number(creditSpin->value()),
        QString::number(loanSpin->value()),
        employmentBox->currentText(),
        QString::number(dependentsSpin->value()),
        educationBox->currentText(),
        QString::number(numHousesSpin->value()),
        QString::number(avgHouseSizeSpin->value()),
        QString::number(numCarsSpin->value()),
        QString::number(totalCarsWorthSpin->value()),
        maritalBox->currentText(),
        QString::number(activeLoansSpin->value()),
        QString::number(latePaymentsSpin->value()),
        criminalBox->currentText(),
        QString::number(savingsSpin->value()),
        QString::number(spendingPerMonth->value()),
        QDateTime::currentDateTime().toString()
    };

    int r = table->rowCount();
    table->insertRow(r);
    for (int i = 0; i < row.size(); i++)
        table->setItem(r, i, new QTableWidgetItem(row[i]));

    QFile file(getBackendPath() + "applicants.csv");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << row.join(",") << "\n";
        file.close();
    }

    runBackend();
}

// =================== RUN BACKEND ===================
void MainWindow::runBackend()
{
    QString exe = getBackendPath() + "backend.exe";

    if (!QFile::exists(exe)) {
        QMessageBox::critical(this, "Error", "backend.exe not found!");
        return;
    }

    QProcess p;
    p.setProgram(exe);
    p.setWorkingDirectory(getBackendPath());
    p.start();
    p.waitForFinished();

    QMessageBox::information(this, "Result", p.readAllStandardOutput());
}
