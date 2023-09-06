#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_tabWidget = new TabWidget(this); // Instancier le TabWidget
    setCentralWidget(m_tabWidget);     // Définir le TabWidget comme widget central

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QString(), "All Files (*)");
    if (!filePath.isEmpty())
    {
        if (m_editorViewModel.openFile(filePath))
        {
            // Utiliser QFileInfo pour extraire le nom du fichier
            QFileInfo fileInfo(filePath);
            QString fileName = fileInfo.fileName();

            m_tabWidget->addTabWithContent(m_editorViewModel.getFileContent(), fileName); // Ajouter un nouvel onglet avec le contenu et le nom du fichier
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
            QString filePath = m_tabWidget->tabText(activeTabIndex); // Utilisez tabText au lieu de tabToolTip
            qDebug() << filePath;
            if (m_editorViewModel.saveFile(filePath, content))
            {
                m_tabWidget->setTabText(activeTabIndex, filePath);
                QMessageBox::information(this, "Success", "File saved successfully.");
            }
            else
            {
                QMessageBox::critical(this, "Error", "Failed to save the file.");
            }
        }
    }
}
