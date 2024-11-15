//--------------------------------------------------------------------------------------
// ���_�V�F�[�_�[
//--------------------------------------------------------------------------------------

// ���_�̃f�[�^��\���\���́i�󂯎��p�j
struct VS_IN
{
    float4 pos : POSITION;
    float4 col : COLOR0;
    float2 tex : TEX;           //UV���W
};

// ���_�̃f�[�^��\���\���́i���M�p�j 
struct VS_OUT
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
    float2 tex : TEXCOORD;     //UV���W
};

//�O���[�o���ϐ��̐錾
//�萔�o�b�t�@�󂯎��p
cbuffer ConstBuffer : register(b0)
{
    //���_�J���[
    float4 vertexColor;
    //UV���W�ړ��s��
    matrix matrixTex;
    //�v���W�F�N�V�����ϊ��s��
    matrix matrixProj;
    //���[���h�ϊ��s��
    matrix matrixWorld;
}
 
// ���_�V�F�[�_�[�̃G���g���|�C���g 
VS_OUT vs_main(VS_IN input)
{
    VS_OUT output;
    
    //���[���h�ϊ��s��𒸓_���W�ɂ����āA�ړ��A��]�A�g��k������
    output.pos = mul(input.pos, matrixWorld);
    //���_���W�ɓ��e�s����|���āA���ʏ�̍��W�ɂ���
    output.pos = mul(output.pos, matrixProj);
    
    //UV���W���ړ�������
    float4 uv;
    uv.xy = input.tex;          //�s��|���Z�̂���float4�^�Ɉڂ�
    uv.z = 0.0f;                    
    uv.w = 1.0f;
    uv = mul(uv, matrixTex);    //UV���W�ƈړ��s����|���Z
    output.tex = uv.xy;         //�|���Z�̌��ʂ��ړ��p�ϐ��ɃZ�b�g
    
    //���_�J���[���Z�b�g����
    output.col = input.col * vertexColor;

    return output;
}