#include "listener.h"
#include "mesh.h"

void Listener::EndContact(b2Contact* contact)
{
    void* dataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void *dataB = contact->GetFixtureB()->GetBody()->GetUserData();

    if (dataA && dataB) {
        static_cast<Mesh*>(dataA)->endContact();
        static_cast<Mesh*>(dataB)->endContact();
    }
}

