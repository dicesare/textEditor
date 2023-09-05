#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
            ui->windowDisplayText->setText(m_editorViewModel.getFileContent());
        }
        else
        {
            QMessageBox::critical(this, "Error", "Failed to open the file.");
        }
    }
}

void MainWindow::saveFile()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", QString(), "All Files (*)");
    if (!filePath.isEmpty())
    {
        QString content = ui->windowDisplayText->toPlainText(); // Récupérer le contenu du QTextEdit
        m_editorViewModel.setFileContent(content); // Mettre à jour le contenu du fichier
        if (m_editorViewModel.saveFile(filePath))
        {
            QMessageBox::information(this, "Success", "File saved successfully.");
        }
        else
        {
            QMessageBox::critical(this, "Error", "Failed to save the file.");
        }
    }
}
