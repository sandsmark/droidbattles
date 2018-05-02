#ifndef JSCPU_H
#define JSCPU_H

#include "cpu.h"

#include <private/qv4debugging_p.h>
#include <random>

class QJSEngine;

class JSCpu : public CPU, QV4::Debugging::Debugger
{
public:
    JSCpu(Ram &ramdev, ScreenObject &object, int arg1, int arg2, int arg3,
           int arg4, int arg5, const std::mt19937 &randomness);
    ~JSCpu() override;

    void execute() override;
    int type() override;
    int specialValue() override;
    void sendmsg(char *msg) override;
    struct DebugContents debugContents() override;
    void execinstr() override;

private:
    bool pauseAtNextOpportunity() const override;
    void maybeBreakAtInstruction() override;
    void enteringFunction() override;
    void leavingFunction(const QV4::ReturnedValue &retVal) override;
    void aboutToThrow() override;

    QJSEngine *m_jsEngine;
};

#endif // JSCPU_H
