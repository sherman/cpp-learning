//
// Created by sherman on 11.11.19.
//
#include <boost/intrusive_ptr.hpp>

#pragma once

namespace service {
    class Service {
    public:
        virtual void heartbeat(std::string& message) = 0;
    };
}

class Heartbeat {
public:
    class Service : public service::Service {
    public:
        void heartbeat(std::string& message) override = 0;
    };
};

class IServiceHolder {
    virtual service::Service* getService() = 0;
};

template<typename T>
class ServiceBase : public IServiceHolder {
public:
    service::Service* getService() override {
        return static_cast<T*>(this);
    }
};

class HeartbeatImpl : public Heartbeat::Service, public ServiceBase<HeartbeatImpl> {
    virtual void heartbeat(std::string& message);
};




