//
// Created by Borin Ouch on 2016-09-20.
//

#ifndef __CATEGORY_H__
#define __CATEGORY_H__


namespace Category
{
    enum Type
    {
        None                = 0,
        Scene               = 1 << 0,
        SceneAirLayer       = 1 << 1,
        PlayerAircraft      = 1 << 2,
        AlliedAircraft      = 1 << 3,
        EnemyAircraft       = 1 << 4,
    };
}


#endif//__CATEGORY_H__
