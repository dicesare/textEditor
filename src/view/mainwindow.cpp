#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_initialTabWidget(true)
{
    ui->setupUi(this);
    // Connecter l'onglet initial
    CustomTextEdit *initialTextEdit = new CustomTextEdit(this);
    ui->tabWidgetEditor->removeTab(0);
    ui->tabWidgetEditor->addTab(initialTextEdit, "tab1");
    ui->tabWidgetEditor->setTabToolTip(0, mCurrentDirectory);
    connect(initialTextEdit, &CustomTextEdit::textModified, ui->tabWidgetEditor, &TabWidgetEditor::handleTextModified);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->tabWidgetEditor, &QTabWidget::tabCloseRequested, ui->tabWidgetEditor, &TabWidgetEditor::closeTab);
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
            if (m_initialTabWidget)
            {
                // Utilisation de votre méthode personnalisée pour ajouter un onglet
                ui->tabWidgetEditor->addTabWithContent(m_controllerEditor.getFileContent(), fileName);
                ui->tabWidgetEditor->setTabToolTip(ui->tabWidgetEditor->count() - 1, filePath);
                // Enlevez l'onglet initial
                ui->tabWidgetEditor->removeTab(0);
                m_initialTabWidget = false;
            }
            else
            {
                ui->tabWidgetEditor->addTabWithContent(m_controllerEditor.getFileContent(), fileName);
                ui->tabWidgetEditor->setTabToolTip(ui->tabWidgetEditor->count() - 1, filePath);
            }
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
    int activeTabIndex = ui->tabWidgetEditor->currentIndex();
    if (activeTabIndex != -1)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit *>(ui->tabWidgetEditor->widget(activeTabIndex));
        if (textEdit)
        {
            QString content = textEdit->toPlainText();
            QString filePath = ui->tabWidgetEditor->tabToolTip(activeTabIndex);  // Utilisez l'info-bulle comme chemin de fichier
            // Vérifier si le chemin du fichier est valide
            if (filePath.isEmpty() || !QFileInfo(filePath).isFile())
            {
                // Afficher une boîte de dialogue pour choisir où sauvegarder le fichier
                filePath = QFileDialog::getSaveFileName(this, "Save File", mCurrentDirectory, "All Files (*)");
                if (filePath.isEmpty())
                {
                    // L'utilisateur a annulé la boîte de dialogue de sauvegarde
                    return;
                }

                // Mettre à jour le chemin du fichier dans l'onglet
                ui->tabWidgetEditor->setTabToolTip(activeTabIndex, filePath);

                // Mettre à jour le texte de l'onglet pour refléter le nouveau nom du fichier
                QFileInfo fileInfo(filePath);
                QString fileName = fileInfo.fileName();
                ui->tabWidgetEditor->setTabText(activeTabIndex, fileName);
            }
            if (m_controllerEditor.saveFile(filePath, content))
            {
                QFileInfo fileInfo(filePath);
                QString fileName = fileInfo.fileName();  // Extrait le nom du fichier à partir du chemin d'accès complet
                ui->tabWidgetEditor->setTabText(activeTabIndex, fileName);  // Utilisez le nom du fichier pour le texte de l'onglet
                ui->tabWidgetEditor->setCurrentTextEditModified(false);      // (Je suppose que cette méthode définit l'état 'modifié' de l'onglet actuel)

                QMessageBox::information(this, "Success", "File saved successfully.");
            }
            else
            {
                QMessageBox::critical(this, "Error", "Failed to save the file.");
            }
        }
    }
}

