#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_initialTabWidget(true),
    m_lastFoundCursor(),
    m_settings(new QSettings("Antony Coco", "XEditor", this)) // Initialisation de QSettings

{
    ui->setupUi(this);
    // Initialize the CustomTextEdit instance and connect signals
    CustomTextEdit *initialTextEdit = new CustomTextEdit(this);
    // Create the initial tab and set up the initial state of the tab widget
    ui->tabWidgetEditor->removeTab(0);
    ui->tabWidgetEditor->addTab(initialTextEdit, "tab1");
    ui->tabWidgetEditor->setTabToolTip(0, mCurrentDirectory);

    connect(initialTextEdit, &CustomTextEdit::textModified, ui->tabWidgetEditor, &TabWidgetEditor::handleTextModified);
    connect(initialTextEdit, &CustomTextEdit::cursorPositionChanged, this, [this, initialTextEdit]() {
        emit ui->tabWidgetEditor->cursorPositionChangedInEditor(initialTextEdit);
    });
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::onSaveAsTriggered);

    connect(ui->tabWidgetEditor, &QTabWidget::tabCloseRequested, ui->tabWidgetEditor, &TabWidgetEditor::closeTab);
    connect(ui->tabWidgetEditor, &TabWidgetEditor::cursorPositionChangedInEditor, this, &MainWindow::updateCursorPosition);
    connect(ui->pushButtonFind, &QPushButton::clicked, this, &MainWindow::pushButtonFind_clicked);
    connect(ui->pushButtonPrevious, &QPushButton::clicked, this, &MainWindow::pushButtonPrevious_clicked);
    connect(ui->pushButtonNext, &QPushButton::clicked, this, &MainWindow::pushButtonNext_clicked);
    connect(ui->pushButtonReplace, &QPushButton::clicked, this, &MainWindow::pushButtonReplace_clicked);
    connect(ui->pushButtonRecentFiles, &QPushButton::clicked, this, &MainWindow::openSelectedFileFromButton);

    loadRecentFiles(); // Download the recent files list

}

MainWindow::~MainWindow()
{
    delete ui;
}
// Update the cursor position display
void MainWindow::updateCursorPosition(CustomTextEdit *editor)
{
    if (editor)
    {
        QTextCursor cursor = editor->textCursor();
        int line = cursor.blockNumber() + 1; // Add 1 to the line number because it starts at 0
        int col = cursor.columnNumber() + 1; // Add 1 to the column number because it starts at 0
        ui->labelTextCursor->setText(QString("Line: %1, Col: %2").arg(line).arg(col));
    }
    else
    {
        qDebug() << "textEditor is nullptr";
    }

}

// Load the recent files from settings and update the list widget
void MainWindow::loadRecentFiles()
{
    ui->listWidgetRecentFiles->clear(); // Clear the list widget
    m_recentFiles = m_settings.value("recentFiles").toStringList(); // Get the recent files from settings
    ui->listWidgetRecentFiles->addItems(m_recentFiles); // Add the recent files to the list widget  

    // Connect the itemClicked signal to the openRecentFile slot
    connect(ui->listWidgetRecentFiles, &QListWidget::itemClicked, [this](QListWidgetItem *item) {
        openRecentFile(item->text());
    });
}
// Open the file selected from the recent files list
void MainWindow::openSelectedFile(QListWidgetItem* item)
{   
    QString filePath = item->text(); // Get the file path from the item
    QString content;
    if(m_controllerEditor.openFile(filePath))
    {
        content = m_controllerEditor.getFileContent(); 
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        ui->tabWidgetEditor->addTabWithContent(content, fileName); // Add the tab with the file content
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to open the file.");
    }
}   

// Open the file selected from the recent files list
void MainWindow::openRecentFile(const QString &filePath)
{
    if (!filePath.isEmpty())
    {
        if (m_controllerEditor.openFile(filePath))
        {
            // use QFileInfo to extract the file name
            QFileInfo fileInfo(filePath);
            mCurrentDirectory = fileInfo.absolutePath();
            QString fileName = fileInfo.fileName();

            ui->tabWidgetEditor->addTabWithContent(m_controllerEditor.getFileContent(), fileName); 
            ui->tabWidgetEditor->setTabToolTip(ui->tabWidgetEditor->count() - 1, filePath);

            m_recentFiles.removeAll(filePath);
            m_recentFiles.prepend(filePath);
            // Remove the last file path if the list size exceeds the maximum number of recent files
            while (m_recentFiles.size() > MaxRecentFiles)
                m_recentFiles.removeLast();
            // Save the list using QSettings
            m_settings.setValue("recentFiles", m_recentFiles);
        }
        else
        {
            QMessageBox::critical(this, "Error", "Failed to open the file.");
        }
    }
}

// Open the file selected from the recent files list
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
            // Use QFileInfo to extract the file name
            QFileInfo fileInfo(filePath);
            mCurrentDirectory = fileInfo.absolutePath();
            QString fileName = fileInfo.fileName();
            if (m_initialTabWidget)
            {
                ui->tabWidgetEditor->addTabWithContent(m_controllerEditor.getFileContent(), fileName); 
                ui->tabWidgetEditor->setTabToolTip(ui->tabWidgetEditor->count() - 1, filePath);
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

    // Save the list using QSettings
    m_settings.setValue("recentFiles", m_recentFiles);
}

