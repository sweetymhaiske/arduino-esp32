#include "RMakerType.h"
class Param
{
    private:
        param_handle_t *param;
        bool updateParam;

    public:
        Param()
        {
            param = NULL;
            updateParam = false;
        }
        
        param_handle_t* getParamHandle()
        {
            return param;
        } 
        
        void setUpdateParam(bool val)
        {
            updateParam = val;
        }
    
        bool getUpdateParam()
        {
            return updateParam;
        }
        
        void updateAndReportParam();
        void createParam(const char *param_name, const char *param_type, param_val_t val, uint8_t properties);
        void addUIType(const char *ui_type);
        void addBounds(param_val_t min, param_val_t max, param_val_t step);
};
