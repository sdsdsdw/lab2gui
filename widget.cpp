#include "widget.h"
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

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    horizontalLayout = new QHBoxLayout();

    initializeWidgets();
    setupPositions();
    setupConnections();
}

void Widget::initializeWidgets()
{
    lineEdit1 = new QLineEdit(this);
    doubleSpinBox = new QDoubleSpinBox(this);
    lineEdit2 = new QLineEdit(this);
    comboBox1 = new QComboBox(this);
    comboBox2 = new QComboBox(this);
    convertButton = new QPushButton("Convert", this);
    buttonGroup1 = new QButtonGroup(this);
    radioButton1 = new QRadioButton(this);
    radioButton2 = new QRadioButton(this);
    radioButton3 = new QRadioButton(this);
    buttonGroup2 = new QButtonGroup(this);
    radioButton4 = new QRadioButton(this);
    radioButton5 = new QRadioButton(this);
    radioButton6 = new QRadioButton(this);
    SpinBox = new QSpinBox(this);
    checkBox = new QCheckBox(this);
    clearButton = new QPushButton("Clear", this);
}

void Widget::setupPositions()
{
    lineEdit1->move(50, 100);
    lineEdit1->resize(100, 30);

    lineEdit2->move(400, 100);
    lineEdit2->resize(100, 30);

    doubleSpinBox->move(270, 100);
    doubleSpinBox->resize(50, 30);

    comboBox1->move(150, 100);
    comboBox1->resize(50, 30);
    comboBox1->addItem("UAH");
    comboBox1->addItem("USD");

    comboBox2->move(500, 100);
    comboBox2->resize(50, 30);
    comboBox2->addItem("UAH");
    comboBox2->addItem("USD");
    comboBox2->setCurrentText("USD");

    radioButton1->move(50, 270);
    radioButton2->move(50, 300);
    radioButton3->move(50, 330);
    radioButton4->move(450, 270);
    radioButton5->move(450, 300);
    radioButton6->move(450, 330);

    checkBox->move(50, 50);
    checkBox->setText("Invert");

    radioButton1->move(50, 270);
    radioButton1->setText("black");
    radioButton1->setChecked(true);
    buttonGroup1->addButton(radioButton1);
    radioButton1->show();

    radioButton2->move(50, 300);
    radioButton2->setText("white");
    buttonGroup1->addButton(radioButton2);
    radioButton2->show();

    radioButton3->move(50, 330);
    radioButton3->setText("blue");
    buttonGroup1->addButton(radioButton3);
    radioButton3->show();

    radioButton4->move(450, 270);
    radioButton4->setText("white");
    radioButton4->setChecked(true);
    buttonGroup2->addButton(radioButton4);
    radioButton4->show();

    radioButton5->move(450, 300);
    radioButton5->setText("gray");
    buttonGroup2->addButton(radioButton5);
    radioButton5->show();

    radioButton6->move(450, 330);
    radioButton6->setText("green");
    buttonGroup2->addButton(radioButton6);
    radioButton6->show();

    horizontalLayout->addWidget(clearButton);
    horizontalLayout->addWidget(convertButton);
    horizontalLayout->addWidget(SpinBox);

    SpinBox->setFixedSize(100, 30);
    convertButton->setFixedSize(100, 30);
    clearButton->setFixedSize(100, 30);

    mainLayout->insertLayout(0, horizontalLayout);
}

