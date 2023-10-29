#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QProgressBar>
#include <QButtonGroup>
#include <QString>
#include <QOverload>
#include <QAbstractButton>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout;

    QLineEdit *lineEdit1;
    QDoubleSpinBox *doubleSpinBox;
    QLineEdit *lineEdit2;
    QComboBox *comboBox1;
    QComboBox *comboBox2;
    QString currentText;
    QPushButton *convertButton;
    QString input;
    QButtonGroup *buttonGroup1;
    QRadioButton *radioButton1;
    QRadioButton *radioButton2;
    QRadioButton *radioButton3;
    QButtonGroup *buttonGroup2;
    QRadioButton *radioButton4;
    QRadioButton *radioButton5;
    QRadioButton *radioButton6;
    QSpinBox *SpinBox;
    QFont spinBoxFont;
    QCheckBox *checkBox;
    QPushButton *clearButton;

    void initializeWidgets();
    void setupPositions();
    void setupConnections();
};

#endif // WIDGET_H
