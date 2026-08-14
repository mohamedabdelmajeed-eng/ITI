#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>
#include <QString>

// All calculator operations and state are kept in this C++ backend.
class Calculator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString display READ display NOTIFY displayChanged FINAL)
    Q_PROPERTY(QString expression READ expression NOTIFY expressionChanged FINAL)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged FINAL)

public:
    explicit Calculator(QObject *parent = nullptr);

    QString display() const;
    QString expression() const;
    QString errorMessage() const;

    Q_INVOKABLE void pressButton(const QString &button);
    Q_INVOKABLE void clear();

signals:
    void displayChanged();
    void expressionChanged();
    void errorMessageChanged();

private:
    void enterDigit(const QString &digit);
    void enterDecimalPoint();
    void selectOperator(const QString &operation);
    void calculateResult();
    void removeLastDigit();
    void changeSign();
    void calculatePercent();

    bool calculate(double left, double right,
                   const QString &operation, double &result);
    double currentNumber(bool *ok = nullptr) const;
    QString formatNumber(double number) const;
    QString normalizeOperator(const QString &operation) const;
    QString operatorForDisplay(const QString &operation) const;

    void updateDisplay();
    void setDisplay(const QString &value);
    void setExpression(const QString &value);
    void setErrorMessage(const QString &value);
    void showError(const QString &message);

    QString m_display = QStringLiteral("0");
    QString m_expression;
    QString m_errorMessage;
    QString m_currentInput = QStringLiteral("0");
    QString m_pendingOperator;
    double m_savedNumber = 0.0;
    bool m_startNewNumber = true;
    bool m_resultIsDisplayed = false;
};

#endif // CALCULATOR_H
