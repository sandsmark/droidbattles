/***************************************************************************
                          myqmultilineedit.cpp  -  description
                             -------------------
    begin                : Sun Jun 3 2001
    copyright            : (C) 2001 by Andreas Agorander
    email                : Bluefire@linux.nu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "myqmultilineedit.h"
#include "instruktion.h"
#include <QDebug>
#include <QFont>
#include <QRegularExpression>
#include <QSyntaxHighlighter>

class Highlighter : public QSyntaxHighlighter
{
    struct Rule
    {
        QRegularExpression pattern;
        QVector<QTextCharFormat> formats;
    };

public:
    explicit Highlighter(QTextDocument *document);

protected:
    void highlightBlock(const QString &block) override;

private:
    void createDefRule(const Instruction &instruction);
    void createRule(const Instruction &instruction);
    QString argPattern(Instruction::Types type);
    QTextCharFormat argFormat(Instruction::Types type);
    void addRule(const QString &pattern, const QVector<QColor> &color, const QVector<QFont::Weight> &weight);

    QTextCharFormat m_commentFormat;
    QVector<Rule> m_rules;

    QRegularExpression m_declareDataRegex;
    QRegularExpression m_dataRegex;
    QRegularExpression m_stringRegex;

    QHash<Instruction::Types, QString> m_argTypePatterns;
};

Highlighter::Highlighter(QTextDocument *document) :
    QSyntaxHighlighter(document)
{
    const QStringList registers({ "ax",
                                  "bx",
                                  "cx",
                                  "dx",
                                  "al",
                                  "ah",
                                  "bl",
                                  "bh",
                                  "cl",
                                  "ch",
                                  "dl",
                                  "dh",
                                  "eip",
                                  "sp",
                                  "bp",
                                  "si",
                                  "di",
                                  "flags" });

    m_argTypePatterns[Instruction::Register] = "(" + registers.join('|') + ")";

    QStringList prefixed;
    for (const QString &reg : registers) {
        prefixed.append("@" + reg);
    }
    m_argTypePatterns[Instruction::RegisterRef] = "(" + prefixed.join('|') + ")";
    m_argTypePatterns[Instruction::Value] = "(-?\\w+)";
    m_argTypePatterns[Instruction::MemAddress] = "(@\\w+)";

    m_commentFormat.setForeground(Qt::gray);
    m_commentFormat.setFontWeight(QFont::Normal);

    m_declareDataRegex = QRegularExpression("(#\\w+)");
    m_dataRegex = QRegularExpression("(dw|db) +(\\w+)");
    m_stringRegex = QRegularExpression("(db) +(\"[^\"]*\")");

    addRule("(:)(\\w+)", { Qt::black, Qt::blue }, { QFont::Normal, QFont::Bold });
    addRule("(%CPUboot) +(\\d+)", { Qt::black, Qt::darkYellow }, { QFont::Bold, QFont::Normal });
    addRule("(%)(CPUstack) +(\\d+)", { Qt::black, Qt::darkGreen, Qt::darkYellow }, { QFont::Bold, QFont::Bold, QFont::Normal });
    addRule("(%org) +(\\d+)", { Qt::darkMagenta, Qt::darkYellow }, { QFont::Bold, QFont::Normal });
    addRule("(%interrupt) +(\\d+)", { Qt::darkCyan, Qt::darkYellow }, { QFont::Bold, QFont::Normal });
    addRule(R"((\$)(\w+) +(\d+))", { Qt::black, Qt::darkBlue, Qt::darkYellow }, { QFont::Normal, QFont::Bold, QFont::Normal });
    addRule("(iret|ret)", { Qt::darkMagenta }, { QFont::Bold });

    for (const Instruction &instruction : Instruction::instructions) {
        createRule(instruction);
    }
}

void Highlighter::highlightBlock(const QString &block)
{
    QTextCharFormat defaultFormat;
    defaultFormat.setForeground(Qt::red);
    setFormat(0, block.length(), defaultFormat);

    if (previousBlockState() != -1) {
        QRegularExpressionMatch dataMatch = m_dataRegex.match(block);

        if (!dataMatch.hasMatch()) {
            dataMatch = m_stringRegex.match(block);
        }

        if (!dataMatch.hasMatch()) {
            return;
        }

        QTextCharFormat format;
        format.setForeground(Qt::darkCyan);
        format.setFontWeight(QFont::Bold);
        setFormat(dataMatch.capturedStart(1), dataMatch.capturedLength(1), format);

        format.setForeground(Qt::darkYellow);
        format.setFontWeight(QFont::Normal);
        setFormat(dataMatch.capturedStart(2), dataMatch.capturedLength(2), format);

        setCurrentBlockState(-1);
        return;
    }

    QRegularExpressionMatch dataMatch = m_declareDataRegex.match(block);
    if (dataMatch.hasMatch()) {
        QTextCharFormat format;
        format.setForeground(Qt::black);
        format.setFontWeight(QFont::Bold);
        setFormat(dataMatch.capturedStart(1), dataMatch.capturedLength(1), format);

        setCurrentBlockState(0);
        return;
    }

    QString cleanedBlock = block;
    int commentStart = block.indexOf(';');
    if (commentStart >= 0) {
        setFormat(commentStart, block.length() - commentStart, m_commentFormat);
        cleanedBlock = block.left(block.length() - commentStart);
    }

    for (const Rule &rule : m_rules) {
        QRegularExpressionMatchIterator it = rule.pattern.globalMatch(block);
        while (it.hasNext()) {
            const QRegularExpressionMatch match = it.next();
            if (match.hasPartialMatch()) {
                continue;
            }
            if (match.lastCapturedIndex() < rule.formats.count()) {
                continue;
            }

            for (int i = 0; i < rule.formats.count(); i++) {
                setFormat(match.capturedStart(i + 1), match.capturedLength(i + 1), rule.formats[i]);
            }
        }
    }
}

void Highlighter::createRule(const Instruction &instruction)
{
    Rule rule;
    QString pattern = "^ *(" + instruction.token();

    QTextCharFormat mainFormat;
    mainFormat.setForeground(Qt::darkGreen);
    mainFormat.setFontWeight(QFont::Bold);
    rule.formats.append(std::move(mainFormat));

    if (instruction.getarg1bits()) {
        pattern += " +" + argPattern(instruction.getarg1type());
        rule.formats.append(argFormat(instruction.getarg1type()));
    }
    if (instruction.getarg2bits()) {
        pattern += " *, *" + argPattern(instruction.getarg2type());
        rule.formats.append(argFormat(instruction.getarg2type()));
    }
    pattern += ")";

    rule.pattern = QRegularExpression(pattern);
    rule.pattern.optimize();

    m_rules.append(std::move(rule));
}

QString Highlighter::argPattern(const Instruction::Types type)
{
    return m_argTypePatterns[type];
}

QTextCharFormat Highlighter::argFormat(const Instruction::Types type)
{
    QTextCharFormat format;
    switch (type) {
    case Instruction::Register:
        format.setForeground(Qt::darkYellow);
        format.setFontWeight(QFont::Normal);
        break;
    case Instruction::RegisterRef:
        format.setForeground(Qt::darkYellow);
        format.setFontWeight(QFont::Bold);
        break;
    case Instruction::Value:
        format.setForeground(Qt::darkBlue);
        format.setFontWeight(QFont::Normal);
        break;
    case Instruction::MemAddress:
        format.setForeground(Qt::darkBlue);
        format.setFontWeight(QFont::Bold);
        break;
    default:
        break;
    }
    return format;
}

void Highlighter::addRule(const QString &pattern, const QVector<QColor> &color, const QVector<QFont::Weight> &weight)
{
#ifdef QT_DEBUG
    Q_ASSERT(color.size() == weight.size());
#else
    if (color.size() != weight.size()) {
        qWarning() << "invalid rule?";
        return;
    }
#endif

    Rule rule;
    rule.pattern = QRegularExpression(pattern);
    for (int i = 0; i < color.count(); i++) {
        QTextCharFormat format;
        format.setForeground(color[i]);
        format.setFontWeight(weight[i]);
        rule.formats.append(std::move(format));
    }
    m_rules.append(std::move(rule));
}

MyQMultiLineEdit::MyQMultiLineEdit(QWidget *parent) :
    QPlainTextEdit(parent)
{
    new Highlighter(document());
}
