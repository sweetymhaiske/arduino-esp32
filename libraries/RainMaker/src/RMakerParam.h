#include "RMakerType.h"
class Param
{
    private:
        param_handle_t *param;
       
    public:
        Param()
        {
            param = NULL;
        }
        
        param_handle_t* getParamHandle()
        {
            return param;
        } 
         
        void createParam(const char *param_name, const char *param_type, param_val_t val, uint8_t properties);
        void addUIType(const char *ui_type);
        void addBounds(param_val_t min, param_val_t max, param_val_t step);
};
