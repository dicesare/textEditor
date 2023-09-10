#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H

#include <QTextEdit>
#include <QDebug>

/**
 * @class CustomTextEdit
 * @brief Represents a custom text editor widget.
 * 
 * The CustomTextEdit class extends QTextEdit to provide custom behavior for text modification detection.
 */
class CustomTextEdit : public QTextEdit
{
    Q_OBJECT

public:

    /**
     * @brief Constructs a new CustomTextEdit instance.
     * 
     * @param parent The parent widget.
     */
    CustomTextEdit(QWidget *parent = nullptr);

    /**
     * @brief Checks whether the text has been modified.
     * 
     * @return True if the text has been modified, false otherwise.
     */
    bool isTextChanged() const;

    /**
     * @brief Sets the modified state of the text.
     * 
     * @param modified Whether the text is considered modified.
     */
    void setIsModified(bool modified);

signals:

    /**
     * @brief Emitted when the text is modified.
     * 
     * @param modified The new modified state of the text.
     */
    void textModified(bool modified);

private slots:

    /**
     * @brief Called when the text is modified. Emits the textModified signal.
     */
    void onTextChanged();

private:
    bool m_isModified = false;          ///< Tracks whether the text has been modified.
    QString m_previousText;    ///< Stores the previous state of the text for comparison.
};

#endif // CUSTOMTEXTEDIT_H
