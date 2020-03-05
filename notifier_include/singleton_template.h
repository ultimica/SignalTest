#ifndef SINGLETON_TEMPLATE_H
#define SINGLETON_TEMPLATE_H

/// Simple singleton template

template <class SingleType>
class TSingleton
{
public:
    static SingleType &GetInstance()
    {
        static SingleType g_instance;
        return g_instance;
    }

private:
    TSingleton() {}
};
#endif
