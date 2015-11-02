//
//  MapDefine.h
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/11.
//
//

#ifndef __TsukubonQuest__MapDefine__
#define __TsukubonQuest__MapDefine__


#define TILE_SIZE  (32.0f)

#define SCREEN_WIDTH  (640.0f)
#define SCREEN_HEIGHT (960.0f)

#define GRID_SCREEN_X (20)
#define GRID_SCREEN_Y (30)

//#define GRID_X_MAX ((int)(SCREEN_WIDTH  / TILE_SIZE))
//#define GRID_Y_MAX ((int)(SCREEN_HEIGHT / TILE_SIZE))

#define GRID_MAX_X (100)
#define GRID_MAX_Y (100)



enum class MapState {
    NONE      = 0,
    CHARACTER = 1,
    OBJECT    = 2,
    EVENT     = 3,
    MOVE      = 4,
};



#endif /* defined(__TsukubonQuest__MapDefine__) */
