#include "jscpu.h"

#include <private/qjsengine_p.h>
#include <private/qjsvalue_p.h>
#include <private/qv4isel_moth_p.h>
#include <private/qv4function_p.h>
#include <QJSEngine>
#include <QDebug>

class QJSEngine;
class JsHandler :
{
    QV4::ExecutionEngine *m_execEngine;
    // Debugger interface
public:
    JsHandler(QV4::ExecutionEngine *engine) { m_execEngine = engine; }
};

bool JsHandler::pauseAtNextOpportunity() const
{
    qWarning() << "pause?";
    return true;
}

void JsHandler::maybeBreakAtInstruction()
{
    qWarning() << "break?";
    if (m_execEngine->currentContext->getFunction()) {
        qDebug() << m_execEngine->currentContext->type() << m_execEngine->currentContext->thisObject().type() << m_execEngine->currentContext->getFunction()->canUseSimpleFunction() << m_execEngine->currentContext->getFunction()->name()->toQString();
    }
}

void JsHandler::enteringFunction()
{
    qDebug() << "entering";
}

void JsHandler::leavingFunction(const QV4::ReturnedValue &retVal)
{
    Q_UNUSED(retVal);

    qDebug() << "leaving";
}

void JsHandler::aboutToThrow()
{
    qDebug() << "abouttothrow`";
}


JSCpu::JSCpu(Ram &ramdev, ScreenObject &object, int arg1, int arg2, int arg3, int arg4, int arg5, const std::mt19937 &randomness)
{
    m_jsEngine = new QJSEngine();
//    QJSValue globalObject = m_jsEngine->globalObject();
//    QV4::ExecutionEngine *execEngine = QJSValuePrivate::engine(&globalObject);

    QV4::ExecutionEngine *execEngine = QV8Engine::getV4(m_jsEngine->handle());
    execEngine->iselFactory.reset(new QV4::Moth::ISelFactory);
    execEngine->setDebugger(new JsHandler(execEngine));
    QJSValue fun = m_jsEngine->evaluate("(function(a, b) { return a + b; })", "foo.js");

//    QV4::ExecutionEngine *execEngine = QJSValuePrivate::engine(&fun);

    QJSValueList args;
    args << 1 << 2;
    QJSValue threeAgain = fun.call(args);
    qDebug() << threeAgain.toNumber();


//    m_jsEngine->evaluate("a=1+1");
    qDebug() << execEngine << execEngine->debugger();


}

void JSCpu::execute()
{
}

int JSCpu::readPort(uint8_t port)
{
}

int JSCpu::absorbHit(int str, int ifint)
{
}

void JSCpu::erase(QPainter *painter)
{
}

void JSCpu::draw(QPainter *painter)
{
}

int JSCpu::type()
{
}

int JSCpu::specialValue()
{
}

DebugContents JSCpu::debugContents()
{
}

void JSCpu::doSpecial(int, int)
{
}

void JSCpu::callobout(uint8_t one, uint16_t two)
{
}

int JSCpu::callobin(uint8_t one)
{
}

void JSCpu::sendmsg(char *msg)
{
}

int JSCpu::writefile(int start, int length, int adress)
{
}

int JSCpu::readfile(int start, int length, int adress)
{
}

void JSCpu::execinstr()
{
}