void Widget::setupConnections()
{
    QObject::connect(comboBox1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index)
    {
        QString currentText = comboBox1->currentText();

        if (currentText == "UAH")
        {
            comboBox2->setCurrentText("USD");
        }
        else if (currentText == "USD")
        {
            comboBox2->setCurrentText("UAH");
        }
    });

    QObject::connect(convertButton, &QPushButton::clicked, this, [=]()
    {
        double exchangeRate = doubleSpinBox->value();
        QString input = lineEdit1->text();

        if (comboBox1->currentText() == "UAH" && comboBox2->currentText() == "USD")
        {
            double result = input.toDouble() / exchangeRate;
            lineEdit2->setText(QString::number(result));
        }
        else if (comboBox1->currentText() == "USD" && comboBox2->currentText() == "UAH")
        {
            double result = input.toDouble() * exchangeRate;
            lineEdit2->setText(QString::number(result));
        }
    });

    QObject::connect(buttonGroup2, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, [=](QAbstractButton *button)
    {
        QPalette pal = qApp->palette();

        if (button == radioButton4)
        {
            pal.setColor(QPalette::Window, Qt::white);
        }
        else if (button == radioButton5)
        {
            pal.setColor(QPalette::Window, Qt::gray);
        }
        else if (button == radioButton6)
        {
            pal.setColor(QPalette::Window, Qt::green);
        }
        qApp->setPalette(pal);
    });

    QObject::connect(SpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value)
    {
        spinBoxFont.setPointSize(9);
        int baseFontSize = 9;

        int fontSize = baseFontSize + value;
        QFont font = SpinBox->font();
        font.setPointSize(fontSize);

        lineEdit1->setFont(font);
        lineEdit2->setFont(font);
        doubleSpinBox->setFont(font);

        radioButton1->setFont(font);
        radioButton2->setFont(font);
        radioButton3->setFont(font);
        radioButton4->setFont(font);
        radioButton5->setFont(font);
        radioButton6->setFont(font);
    });
    SpinBox->setValue(0);

    QObject::connect(checkBox, &QCheckBox::stateChanged, this, [=](int state)
    {
        QPalette pal = qApp->palette();
        if (state == Qt::Checked)
        {
            radioButton2->setChecked(true);
            pal.setColor(QPalette::Window, Qt::black);

            checkBox->setStyleSheet("color: white;");
            radioButton1->setStyleSheet("color: white;");
            radioButton2->setStyleSheet("color: white;");
            radioButton3->setStyleSheet("color: white;");
            radioButton4->setStyleSheet("color: white;");
            radioButton5->setStyleSheet("color: white;");
            radioButton6->setStyleSheet("color: white;");
        }
        else
        {
            radioButton1->setChecked(true);
            pal.setColor(QPalette::Window, Qt::white);

            checkBox->setStyleSheet("color: black;");
            radioButton1->setStyleSheet("color: black;");
            radioButton2->setStyleSheet("color: black;");
            radioButton3->setStyleSheet("color: black;");
            radioButton4->setStyleSheet("color: black;");
            radioButton5->setStyleSheet("color: black;");
            radioButton6->setStyleSheet("color: black;");

            if (radioButton5->isChecked() || radioButton6->isChecked())
            {
                radioButton4->setChecked(true);
            }
        }
        qApp->setPalette(pal);
    });

    QObject::connect(clearButton, &QPushButton::clicked, this, [=]()
    {
        lineEdit1->clear();
        lineEdit2->clear();
        checkBox->setChecked(false);

        radioButton1->setChecked(true);
        radioButton2->setChecked(false);
        radioButton3->setChecked(false);
        radioButton4->setChecked(true);
        radioButton5->setChecked(false);
        radioButton6->setChecked(false);

        SpinBox->setFont(spinBoxFont);
        lineEdit1->setFont(spinBoxFont);
        lineEdit2->setFont(spinBoxFont);

        radioButton1->setFont(spinBoxFont);
        radioButton2->setFont(spinBoxFont);
        radioButton3->setFont(spinBoxFont);
        radioButton4->setFont(spinBoxFont);
        radioButton5->setFont(spinBoxFont);
        radioButton6->setFont(spinBoxFont);

        doubleSpinBox->setFont(spinBoxFont);
        SpinBox->setValue(0);
        doubleSpinBox->setValue(0);

        lineEdit1->setStyleSheet("color: black;");
        lineEdit2->setStyleSheet("color: black;");

        radioButton1->setStyleSheet("color: black;");
        radioButton2->setStyleSheet("color: black;");
        radioButton3->setStyleSheet("color: black;");
        radioButton4->setStyleSheet("color: black;");
        radioButton5->setStyleSheet("color: black;");
        radioButton6->setStyleSheet("color: black;");

        doubleSpinBox->setStyleSheet("color: black;");
        SpinBox->setStyleSheet("color: black;");
        convertButton->setStyleSheet("color: black;");
        checkBox->setStyleSheet("color: black;");
        comboBox1->setStyleSheet("color: black;");
        comboBox2->setStyleSheet("color: black;");
        clearButton->setStyleSheet("color: black;");

        QPalette pal = qApp->palette();
        pal.setColor(QPalette::Window, Qt::white);
        qApp->setPalette(pal);
    });

    QObject::connect(buttonGroup1, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, [=](QAbstractButton *button)
    {
        if (button == radioButton1)
        {
            lineEdit1->setStyleSheet("color: black;");
            lineEdit2->setStyleSheet("color: black;");

            radioButton1->setStyleSheet("color: black;");
            radioButton2->setStyleSheet("color: black;");
            radioButton3->setStyleSheet("color: black;");
            radioButton4->setStyleSheet("color: black;");
            radioButton5->setStyleSheet("color: black;");
            radioButton6->setStyleSheet("color: black;");

            doubleSpinBox->setStyleSheet("color: black;");
            SpinBox->setStyleSheet("color: black;");
            convertButton->setStyleSheet("color: black;");
            checkBox->setStyleSheet("color: black;");
            comboBox1->setStyleSheet("color: black;");
            comboBox2->setStyleSheet("color: black;");
            clearButton->setStyleSheet("color: black;");
        }
        else if (button == radioButton2)
        {
            checkBox->setStyleSheet("color: white;");
            radioButton1->setStyleSheet("color: white;");
            radioButton2->setStyleSheet("color: white;");
            radioButton3->setStyleSheet("color: white;");
            radioButton4->setStyleSheet("color: white;");
            radioButton5->setStyleSheet("color: white;");
            radioButton6->setStyleSheet("color: white;");
        }
        else if (button == radioButton3)
        {
            lineEdit1->setStyleSheet("color: blue;");
            lineEdit2->setStyleSheet("color: blue;");

            radioButton1->setStyleSheet("color: blue;");
            radioButton2->setStyleSheet("color: blue;");
            radioButton3->setStyleSheet("color: blue;");
            radioButton4->setStyleSheet("color: blue;");
            radioButton5->setStyleSheet("color: blue;");
            radioButton6->setStyleSheet("color: blue;");

            doubleSpinBox->setStyleSheet("color: blue;");
            SpinBox->setStyleSheet("color: blue;");
            convertButton->setStyleSheet("color: blue;");
            checkBox->setStyleSheet("color: blue;");
            comboBox1->setStyleSheet("color: blue;");
            comboBox2->setStyleSheet("color: blue;");
            clearButton->setStyleSheet("color: blue;");
        }
    });
}

Widget::~Widget() {}
