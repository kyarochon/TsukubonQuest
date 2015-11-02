//
//  ConvertUtil.h
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/06.
//
//

#ifndef __TsukubonQuest__ConvertUtil__
#define __TsukubonQuest__ConvertUtil__

#include "cocos2d.h"
#include "CharacterDefine.h"
USING_NS_CC;

namespace Util {
namespace Convert {
        

    static Vec2 gridToPixel(Vec2 gridPos, float mapGridY)
    {
        float pixelX = TILE_SIZE / 2.0f + gridPos.x * TILE_SIZE;
        float pixelY = TILE_SIZE / 2.0f + (mapGridY - gridPos.y - 1) * TILE_SIZE;
        
        return Vec2(pixelX, pixelY);
    }
    
    static Vec2 pixelToGrid(Vec2 pixelPos)
    {
        float gridX = pixelPos.x / TILE_SIZE;
        float gridY = GRID_MAX_Y - pixelPos.y / TILE_SIZE - 1.0f;
        
        return Vec2(gridX, gridY);
    }
    
        
}   // end namespace Convert
}   // end namespace Util



#endif /* defined(__TsukubonQuest__ConvertUtil__) */
