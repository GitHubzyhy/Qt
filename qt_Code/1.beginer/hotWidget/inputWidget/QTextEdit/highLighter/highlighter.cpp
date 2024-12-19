#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)//必须将父参数传递给基类构造函数。父级是将应用语法突出显示的文本文档
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);//设置前景色
    keywordFormat.setFontWeight(QFont::Bold);//设置粗体

    const QString keywordPatterns[] =
    {
        //这里用到的QStringLiteral用于在编译期间构建QString提升效率
        QStringLiteral("\\bchar\\b"), QStringLiteral("\\bclass\\b"), QStringLiteral("\\bconst\\b"),
        QStringLiteral("\\bdouble\\b"), QStringLiteral("\\benum\\b"), QStringLiteral("\\bexplicit\\b"),
        QStringLiteral("\\bfriend\\b"), QStringLiteral("\\binline\\b"), QStringLiteral("\\bint\\b"),
        QStringLiteral("\\blong\\b"), QStringLiteral("\\bnamespace\\b"), QStringLiteral("\\boperator\\b"),
        QStringLiteral("\\bprivate\\b"), QStringLiteral("\\bprotected\\b"), QStringLiteral("\\bpublic\\b"),
        QStringLiteral("\\bshort\\b"), QStringLiteral("\\bsignals\\b"), QStringLiteral("\\bsigned\\b"),
        QStringLiteral("\\bslots\\b"), QStringLiteral("\\bstatic\\b"), QStringLiteral("\\bstruct\\b"),
        QStringLiteral("\\btemplate\\b"), QStringLiteral("\\btypedef\\b"), QStringLiteral("\\btypename\\b"),
        QStringLiteral("\\bunion\\b"), QStringLiteral("\\bunsigned\\b"), QStringLiteral("\\bvirtual\\b"),
        QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bvolatile\\b"), QStringLiteral("\\bbool\\b")
    };
    for (const QString &pattern : keywordPatterns)
    {
        rule.pattern = QRegularExpression(pattern); //模式字符串就是正则匹配规则
        rule.format = keywordFormat;
        highlightingRules.append(rule);//加入到QList中
    }

    //类名，引号，函数的突出显示规则
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);//深洋红
    //用于匹配以大写字母Q开头，后跟一个或多个大小写字母的单词
    rule.pattern = QRegularExpression(QStringLiteral("\\bQ[A-Za-z]+\\b"));
    rule.format = classFormat;

    quotationFormat.setForeground(Qt::darkGreen);
    //用于匹配一对双引号之间的任意字符序列
    rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);//设置斜体
    functionFormat.setForeground(Qt::blue);
    //前瞻断言的模式，用于匹配函数名（或标识符），这个函数名后面紧跟着一个左括号
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
    rule.format = functionFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::red);
    ////：匹配双斜杠 // 字符串。 [^\n]*：匹配零个或多个 非 换行符的字符。
    rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);
    // /**/
    commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));

}

void Highlighter::highlightBlock(const QString &text)
{
    //从QList中一个个取出来进行正则全局匹配，设置成对应的格式
    for (const HighlightingRule &rule : std::as_const(highlightingRules))//给定的左值引用转为常量左值引用
    {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) //判断是否还有结果
        {
            QRegularExpressionMatch math = matchIterator.next(); //返回下一个结果并推进迭代器
            setFormat(math.capturedStart(), math.capturedLength(), rule.format);//设置格式
        }
    }

    //处理多行注释
    setCurrentBlockState(0);//初始状态

    int startIndex = 0;
    if (previousBlockState() != 1)//上一段代码块不在注释中结束
        startIndex = text.indexOf(commentStartExpression);//搜索指定起始表达式

    while (startIndex >= 0)//没有找到起始表达式
    {
        //搜索指定的结束表达式
        QRegularExpressionMatch endMatch;//用于检查匹配的结果
        int endIndex = text.indexOf(commentEndExpression, startIndex, &endMatch);
        int commentLength;//高亮的长度
        if (endIndex == -1) //找不到指定的结束表达式
        {
            setCurrentBlockState(1);//状态改变
            commentLength = text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex
                            + endMatch.capturedLength();//捕获的长度
        }
        //设置文本字符格式--高亮
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression,//从上一段捕获末尾开始搜索指定的起始表达式
                                  startIndex + commentLength);
    }

}
