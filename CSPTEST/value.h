

#ifndef VALUE_H
#define VALUE_H


class value//�������Ҫ��Ϊ�˴���һ�������洢ֵ��xi,a����������ݽṹ
{
public:
    value(int which_variable, int which_value);
    int GetVariableIndex(void);
    int GetValueIndex(void);
    void SetVariableIndex(int which_variable);
    void SetValueIndex(int which_value);
    void operator=(value a);
private:
    int variable_index;//�������
    int value_index;//��ֵ�ڱ���֮�еı��
};



#endif
