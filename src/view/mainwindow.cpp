#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_tabWidget = new TabWidget(this); // Instancier le TabWidget
    setCentralWidget(m_tabWidget);     // Définir le TabWidget comme widget central

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->tabWidgetEditor, &QTabWidget::tabCloseRequested, m_tabWidget, &TabWidget::closeTab);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", mCurrentDirectory, "All Files (*)");
    if (!filePath.isEmpty())
    {
        if (m_controllerEditor.openFile(filePath))
        {
            // Utiliser QFileInfo pour extraire le nom du fichier
            QFileInfo fileInfo(filePath);
            mCurrentDirectory = fileInfo.absolutePath();
            QString fileName = fileInfo.fileName();

            m_tabWidget->addTabWithContent(m_controllerEditor.getFileContent(), fileName); // Ajouter un nouvel onglet avec le contenu et le nom du fichier
            m_tabWidget->setTabModified(m_tabWidget->count() - 1, false);                 // Initialiser l'état modifié à false
        }
        else
        {
            QMessageBox::critical(this, "Error", "Failed to open the file.");
        }
    }
}

void MainWindow::saveFile()
{
    // Récupérer l'index de l'onglet actif dans le TabWidget
    int activeTabIndex = m_tabWidget->currentIndex();
    if (activeTabIndex != -1)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit *>(m_tabWidget->widget(activeTabIndex));
        if (textEdit)
        {
            QString content = textEdit->toPlainText();
            QString filePath = mCurrentDirectory + "/" + m_tabWidget->tabToolTip(activeTabIndex);
            if (m_controllerEditor.saveFile(filePath, content))
            {
                m_tabWidget->setTabText(activeTabIndex, m_tabWidget->tabToolTip(activeTabIndex));
                QMessageBox::information(this, "Success", "File saved successfully.");
            }
            else
            {
                QMessageBox::critical(this, "Error", "Failed to save the file.");
            }
        }
    }
}