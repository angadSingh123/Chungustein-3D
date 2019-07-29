#ifndef WORLD_H
#define WORLD_H
#include<Map.h>

class World
{
    public:
        World();
        virtual ~World();

    protected:

    private:
        Map* m_map;
};

#endif // WORLD_H
