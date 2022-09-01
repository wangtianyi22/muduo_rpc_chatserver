#include "rpcController.h"

Controller::Controller()
{
    m_failed = false;
    m_errText = "";
}

void Controller::Reset()
{
    m_failed = false;
    m_errText = "";
}

bool Controller::Failed() const
{
    return m_failed;
}

std::string Controller::ErrorText() const
{
    return m_errText;
}

void Controller::SetFailed(const std::string& reason)
{
    m_failed = true;
    m_errText = reason;
}

// 目前未实现具体的功能
void Controller::StartCancel(){}
bool Controller::IsCanceled() const {return false;}
void Controller::NotifyOnCancel(google::protobuf::Closure* callback) {}