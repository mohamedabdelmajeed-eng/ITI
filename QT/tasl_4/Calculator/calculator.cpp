#include "calculator.h"

#include <cmath>

Calculator::Calculator(QObject *parent)
    : QObject(parent)
{
}

QString Calculator::display() const
{
    return m_display;
}

QString Calculator::expression() const
{
    return m_expression;
}

QString Calculator::errorMessage() const
{
    return m_errorMessage;
}

void Calculator::pressButton(const QString &button)
{
    const QString key = button.trimmed();

    if (key.size() == 1 && key.at(0).isDigit()) {
        enterDigit(key);
    } else if (key == QStringLiteral(".")) {
        enterDecimalPoint();
    } else if (key == QStringLiteral("+")
               || key == QStringLiteral("-") || key == QStringLiteral("−")
               || key == QStringLiteral("*") || key == QStringLiteral("×")
               || key == QStringLiteral("/") || key == QStringLiteral("÷")) {
        selectOperator(key);
    } else if (key == QStringLiteral("=")) {
        calculateResult();
    } else if (key == QStringLiteral("⌫")) {
        removeLastDigit();
    } else if (key == QStringLiteral("±")) {
        changeSign();
    } else if (key == QStringLiteral("%")) {
        calculatePercent();
    } else if (key.compare(QStringLiteral("C"), Qt::CaseInsensitive) == 0) {
        clear();
    }
}

void Calculator::clear()
{
    m_currentInput = QStringLiteral("0");
    m_pendingOperator.clear();
    m_savedNumber = 0.0;
    m_startNewNumber = true;
    m_resultIsDisplayed = false;
    setDisplay(QStringLiteral("0"));
    setExpression(QString());
    setErrorMessage(QString());
}

void Calculator::enterDigit(const QString &digit)
{
    if (!m_errorMessage.isEmpty())
        clear();

    if (m_resultIsDisplayed) {
        m_currentInput = QStringLiteral("0");
        m_savedNumber = 0.0;
        m_pendingOperator.clear();
        m_resultIsDisplayed = false;
        setExpression(QString());
    }

    QString digitsOnly = m_currentInput;
    digitsOnly.remove(QLatin1Char('-'));
    digitsOnly.remove(QLatin1Char('.'));
    if (!m_startNewNumber && digitsOnly.length() >= 15)
        return;

    if (m_startNewNumber || m_currentInput == QStringLiteral("0")) {
        m_currentInput = digit;
        m_startNewNumber = false;
    } else {
        m_currentInput.append(digit);
    }
    updateDisplay();
}

void Calculator::enterDecimalPoint()
{
    if (!m_errorMessage.isEmpty())
        clear();

    if (m_resultIsDisplayed) {
        m_currentInput = QStringLiteral("0");
        m_savedNumber = 0.0;
        m_pendingOperator.clear();
        m_resultIsDisplayed = false;
        setExpression(QString());
    }

    if (m_startNewNumber) {
        m_currentInput = QStringLiteral("0.");
        m_startNewNumber = false;
    } else if (!m_currentInput.contains(QLatin1Char('.'))) {
        m_currentInput.append(QLatin1Char('.'));
    }
    updateDisplay();
}

void Calculator::selectOperator(const QString &operation)
{
    if (!m_errorMessage.isEmpty())
        return;

    const QString newOperator = normalizeOperator(operation);
    if (newOperator.isEmpty())
        return;

    bool ok = false;
    const double current = currentNumber(&ok);
    if (!ok) {
        showError(QStringLiteral("Invalid number"));
        return;
    }

    if (!m_pendingOperator.isEmpty() && m_startNewNumber) {
        m_pendingOperator = newOperator;
        setExpression(formatNumber(m_savedNumber) + QLatin1Char(' ')
                      + operatorForDisplay(m_pendingOperator));
        return;
    }

    if (!m_pendingOperator.isEmpty()) {
        double result = 0.0;
        if (!calculate(m_savedNumber, current, m_pendingOperator, result))
            return;
        m_savedNumber = result;
        m_currentInput = formatNumber(result);
        setDisplay(m_currentInput);
    } else {
        m_savedNumber = current;
    }

    m_pendingOperator = newOperator;
    m_startNewNumber = true;
    m_resultIsDisplayed = false;
    setExpression(formatNumber(m_savedNumber) + QLatin1Char(' ')
                  + operatorForDisplay(m_pendingOperator));
}

