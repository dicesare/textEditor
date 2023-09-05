#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    // connect(m_editorViewModel, &EditorViewModel::fileContentChanged, this, &MainWindow::updateFileContent);

    // Reste du code...
}

void MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QString(), "Text Files (*.txt);;All Files (*)");
    if (!filePath.isEmpty())
    {
        if (!m_editorViewModel.openFile(filePath))
        {
            QMessageBox::critical(this, "Error", "Failed to open the file.");
        }
    }
}

void MainWindow::updateFileContent(const QString &content)
{
    ui->windowDisplayText->setPlainText(content);
}

MainWindow::~MainWindow()
{
    delete ui;
}
