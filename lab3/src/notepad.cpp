#include "notepad.h"

Notepad::Notepad(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Notepad");
    resize(800, 600);

    createMenus();
    createStatusBar();

    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    createTab();

    fileDock = new QDockWidget("File Commands", this);
    fileDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::TopDockWidgetArea, fileDock);

    editingDock = new QDockWidget("Editing Commands", this);
    editingDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::LeftDockWidgetArea, editingDock);

    tabifyDockWidget(fileDock, editingDock);

    createMenusFiles(fileDock);
    createToolbar(editingDock);
}

void Notepad::createMenus()
{
    createFileMenu();
    createEditingMenu();
    createHelpMenu();
}

void Notepad::createMenusFiles(QDockWidget *fileDock)
{
    QToolBar *firstToolBar = new QToolBar(" ", this);
    createFileToolbar(firstToolBar);
    fileDock->setWidget(firstToolBar);
}

void Notepad::createToolbar(QDockWidget *editingDock)
{
    QToolBar *secondToolBar = new QToolBar(" ", this);
    createEditingToolbar(secondToolBar);
    editingDock->setWidget(secondToolBar);
}

void Notepad::createFileMenu()
{
    QMenu *fileMenu = menuBar()->addMenu("File");
    createFileAction("New", &Notepad::newFile, fileMenu);
    createFileAction("Open", &Notepad::openFile, fileMenu);
    createFileAction("Save", &Notepad::saveFile, fileMenu);
    createFileAction("Save As", &Notepad::saveFileAs, fileMenu);
    createFileAction("Close App", &Notepad::closeApp, fileMenu);
}

void Notepad::createEditingMenu()
{
    QMenu *editingMenu = menuBar()->addMenu("Editing");
    createEditAction("Clear Text Field", &Notepad::clearText, editingMenu);
    createEditAction("To Uppercase", &Notepad::toUppercase, editingMenu);
    createEditAction("To Lowercase", &Notepad::toLowercase, editingMenu);
    createEditAction("Increase Font", &Notepad::increaseFont, editingMenu);
    createEditAction("Decrease Font", &Notepad::decreaseFont, editingMenu);
    createEditAction("Remove Double Spaces", &Notepad::removeDoubleSpaces, editingMenu);
}

void Notepad::createHelpMenu()
{
    QMenu *helpMenu = menuBar()->addMenu("Help");
    createHelpAction("About App", &Notepad::showAboutDialog, helpMenu);
    createHelpAction("Help", &Notepad::showHelp, helpMenu);
}

void Notepad::createFileToolbar(QToolBar *firstToolBar)
{
    createToolbarAction("New", &Notepad::newFile, firstToolBar);
    createToolbarAction("Open", &Notepad::openFile, firstToolBar);
    createToolbarAction("Save", &Notepad::saveFile, firstToolBar);
    createToolbarAction("Save As", &Notepad::saveFileAs, firstToolBar);
    createToolbarAction("Close App", &Notepad::closeApp, firstToolBar);
}

void Notepad::createEditingToolbar(QToolBar *secondToolBar)
{
    createToolbarAction("Clear Text Field", &Notepad::clearText, secondToolBar);
    createToolbarAction("To Uppercase", &Notepad::toUppercase, secondToolBar);
    createToolbarAction("To Lowercase", &Notepad::toLowercase, secondToolBar);

    QWidgetAction *spinBoxAction = new QWidgetAction(this);
    QSpinBox *spinBox = new QSpinBox(this);
    spinBox->setRange(0, 100);
    spinBox->setValue(11);
    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(spinBoxSlot(int)));
    spinBoxAction->setDefaultWidget(spinBox);
    secondToolBar->addAction(spinBoxAction);

    createToolbarAction("Remove Double Spaces", &Notepad::removeDoubleSpaces, secondToolBar);
}

void Notepad::createFileAction(const QString &text, void (Notepad::*slot)(), QMenu *menu)
{
    QAction *action = new QAction(text, this);
    connect(action, &QAction::triggered, this, slot);
    menu->addAction(action);
}

void Notepad::createEditAction(const QString &text, void (Notepad::*slot)(), QMenu *menu)
{
    QAction *action = new QAction(text, this);
    connect(action, &QAction::triggered, this, slot);
    menu->addAction(action);
}

void Notepad::createHelpAction(const QString &text, void (Notepad::*slot)(), QMenu *menu)
{
    QAction *action = new QAction(text, this);
    connect(action, &QAction::triggered, this, slot);
    menu->addAction(action);
}

void Notepad::createToolbarAction(const QString &text, void (Notepad::*slot)(), QToolBar *toolbar)
{
    QAction *action = new QAction(text, this);
    connect(action, &QAction::triggered, this, slot);
    toolbar->addAction(action);
}

void Notepad::clearText()
{
    auto currentTextEdit = getCurrentTextEdit();
    if (currentTextEdit)
    {
        currentTextEdit->clear();
        showNormalMessage("Text field cleared.");
    }
}

void Notepad::toUppercase()
{
    auto currentTextEdit = getCurrentTextEdit();
    if (currentTextEdit)
    {
        QString text = currentTextEdit->toPlainText();
        currentTextEdit->setPlainText(text.toUpper());
    }
}

void Notepad::toLowercase()
{
    auto currentTextEdit = getCurrentTextEdit();
    if (currentTextEdit)
    {
        QString text = currentTextEdit->toPlainText();
        currentTextEdit->setPlainText(text.toLower());
    }
}