void MainWindow::onSaveAsTriggered()
{
    m_actionSaveAsTriggered = true;
    saveFile(); // Call the saveFile slot  
}

void MainWindow::saveFile()
{
    if (m_actionSaveAsTriggered)
    {
        m_actionSaveAsTriggered = false; // Reset the flag
        m_shouldShowSaveDialog = true; // Set the flag to show the save dialog
    }
    
    int activeTabIndex = ui->tabWidgetEditor->currentIndex();
    if (activeTabIndex != -1)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit *>(ui->tabWidgetEditor->widget(activeTabIndex));
        if (textEdit)
        {
            QString content = textEdit->toPlainText();
            QString filePath = ui->tabWidgetEditor->tabToolTip(activeTabIndex);  // Use the tooltip of the tab as the file path
            if (filePath.isEmpty() || !QFileInfo(filePath).isFile() || m_shouldShowSaveDialog) // If the file path is empty or invalid, show the save dialog
            {
                filePath = QFileDialog::getSaveFileName(this, "Save File", mCurrentDirectory, "All Files (*)");
                if (filePath.isEmpty())
                {
                    return;
                }
                ui->tabWidgetEditor->setTabToolTip(activeTabIndex, filePath);
                // Update the tab text to reflect the new file name
                QFileInfo fileInfo(filePath);
                QString fileName = fileInfo.fileName();
                ui->tabWidgetEditor->setTabText(activeTabIndex, fileName);
            }
            if (m_controllerEditor.saveFile(filePath, content))
            {
                QFileInfo fileInfo(filePath);
                QString fileName = fileInfo.fileName();
                ui->tabWidgetEditor->setTabText(activeTabIndex, fileName); 
                ui->tabWidgetEditor->setCurrentTextEditModified(false);

                QMessageBox::information(this, "Success", "File saved successfully.");
            }
            else
            {
                QMessageBox::critical(this, "Error", "Failed to save the file.");
            }
        }
    }
}

// Compare this snippet from textEditor/src/view/mainwindow.cpp:
void MainWindow::pushButtonFind_clicked()
{
    CustomTextEdit *currentTextEdit = qobject_cast<CustomTextEdit*>(ui->tabWidgetEditor->currentWidget());

    if (!currentTextEdit) {
        qDebug() << "The active text editor is a null pointer.";
        return;
    }

    QString searchString = ui->lineEditResearch->text().trimmed();// Get the search string from the line edit
    bool caseSensitive = ui->checkBoxUppercase->isChecked();// Get the caseSensitive flag from the checkbox
    bool wholeWordsOnly = ui->checkBoxWordOnly->isChecked();// Get the wholeWordsOnly flag from the checkbox

    QTextDocument::FindFlags flags;
    // If the caseSensitive flag is set, add the QTextDocument::FindCaseSensitively flag
    if(caseSensitive) {
        flags |= QTextDocument::FindCaseSensitively;
    }
    // If the wholeWordsOnly flag is set, add the QTextDocument::FindWholeWords flag
    if(wholeWordsOnly) {
        flags |= QTextDocument::FindWholeWords;
    }

    QTextCursor cursor = currentTextEdit->textCursor();// Get the cursor from the current text editor

    QTextCursor found = currentTextEdit->document()->find(searchString, cursor, flags);// Find the search string
    // If the search string is not found, move the cursor to the beginning of the document and try again
    if(found.isNull()) {
        cursor.setPosition(0);
        found = currentTextEdit->document()->find(searchString, cursor, flags);
    }
    // If the search string is found, update the cursor
    if(!found.isNull()) {
        currentTextEdit->setTextCursor(found);
        m_lastFoundCursor = found; // Update m_lastFoundCursor
    }
}
// Compare this snippet from textEditor/src/view/mainwindow.cpp:
void MainWindow::pushButtonNext_clicked()
{
    pushButtonFind_clicked();// Call the pushButtonFind_clicked slot to find the next occurrence (RECURSIVE)
}

void MainWindow::pushButtonPrevious_clicked()
{
    CustomTextEdit *currentTextEdit = qobject_cast<CustomTextEdit*>(ui->tabWidgetEditor->currentWidget());

    if (!currentTextEdit) {
        qDebug() << "The active text editor is a null pointer.";
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
        // Move the cursor to the end of the document and try again
        cursor.movePosition(QTextCursor::End);
        found = currentTextEdit->document()->find(searchString, cursor, flags);
    }
    // If the search string is found, update the cursor
    if(!found.isNull()) {
        currentTextEdit->setTextCursor(found);
    }
}

// Compare this snippet from textEditor/src/view/mainwindow.cpp:
void MainWindow::pushButtonReplace_clicked()
{
    CustomTextEdit *currentTextEdit = qobject_cast<CustomTextEdit*>(ui->tabWidgetEditor->currentWidget());

    if (!currentTextEdit) {
        qDebug() << "The active text editor is a null pointer.";
        return;
    }

    if(m_lastFoundCursor.isNull() || m_lastFoundCursor.selectedText().isEmpty()) {
        qDebug() << "No text selected for replacement.";
        return;
    }

    QString replaceString = ui->lineEditReplace->text(); 

    m_lastFoundCursor.beginEditBlock();
    m_lastFoundCursor.removeSelectedText();
    m_lastFoundCursor.insertText(replaceString);
    m_lastFoundCursor.endEditBlock();

    currentTextEdit->setTextCursor(m_lastFoundCursor);
}
