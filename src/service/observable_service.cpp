#include "observable_service.hpp"

namespace srv
{

ObservableService::ObservableService()
    : m_observersMtx()
    , m_observers( {} )
{
}

ObservableService::~ObservableService()
{
    std::lock_guard<std::mutex> guard( m_observersMtx );

    // Unregister all observers

    for ( IServiceObserver* observer : m_observers )
    {
        observer->stopObserving( this );
    }
}

void ObservableService::addObserver( IServiceObserver* ref )
{
    std::lock_guard<std::mutex> guard( m_observersMtx );

    m_observers.insert( ref );
}

void ObservableService::removeObserver( IServiceObserver* ref )
{
    std::lock_guard<std::mutex> guard( m_observersMtx );

    m_observers.erase( ref );
}

};