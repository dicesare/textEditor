#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_initialTabWidget(true),
    m_lastFoundCursor(),
    m_settings(new QSettings("Antony Coco", "XEditor", this)) // Initialisation de QSettings

{
    ui->setupUi(this);
    // Connecter l'onglet initial
    CustomTextEdit *initialTextEdit = new CustomTextEdit(this);
    // Création de l'instance de TabWidgetEditor
    //TabWidgetEditor *tabWidgetEditorInstance = new TabWidgetEditor(this);
    loadRecentFiles();

    ui->tabWidgetEditor->removeTab(0);
    ui->tabWidgetEditor->addTab(initialTextEdit, "tab1");
    ui->tabWidgetEditor->setTabToolTip(0, mCurrentDirectory);

    connect(initialTextEdit, &CustomTextEdit::textModified, ui->tabWidgetEditor, &TabWidgetEditor::handleTextModified);
    connect(initialTextEdit, &CustomTextEdit::cursorPositionChanged, this, [this, initialTextEdit]() {
        emit ui->tabWidgetEditor->cursorPositionChangedInEditor(initialTextEdit);
    });
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->tabWidgetEditor, &QTabWidget::tabCloseRequested, ui->tabWidgetEditor, &TabWidgetEditor::closeTab);
    connect(ui->tabWidgetEditor, &TabWidgetEditor::cursorPositionChangedInEditor, this, &MainWindow::updateCursorPosition);
    connect(ui->pushButtonFind, &QPushButton::clicked, this, &MainWindow::pushButtonFind_clicked);
    connect(ui->pushButtonPrevious, &QPushButton::clicked, this, &MainWindow::pushButtonPrevious_clicked);
    connect(ui->pushButtonNext, &QPushButton::clicked, this, &MainWindow::pushButtonNext_clicked);
    connect(ui->pushButtonReplace, &QPushButton::clicked, this, &MainWindow::pushButtonReplace_clicked);
    connect(ui->pushButtonRecentFiles, &QPushButton::clicked, this, &MainWindow::openSelectedFileFromButton);


    //ui->labelTextCursor->setText("Test");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCursorPosition(CustomTextEdit *editor)
{
    if (editor)
    {
        QTextCursor cursor = editor->textCursor();
        int line = cursor.blockNumber() + 1; // Les numéros de ligne et de colonne sont basés sur 0
        int col = cursor.columnNumber() + 1;
        ui->labelTextCursor->setText(QString("Line: %1, Col: %2").arg(line).arg(col));
    }
    else
    {
        qDebug() << "textEditor is nullptr";
    }

}

void MainWindow::loadRecentFiles()
{
    ui->listWidgetRecentFiles->clear(); // Nettoyer les anciens éléments
    m_recentFiles = m_settings.value("recentFiles").toStringList(); // Charger la liste depuis QSettings
    ui->listWidgetRecentFiles->addItems(m_recentFiles); // Ajouter les éléments à listWidgetRecentFiles

    // Connecter le signal itemClicked au slot pour ouvrir le fichier
    connect(ui->listWidgetRecentFiles, &QListWidget::itemClicked, [this](QListWidgetItem *item) {
        openRecentFile(item->text());
    });
}

void MainWindow::openSelectedFile(QListWidgetItem* item)
{   
    QString filePath = item->text();
    QString content;
    if(m_controllerEditor.openFile(filePath))
    {
        content = m_controllerEditor.getFileContent();
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        ui->tabWidgetEditor->addTabWithContent(content, fileName);
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to open the file.");
    }
}   

// Lorsqu'un utilisateur clique sur un fichier récent
void MainWindow::openRecentFile(const QString &filePath)
{
    if (!filePath.isEmpty())
    {
        if (m_controllerEditor.openFile(filePath))
        {
            // Utiliser QFileInfo pour extraire le nom du fichier
            QFileInfo fileInfo(filePath);
            mCurrentDirectory = fileInfo.absolutePath();
            QString fileName = fileInfo.fileName();

            ui->tabWidgetEditor->addTabWithContent(m_controllerEditor.getFileContent(), fileName);
            ui->tabWidgetEditor->setTabToolTip(ui->tabWidgetEditor->count() - 1, filePath);

            // Mettre à jour la liste des fichiers récents
            m_recentFiles.removeAll(filePath);
            m_recentFiles.prepend(filePath);
            while (m_recentFiles.size() > MaxRecentFiles)
                m_recentFiles.removeLast();

            // Sauvegarder la liste en utilisant QSettings
            m_settings.setValue("recentFiles", m_recentFiles);
        }
        else
        {
            QMessageBox::critical(this, "Error", "Failed to open the file.");
        }
    }
}

