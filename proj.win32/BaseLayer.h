#ifndef __BASE_LAYER__H_
#define __BASE_LAYER__H_

#include "cocos2d.h"   
using namespace cocos2d;  
  
class BaseLayer:public CCLayerColor
{  
public:  
    virtual bool init();  
      
    CREATE_FUNC(BaseLayer);  
}; 
  
#endif  
