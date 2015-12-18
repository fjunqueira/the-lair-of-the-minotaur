//
// Created by fabio on 12/12/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_COMPARATOR_H
#define THE_LAIR_OF_THE_MINOTAUR_COMPARATOR_H

namespace pathfinding
{
    template<typename T>
    class Comparator
    {
    public:
        virtual const int Compare(const T& obj1, const T& obj2) const = 0;
    };
}


#endif //THE_LAIR_OF_THE_MINOTAUR_COMPARATOR_H
