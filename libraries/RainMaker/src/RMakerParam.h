#include "RMakerType.h"
class Param
{
    private:
        const char *param_name;
        const param_handle_t *param_handle;
       
    public:
        Param()
        {
            param_name = NULL;
            param_handle = NULL;
        }
        
        //setter methods
        void setParamName(const char *param_name)
        {
            this->param_name = param_name;
        }
        void setParamHandle(const param_handle_t *param_handle)
        {
            this->param_handle = param_handle;
        }

        //getter methods
        const char *getParamName()
        {
            return param_name;
        }
        const param_handle_t *getParamHandle()
        {
            return param_handle;
        } 
         
        esp_err_t addUIType(const char *ui_type);
        esp_err_t addBounds(param_val_t min, param_val_t max, param_val_t step);
        esp_err_t updateAndReport(param_val_t val);
};

static Param createParam(const char *param_name, const char *param_type, param_val_t val, uint8_t properties)
{
    Param new_param;
    param_handle_t *param_handle = esp_rmaker_param_create(param_name, param_type, val, properties);
    new_param.setParamName(param_name);
    new_param.setParamHandle(param_handle);
    return new_param;
}