void MainWindow::openSelectedFileFromButton()
{
    QListWidgetItem *selectedItem = ui->listWidgetRecentFiles->currentItem();
    if (selectedItem) {
        openSelectedFile(selectedItem);
    }
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
    m_recentFiles.removeAll(filePath);
    m_recentFiles.prepend(filePath);
    while (m_recentFiles.size() > MaxRecentFiles)
        m_recentFiles.removeLast();

    // Sauvegarder la liste en utilisant QSettings
    m_settings.setValue("recentFiles", m_recentFiles);
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


void MainWindow::pushButtonFind_clicked()
{
    CustomTextEdit *currentTextEdit = qobject_cast<CustomTextEdit*>(ui->tabWidgetEditor->currentWidget());

    if (!currentTextEdit) {
        qDebug() << "L'éditeur de texte actif est un pointeur nul.";
        return;
    }

    QString searchString = ui->lineEditResearch->text().trimmed();
    bool caseSensitive = ui->checkBoxUppercase->isChecked();
    bool wholeWordsOnly = ui->checkBoxWordOnly->isChecked();

    QTextDocument::FindFlags flags;

    if(caseSensitive) {
        flags |= QTextDocument::FindCaseSensitively;
    }

    if(wholeWordsOnly) {
        flags |= QTextDocument::FindWholeWords;
    }

    QTextCursor cursor = currentTextEdit->textCursor();

    QTextCursor found = currentTextEdit->document()->find(searchString, cursor, flags);

    if(found.isNull()) {
        cursor.setPosition(0);
        found = currentTextEdit->document()->find(searchString, cursor, flags);
    }

    if(!found.isNull()) {
        currentTextEdit->setTextCursor(found);
        m_lastFoundCursor = found; // Update m_lastFoundCursor
    }
}

void MainWindow::pushButtonNext_clicked()
{
    pushButtonFind_clicked();
}

void MainWindow::pushButtonPrevious_clicked()
{
    CustomTextEdit *currentTextEdit = qobject_cast<CustomTextEdit*>(ui->tabWidgetEditor->currentWidget());

    if (!currentTextEdit) {
        qDebug() << "L'éditeur de texte actif est un pointeur nul.";
        return;
    }

    QString searchString = ui->lineEditResearch->text();
    bool caseSensitive = ui->checkBoxUppercase->isChecked();
    bool wholeWordsOnly = ui->checkBoxWordOnly->isChecked();

    QTextDocument::FindFlags flags = QTextDocument::FindBackward;

    if (caseSensitive) {
        flags |= QTextDocument::FindCaseSensitively;
    }

    if (wholeWordsOnly) {
        flags |= QTextDocument::FindWholeWords;
    }

    QTextCursor cursor = currentTextEdit->textCursor();

    QTextCursor found = currentTextEdit->document()->find(searchString, cursor, flags);

    if(found.isNull()) {
        // Déplacer le curseur à la fin du document et essayer à nouveau
        cursor.movePosition(QTextCursor::End);
        found = currentTextEdit->document()->find(searchString, cursor, flags);
    }

    if(!found.isNull()) {
        currentTextEdit->setTextCursor(found);
    }
}


void MainWindow::pushButtonReplace_clicked()
{
    CustomTextEdit *currentTextEdit = qobject_cast<CustomTextEdit*>(ui->tabWidgetEditor->currentWidget());

    if (!currentTextEdit) {
        qDebug() << "L'éditeur de texte actif est un pointeur nul.";
        return;
    }

    if(m_lastFoundCursor.isNull() || m_lastFoundCursor.selectedText().isEmpty()) {
        qDebug() << "Aucun texte sélectionné pour le remplacement.";
        return;
    }

    QString replaceString = ui->lineEditReplace->text(); 

    m_lastFoundCursor.beginEditBlock();
    m_lastFoundCursor.removeSelectedText();
    m_lastFoundCursor.insertText(replaceString);
    m_lastFoundCursor.endEditBlock();

    currentTextEdit->setTextCursor(m_lastFoundCursor);
}
