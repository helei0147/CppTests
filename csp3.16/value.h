

#ifndef VALUE_H
#define VALUE_H


class value//这个类主要是为了创造一个类来存储值（xi,a）这类的数据结构
{
public:
    value(int which_variable, int which_value);
    int GetVariableIndex(void);
    int GetValueIndex(void);
    void SetVariableIndex(int which_variable);
    void SetValueIndex(int which_value);
    void operator=(value a);
private:
    int variable_index;//变量标号
    int value_index;//该值在变量之中的标号
};



#endif
