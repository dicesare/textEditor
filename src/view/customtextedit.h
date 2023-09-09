// customtextedit.h
#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H

#include <QTextEdit>

class CustomTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    CustomTextEdit(QWidget *parent = nullptr);
    bool isTextChanged() const;
    void setIsModified(bool modified);

signals:
    void textModified(bool modified);

private slots:
    void onTextChanged();

private:
    bool m_isModified;
    QString m_previousText;
};

#endif // CUSTOMTEXTEDIT_H
