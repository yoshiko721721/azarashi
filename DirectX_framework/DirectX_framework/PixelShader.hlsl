//--------------------------------------------------------------------------------------
// �s�N�Z���V�F�[�_�[
//--------------------------------------------------------------------------------------

// �s�N�Z���̏��̍\���́i�󂯎��p�j
struct PS_IN
{
    // float4�^�@���@float�^���S�̍\����
    float4 pos : SV_POSITION; // �s�N�Z���̉�ʏ�̍��W
    float4 col : COLOR0;
    float2 tex : TEXCOORD;
};

Texture2D myTexture : register(t0);
SamplerState mySampler : register(s0);

// �s�N�Z���V�F�[�_�[�̃G���g���|�C���g
float4 ps_main(PS_IN input) : SV_Target
{
    float4 color = myTexture.Sample(mySampler, input.tex);
    
    return color * input.col;
    //return float4(1, 1, 1, 1);
}
