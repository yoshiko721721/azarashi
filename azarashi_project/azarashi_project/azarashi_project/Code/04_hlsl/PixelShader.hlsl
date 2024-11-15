//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[
//--------------------------------------------------------------------------------------

// �s�N�Z���̏��̍\���́i�󂯎��p�j
struct PS_IN
{
    // float4�^�@���@float�^���S�̍\����
    float4 pos : SV_POSITION; // �s�N�Z���̉�ʏ�̍��W
    float4 col : COLOR0;
    float2 tex : TEXCOORD;    //�s�N�Z����UV���W
};

//�O���[�o���ϐ��̐錾
//��C���ꑤ����f�[�^��n���ꂽ�Ƃ��ɃZ�b�g�����ϐ�
Texture2D myTexture : register(t0); //�e�N�X�`���[
SamplerState mySampler : register(s0);  //�T���v���[

// �s�N�Z���V�F�[�_�[�̃G���g���|�C���g
float4 ps_main(PS_IN input) : SV_Target
{
    //Sample�֐�->�e�N�X�`������Y����UV�ʒu�̃s�N�Z���F���Ƃ��Ă���
    float4 color = myTexture.Sample(mySampler, input.tex);

    color = color * input.col;

    //���肵���F��return����B
    return color;
}
