//
//  InputDefine.h
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/11.
//
//

#ifndef __TsukubonQuest__InputDefine__
#define __TsukubonQuest__InputDefine__


// 入力の種類
enum class InputType {
    NONE = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    OK,
    CANCEL
};

// 入力の状態
enum class InputPhase {
    NONE,       // なし
    BEGIN,      // 開始
    TOUCHING,   // タッチ中
    END,        // 終了
};



#endif /* defined(__TsukubonQuest__InputDefine__) */