void Calculator::calculateResult()
{
    if (!m_errorMessage.isEmpty() || m_pendingOperator.isEmpty()
        || m_startNewNumber)
        return;

    bool ok = false;
    const double rightNumber = currentNumber(&ok);
    if (!ok) {
        showError(QStringLiteral("Invalid number"));
        return;
    }

    const QString completeExpression = formatNumber(m_savedNumber)
        + QLatin1Char(' ') + operatorForDisplay(m_pendingOperator)
        + QLatin1Char(' ') + formatNumber(rightNumber)
        + QStringLiteral(" =");

    double result = 0.0;
    if (!calculate(m_savedNumber, rightNumber, m_pendingOperator, result))
        return;

    m_savedNumber = result;
    m_currentInput = formatNumber(result);
    m_pendingOperator.clear();
    m_startNewNumber = true;
    m_resultIsDisplayed = true;
    setExpression(completeExpression);
    setDisplay(m_currentInput);
}

void Calculator::removeLastDigit()
{
    if (!m_errorMessage.isEmpty()) {
        clear();
        return;
    }
    if (m_startNewNumber || m_resultIsDisplayed)
        return;

    m_currentInput.chop(1);
    if (m_currentInput.isEmpty() || m_currentInput == QStringLiteral("-"))
        m_currentInput = QStringLiteral("0");
    updateDisplay();
}

void Calculator::changeSign()
{
    if (!m_errorMessage.isEmpty())
        clear();

    if (m_startNewNumber && !m_resultIsDisplayed) {
        m_currentInput = QStringLiteral("0");
        m_startNewNumber = false;
    }

    if (m_currentInput.startsWith(QLatin1Char('-')))
        m_currentInput.remove(0, 1);
    else if (currentNumber() != 0.0)
        m_currentInput.prepend(QLatin1Char('-'));

    m_resultIsDisplayed = false;
    updateDisplay();
}

void Calculator::calculatePercent()
{
    if (!m_errorMessage.isEmpty())
        return;

    bool ok = false;
    const double value = currentNumber(&ok);
    if (!ok) {
        showError(QStringLiteral("Invalid number"));
        return;
    }
    m_currentInput = formatNumber(value / 100.0);
    m_startNewNumber = false;
    m_resultIsDisplayed = false;
    updateDisplay();
}

bool Calculator::calculate(double left, double right,
                           const QString &operation, double &result)
{
    if (operation == QStringLiteral("+"))
        result = left + right;
    else if (operation == QStringLiteral("-"))
        result = left - right;
    else if (operation == QStringLiteral("*"))
        result = left * right;
    else if (operation == QStringLiteral("/")) {
        if (right == 0.0) {
            showError(QStringLiteral("Cannot divide by zero"));
            return false;
        }
        result = left / right;
    } else {
        showError(QStringLiteral("Unknown operation"));
        return false;
    }

    if (!std::isfinite(result)) {
        showError(QStringLiteral("Result is too large"));
        return false;
    }
    return true;
}

double Calculator::currentNumber(bool *ok) const
{
    return m_currentInput.toDouble(ok);
}

QString Calculator::formatNumber(double number) const
{
    if (std::abs(number) < 1.0e-15)
        number = 0.0;
    return QString::number(number, 'g', 15);
}

QString Calculator::normalizeOperator(const QString &operation) const
{
    if (operation == QStringLiteral("+")) return QStringLiteral("+");
    if (operation == QStringLiteral("-") || operation == QStringLiteral("−"))
        return QStringLiteral("-");
    if (operation == QStringLiteral("*") || operation == QStringLiteral("×"))
        return QStringLiteral("*");
    if (operation == QStringLiteral("/") || operation == QStringLiteral("÷"))
        return QStringLiteral("/");
    return QString();
}

QString Calculator::operatorForDisplay(const QString &operation) const
{
    if (operation == QStringLiteral("*")) return QStringLiteral("×");
    if (operation == QStringLiteral("/")) return QStringLiteral("÷");
    if (operation == QStringLiteral("-")) return QStringLiteral("−");
    return operation;
}

void Calculator::updateDisplay()
{
    setDisplay(m_currentInput);
    setErrorMessage(QString());
    if (!m_pendingOperator.isEmpty() && !m_startNewNumber) {
        setExpression(formatNumber(m_savedNumber) + QLatin1Char(' ')
                      + operatorForDisplay(m_pendingOperator) + QLatin1Char(' ')
                      + m_currentInput);
    }
}

void Calculator::setDisplay(const QString &value)
{
    if (m_display == value) return;
    m_display = value;
    emit displayChanged();
}

void Calculator::setExpression(const QString &value)
{
    if (m_expression == value) return;
    m_expression = value;
    emit expressionChanged();
}

void Calculator::setErrorMessage(const QString &value)
{
    if (m_errorMessage == value) return;
    m_errorMessage = value;
    emit errorMessageChanged();
}

void Calculator::showError(const QString &message)
{
    m_currentInput = QStringLiteral("0");
    m_pendingOperator.clear();
    m_savedNumber = 0.0;
    m_startNewNumber = true;
    m_resultIsDisplayed = false;
    setDisplay(QStringLiteral("Error"));
    setExpression(QString());
    setErrorMessage(message);
}