void Notepad::increaseFont()
{
    auto currentTextEdit = getCurrentTextEdit();
    if (currentTextEdit)
    {
        QFont font = currentTextEdit->font();
        font.setPointSize(font.pointSize() + 1);
        currentTextEdit->setFont(font);
    }
}

void Notepad::decreaseFont()
{
    auto currentTextEdit = getCurrentTextEdit();
    if (currentTextEdit)
    {
        QFont font = currentTextEdit->font();
        font.setPointSize(font.pointSize() - 1);
        currentTextEdit->setFont(font);
    }
}

void Notepad::showAboutDialog()
{
    QMessageBox::about(this, "About Application", "Notepad Application v1.0");
}

void Notepad::showHelp()
{
    QMessageBox::about(this, "Help", "This is a simple Notepad application. You can use it to create and edit text documents.");
}

void Notepad::closeApp()
{
    if (QMessageBox::question(this, "Exit Dialog", "Do you really want to exit") == QMessageBox::StandardButton::Yes)
    {
        QCoreApplication::quit();
    }
}

void Notepad::spinBoxSlot(int value)
{
    auto currentTextEdit = getCurrentTextEdit();
    if (currentTextEdit)
    {
        QFont font = currentTextEdit->font();
        font.setPointSize(value);
        currentTextEdit->setFont(font);
    }
}

void Notepad::newFile()
{
    createTab();
}

void Notepad::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File");
    if (!filePath.isEmpty())
    {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            textEdit->setPlainText(in.readAll());
            file.close();
            currentFilePath = filePath;
            updateTabText(tabWidget->currentIndex(), currentFilePath);
        }
        else
        {
            QMessageBox::warning(this, "Error", "Could not open file");
        }
    }
}

void Notepad::saveFile()
{
    if (currentFilePath.isEmpty())
    {
        saveFileAs();
    }
    else
    {
        QFile file(currentFilePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
            updateTabText(tabWidget->currentIndex(), currentFilePath);
            showNormalMessage("File saved successfully.");
        }
        else
        {
            QMessageBox::warning(this, "Error", "Could not save file");
        }
    }
}

void Notepad::saveFileAs()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save File As", "", "Text Files (*.txt)");
    if (!filePath.isEmpty())
    {
        if (!filePath.endsWith(".txt", Qt::CaseInsensitive))
        {
            filePath += ".txt";
        }
        currentFilePath = filePath;
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
            updateTabText(tabWidget->currentIndex(), currentFilePath);
            showNormalMessage("File saved successfully.");
        }
        else
        {
            QMessageBox::warning(this, "Error", "Could not save file");
        }
    }
}

void Notepad::createStatusBar()
{
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    temporaryStatusLabel = new QLabel(this);
    normalStatusLabel = new QLabel(this);
    permanentStatusLabel = new QLabel(this);

    statusBar->addWidget(temporaryStatusLabel);
    statusBar->addWidget(normalStatusLabel, 1);
    statusBar->addPermanentWidget(permanentStatusLabel);

    temporaryStatusLabel->setText("");
    normalStatusLabel->setText("");
    permanentStatusLabel->setText("");
}

void Notepad::showTemporaryMessage(const QString &message, int timeout)
{
    statusBar->showMessage(message, timeout);
}

void Notepad::showNormalMessage(const QString &message)
{
    normalStatusLabel->setText(message);
}

void Notepad::showPermanentMessage(const QString &message)
{
    permanentStatusLabel->setText(message);
}

void Notepad::removeDoubleSpaces()
{
    auto currentTextEdit = getCurrentTextEdit();
    if (currentTextEdit)
    {
        QString text = currentTextEdit->toPlainText();
        QString cleanedText = text.simplified();
        currentTextEdit->setPlainText(cleanedText);
    }
}

void Notepad::createTab()
{
    textEdit = new QTextEdit(this);
    tabWidget->addTab(textEdit, "Untitled.txt");
    connect(textEdit->document(), &QTextDocument::contentsChanged, this, &Notepad::documentWasModified);
}

QTextEdit* Notepad::getCurrentTextEdit()
{
    int currentIndex = tabWidget->currentIndex();
    if (currentIndex != -1)
    {
        QWidget *currentWidget = tabWidget->widget(currentIndex);
        if (currentWidget)
        {
            QTextEdit *currentTextEdit = currentWidget->findChild<QTextEdit *>();
            return currentTextEdit;
        }
    }
    return nullptr;
}

QString Notepad::getCurrentTabFilePath()
{
    int currentIndex = tabWidget->currentIndex();
    if (currentIndex != -1)
    {
        return tabWidget->tabToolTip(currentIndex);
    }
    return QString();
}

void Notepad::updateTabText(int tabIndex, const QString &filePath)
{
    if (tabIndex >= 0 && tabIndex < tabWidget->count())
    {
        QString fileName = QFileInfo(filePath).fileName();
        tabWidget->setTabText(tabIndex, fileName);
        tabWidget->setTabToolTip(tabIndex, filePath);
    }
}

void Notepad::documentWasModified()
{
    int currentIndex = tabWidget->currentIndex();
    if (currentIndex != -1)
    {
        QString filePath = getCurrentTabFilePath();
        if (!filePath.isEmpty())
        {
            QString fileName = QFileInfo(filePath).fileName();
            tabWidget->setTabText(currentIndex, "* " + fileName);
        }
    }
}

Notepad::~Notepad()
{
    delete fileDock;
    delete editingDock;
    delete statusBar;
}
