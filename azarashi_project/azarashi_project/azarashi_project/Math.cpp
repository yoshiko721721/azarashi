#include "Math.h"

#define PI 3.1415926535

float Math::ConvertDegreeToRadian()
{
    return PI / 180;
}

//��̑��x���甽���W�� e ��Ԃ�
float Math::CoefficientOfRestitution(float v_Initial,float v_After){
    float e = v_After / v_Initial;
    return ConvertAbsoluteValue(e);
}

// �ՓˑO�̑��x���v�Z����֐�
float Math::CalculateVelocityBeforeImpact(float setHeight, float gravity)
{
    //�K�����̒l(��Βl)�ɂ��ĕԂ�
    
    float temp = sqrt(2 * gravity * ConvertAbsoluteValue(setHeight));
    temp = ConvertAbsoluteValue(temp);
    return temp;
}

// �Փˌ�̑��x���擾����C���^�[�t�F�[�X
double Math::calculateRestitutionCoefficient(const std::function<float()>& velocityProvider)
{
    float velocityAfter = velocityProvider();
    return velocityAfter;
}

//��Βl�ɂ��ĕԂ�
float Math::ConvertAbsoluteValue(float AbsValue)
{
    AbsValue = (AbsValue >= 0) ? AbsValue : -AbsValue;
    return AbsValue;
}
