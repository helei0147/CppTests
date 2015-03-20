#include "value.h"
value::value(int which_variable, int which_value)//≥ı ºªØ¿‡
{
    variable_index = which_variable;
    value_index = which_value;
}
int value::GetValueIndex(void)
{
    return value_index;
}
int value::GetVariableIndex(void)
{
    return variable_index;
}
void value::SetValueIndex(int which_value)
{
    value_index = which_value;
}
void value::SetVariableIndex(int which_variable)
{
    variable_index = which_variable;
}
void value::operator=(value a)
{
    variable_index=a.GetVariableIndex();
    value_index=a.GetValueIndex();
    return;
}