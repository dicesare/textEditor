// tabwidget.cpp
#include "tabwidget.h"

TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent)
{
    connect(this, &QTabWidget::tabCloseRequested, this, &TabWidget::closeTab);
}

void TabWidget::addTabWithContent(const QString &content, const QString &filePath)
{
    CustomTextEdit *textEditor = new CustomTextEdit(this);
    textEditor->setText(content);

    int newIndex = addTab(textEditor, filePath);
    // Activer l'option "tabsClosable" pour cet onglet
    setTabsClosable(true);
    // Définir le tooltip de l'onglet sur le chemin du fichier
    setTabToolTip(newIndex, filePath);
    // Définir le texte de l'onglet sur le nom du fichier
    setCurrentIndex(newIndex);
    m_currentTextEdit = textEditor;

    // Connectez le signal textModified au slot handleTextModified
    connect(textEditor, &CustomTextEdit::textModified, this, &TabWidget::handleTextModified);

    // Initialiser l'état modifié à false pour le nouvel onglet
    m_modifiedTabs.append(false);
}

void TabWidget::closeTab(int index)
{
    if (index >= 0 && index < count())
    {
        // Récupérer le chemin du fichier à partir du tooltip de l'onglet
        QString filePath = mCurrentDirectory + "/" + tabToolTip(index);
        // Demander une confirmation à l'utilisateur
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous fermer cet onglet ?",
                                             QMessageBox::Yes | QMessageBox::No);

        // Si l'utilisateur confirme, fermer l'onglet
        if (confirmation == QMessageBox::Yes)
        {
            CustomTextEdit *textTabEdit = qobject_cast<CustomTextEdit *>(widget(index));
            // Si l'onglet actif est modifié, demandez à l'utilisateur s'il veut sauvegarder les modifications
            if (textTabEdit && textTabEdit->isTextChanged())
            {
                QTextEdit *textEditor = qobject_cast<QTextEdit *>(widget(index));
                QString content = textEditor->toPlainText();
                QMessageBox::StandardButton saveConfirmation;
                saveConfirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous sauvegarder les modifications ?",
                                                         QMessageBox::Yes | QMessageBox::No);
                // Utilisez mCurrentDirectory comme emplacement par défaut pour l'enregistrement
                if (saveConfirmation == QMessageBox::Yes)
                {
                    // Sauvegarder le fichier
                    if (!m_controllerEditor.saveFile(filePath, content))
                    {
                        QMessageBox::critical(this, "Erreur", "Échec de la sauvegarde du fichier.");
                        return; // Ne pas fermer l'onglet si la sauvegarde échoue.
                    }
                }
            }

            QWidget *widgetToRemove = widget(index);
            removeTab(index);
            delete widgetToRemove;
            // Retirer l'état modifié de l'onglet supprimé du QVector
            m_modifiedTabs.remove(index);
        }
    }
}

void TabWidget::setTabModified(int index, bool modified)
{
    if (index >= 0 && index < m_modifiedTabs.size())
    {
        m_modifiedTabs[index] = modified; // Définissez la valeur correspondante dans le QVector
        // m_modifiedLabels[index]->setVisible(modified); // Affiche ou masque l'astérisque
    }
}

void TabWidget::handleTextModified(bool modified)
{
    int currentTabIndex = this->currentIndex();
    if (currentTabIndex != -1)
    {
        QTextEdit *textEdit = qobject_cast<QTextEdit *>(widget(currentTabIndex));
        if (textEdit)
        {
            QString tabText = this->tabText(currentTabIndex); // Utilisez 'this->' pour accéder à la fonction de la classe de base
            if (modified)
            {
                // Si le fichier est modifié, ajouter un astérisque (*) à son nom dans l'onglet
                if (!tabText.endsWith("*"))
                {
                    setTabText(currentTabIndex, tabText + "*");
                    emit fileModified(true);
                }
            }
            else
            {
                // Si le fichier n'est plus modifié, enlever l'astérisque (*) de son nom dans l'onglet
                if (tabText.endsWith("*"))
                {
                    setTabText(currentTabIndex, tabText.left(tabText.length() - 1));
                    emit fileModified(false);
                }
            }
        }
    }
}

void TabWidget::setCurrentTextEditModified(bool modified)
{
    if (m_currentTextEdit)
    {
        m_currentTextEdit->setIsModified(modified);
    }
}
