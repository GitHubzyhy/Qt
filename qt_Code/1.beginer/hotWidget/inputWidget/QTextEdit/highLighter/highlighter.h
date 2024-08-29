#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    Highlighter(QTextDocument *parent = nullptr);

    // QSyntaxHighlighter interface
protected:
    virtual void highlightBlock(const QString &text) override;//提供自己的语法突出显示

private:
    struct HighlightingRule
    {
        //存储突出显示规则
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QList<HighlightingRule> highlightingRules;//存储各种各样的规则

    QTextCharFormat keywordFormat;//常见的c++关键字的字符格式
    QTextCharFormat classFormat;//Qt的类名
    QTextCharFormat quotationFormat;//双引号
    QTextCharFormat functionFormat;//函数

    QTextCharFormat singleLineCommentFormat;//单行注释
    QTextCharFormat multiLineCommentFormat;//多行注释
    QRegularExpression commentStartExpression;//多行注释的开始
    QRegularExpression commentEndExpression;//多行注释的结束

};

#endif // HIGHLIGHTER_H
